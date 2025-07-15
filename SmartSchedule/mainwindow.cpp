#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout> // 包含 QVBoxLayout

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupSemesterTabs();

}

MainWindow::~MainWindow()
{
    delete ui;
}


// 弹出全局设置对话框
void MainWindow::on_action_globalSettings_triggered()
{
    SettingsDialog dialog(this);
    dialog.setValues(m_totalCredits,m_semesterCreditsLimit);

    // exec() 以模态方式显示对话框（阻塞主窗口，直到对话框关闭）。
    // 如果用户点击 "确定"（Accepted），进入条件块；如果点击 "取消"，则跳过。

    if(dialog.exec() == QDialog::Accepted) {
        m_totalCredits = dialog.totalCredits();
        m_semesterCreditsLimit = dialog.semesterCreditsLimit();
        qDebug() << "New settings saved:" << m_totalCredits << m_semesterCreditsLimit <<"\n";
    }
}

// 退出事件
void MainWindow::on_action_quit_triggered()
{
    QApplication::quit();
}

// 弹出无课时间对话框
void MainWindow::on_action_noClassTime_triggered()
{
    if(m_mainScheduleData.empty()) {
        // 初始化数据结构
        m_mainScheduleData.resize(numSemesters);
        for(int i=0;i<numSemesters;i++) {
            m_mainScheduleData[i].resize(numWeeks);
            for(int j=0;j<numWeeks;j++) {
                m_mainScheduleData[i][j].resize(numDays*numSlots,0);
            }
        }
    }

    NoClassTimeDialog dialog(this);
    dialog.setScheduleData(m_mainScheduleData);

    if(dialog.exec() == QDialog::Accepted) {
        m_mainScheduleData = dialog.scheduleData();
        qDebug() << "No-class time data updated.\n";
    }

}

// 点击保存方案时
void MainWindow::on_action_save_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this,"保存课程","schedule.json","JSON Files (*.json)");
    if(filePath.isEmpty()) return;

    saveSchedule(filePath,m_generatedSchedule);
    QMessageBox::information(this,"成功",QString("保存成功"));
}

// 选中加载方案时
void MainWindow::on_action_load_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,"导入方案","","JSON Files (*.json)");
    if(filePath.isEmpty()) return;

    m_generatedSchedule = loadSchedule(filePath);
    if(!m_generatedSchedule.empty()) {
        QMessageBox::information(this,"成功",QString("成功导入选课方案"));
        updateScheduleView();
    }
}

// 选中产生方案时
void MainWindow::on_action_generate_triggered()
{
    if (m_allCourses.isEmpty()) {
        QMessageBox::warning(this, "错误", "请先通过“文件”->“导入课程”来加载课程列表。");
        return;
    }

    // 1. 数据初始化
    m_generatedSchedule.clear();
    courseMap.clear();
    for (const auto& course : m_allCourses) {
        courseMap[course.id] = course;
    }

    QList<Course> coursesToSchedule = m_allCourses;

    // 2. 扩展功能：考虑优先级 (Compulsory vs. Elective)
    std::sort(coursesToSchedule.begin(), coursesToSchedule.end(), [](const Course &a, const Course &b) {
        if (a.required == "Compulsory" && b.required != "Compulsory") return true;
        if (a.required != "Compulsory" && b.required == "Compulsory") return false;
        return a.prerequisites.size() < b.prerequisites.size();
    });

    int currentTotalCredits = 0;
    QVector<int> semesterCredits(numSemesters, 0);

    for (const auto& course : coursesToSchedule) {
        ScheduledCourse sc;
        sc.course_id = course.id;
        sc.semester = -1;
        m_generatedSchedule.append(sc);
    }

    // 3. 核心排课算法
    bool madeProgressInLastPass = true;
    while(madeProgressInLastPass) {
        madeProgressInLastPass = false;
        for (int i = 0; i < m_generatedSchedule.size(); ++i) {
            if (m_generatedSchedule[i].semester != -1) continue;

            const Course& course = courseMap[m_generatedSchedule[i].course_id];

            bool prereqsMet = true;
            int earliestPossibleSemester = 0;
            for (const QString &prereq_id : course.prerequisites) {
                auto it = std::find_if(m_generatedSchedule.begin(), m_generatedSchedule.end(),
                                       [&](const ScheduledCourse& s){ return s.course_id == prereq_id; });
                if (it != m_generatedSchedule.end()) {
                    if (it->semester == -1) {
                        prereqsMet = false;
                        break;
                    }
                    earliestPossibleSemester = qMax(earliestPossibleSemester, it->semester + 1);
                }
            }
            if (!prereqsMet) continue;

            for (int sem = earliestPossibleSemester; sem < numSemesters; ++sem) {
                // ==================== 新增逻辑：检查开课学期是否匹配 ====================
                // Autumn (秋季) -> 对应学期索引 0, 2, 4, 6
                // Spring (春季) -> 对应学期索引 1, 3, 5, 7
                bool isAutumnSemester = (sem % 2 == 0);
                bool isSpringSemester = (sem % 2 != 0);

                if (course.semester == "Autumn" && !isAutumnSemester) {
                    continue; // 课程是秋季开课，但当前是春季学期，跳过
                }
                if (course.semester == "Spring" && !isSpringSemester) {
                    continue; // 课程是春季开课，但当前是秋季学期，跳过
                }
                // =======================================================================

                if (m_semesterCreditsLimit > 0 && (semesterCredits[sem] + course.credit > m_semesterCreditsLimit)) {
                    continue;
                }

                bool courseScheduled = false;
                for (const auto& offering : std::as_const(course.offerings)) {
                    bool isConflict = false;

                    for (const auto& scheduledCourse : std::as_const(m_generatedSchedule)) {
                        if (scheduledCourse.semester == sem) {
                            const Course& otherCourse = courseMap[scheduledCourse.course_id];
                            const Offering* otherOffering = nullptr;
                            for (int j = 0; j < otherCourse.offerings.size(); ++j) {
                                if (otherCourse.offerings[j].id == scheduledCourse.class_id) {
                                    otherOffering = &otherCourse.offerings[j];
                                    break;
                                }
                            }
                            if (otherOffering && (offering.weeks & otherOffering->weeks)) {
                                for (int day = 0; day < 7; ++day) {
                                    if ((offering.times[day] & otherOffering->times[day])) {
                                        isConflict = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if (isConflict) break;
                    }
                    if (isConflict) continue;

                    if (!m_mainScheduleData.empty()) {
                        for (int week = 0; week < numWeeks; ++week) {
                            if ((offering.weeks >> week) & 1) {
                                for (int day = 0; day < numDays; ++day) {
                                    for (int slot = 0; slot < numSlots; ++slot) {
                                        if ((offering.times[day] >> slot) & 1) {
                                            if (m_mainScheduleData[sem][week][day * numSlots + slot]) {
                                                isConflict = true;
                                                break;
                                            }
                                        }
                                    }
                                    if (isConflict) break;
                                }
                            }
                            if (isConflict) break;
                        }
                    }
                    if (isConflict) continue;

                    m_generatedSchedule[i].semester = sem;
                    m_generatedSchedule[i].class_id = offering.id;
                    semesterCredits[sem] += course.credit;
                    currentTotalCredits += course.credit;
                    madeProgressInLastPass = true;
                    courseScheduled = true;
                    break;
                }
                if (courseScheduled) break;
            }
        }
    }

    // 4. 结果反馈
    if (currentTotalCredits < m_totalCredits) {
        QMessageBox::warning(this, "生成方案可能未完成", QString("无法生成满足 %1 总学分下限的方案。当前已排课程总学分: %2").arg(m_totalCredits).arg(currentTotalCredits));
    } else {
        QMessageBox::information(this, "成功", QString("成功生成选课方案，总学分: %1").arg(currentTotalCredits));
    }

    updateScheduleView();
}


// 选中重置方案时
void MainWindow::on_action_reset_triggered()
{
    clearScheduleView();
    m_generatedSchedule.clear();
}

// 选中导入课程时
void MainWindow::on_action_loadCourses_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,"导入课程","","JSON Files (*.json)");
    if(filePath.isEmpty()) return;

    m_allCourses = loadCourses(filePath);
    if(!m_allCourses.empty()) {
        QMessageBox::information(this,"成功",QString("已经导入 %1 门课程").arg(m_allCourses.size()));
    }
}


// 选中查看课程列表时
void MainWindow::on_action_viewCourses_triggered()
{
    CourseManagerDialog dialog(this);
    dialog.setCourseList(m_allCourses);
    if(dialog.exec() == QDialog::Accepted) {
        m_allCourses = dialog.getCourseList();
    }
}

// 初始化课表
void MainWindow::setupSemesterTabs()
{
    ui->mainTabWidget->clear(); // 清楚默认标签页
    m_semesterTabs.clear();

    for(int i=0;i<8;i++) {

        // 为每个标签页创建一个父QWidget和垂直布局
        QWidget* tabContentWidget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout(tabContentWidget);

        // 创建周选择器
        QComboBox* weekSelector = new QComboBox();
        for(int i=0;i<18;i++) {
            weekSelector->addItem(QString("第 %1 周").arg(i+1),i+1);
        }

        // 创建课表
        QTableWidget* table = new QTableWidget(13,7);
        // 设置表头
        table->setHorizontalHeaderLabels({"周一", "周二", "周三", "周四", "周五", "周六", "周日"});
        QStringList verticalHeaders;
        for(int i=1;i<=13;++i) {
            verticalHeaders << QString::number(i);
        }
        table->setVerticalHeaderLabels(verticalHeaders);

        // 添加至布局
        layout->addWidget(weekSelector);
        layout->addWidget(table);
        // 设置布局
        tabContentWidget->setLayout(layout);

        // 储存控件
        SemesterTabWidgets tabwidget;
        tabwidget.mainWidget = tabContentWidget;
        tabwidget.weekSelector = weekSelector;
        tabwidget.scheduleTable = table;
        m_semesterTabs.append(tabwidget);

        // 添加至UI
        ui->mainTabWidget->addTab(tabContentWidget,QString("第 %1 学期").arg(i+1));

        // 连接信号和槽，周次变化时更新课表，使用lambda表达式来捕获当前学期的索引 i
        connect(weekSelector,&QComboBox::currentIndexChanged,this,[this,i]() {
            onWeekChanged(i);
        });
    }
}

void MainWindow::updateScheduleView()
{
    clearScheduleView();

    // 建立映射关系
    for(const Course course:m_allCourses) {
        courseMap[course.id] = course;
    }

    // 遍历选课方案
    for(const ScheduledCourse& scheduledcourse:m_generatedSchedule) {
        // 跳过未选中课程
        if(scheduledcourse.semester < 0) continue;
        // 如果在课程列表中找不到，跳过
        if(!courseMap.contains(scheduledcourse.course_id)) continue;

        // 找出课程信息
        const Course& course = courseMap[scheduledcourse.course_id];
        const Offering* selectedOffering = nullptr;
        // 找出选中开课班级
        for(const Offering& o:course.offerings) {
            if(o.id == scheduledcourse.class_id) {
                selectedOffering = &o;
                break;
            }
        }
        if(selectedOffering == nullptr) continue; // 安全检查

        // 获取当前学期UI控件
        const SemesterTabWidgets& curTab = m_semesterTabs[scheduledcourse.semester];
        // 获取选择的周次
        int selectedWeek = curTab.weekSelector->currentData().toInt();
        // 判断该周是否开课
        if( !((selectedOffering->weeks>>(selectedWeek-1)) & 1)) {
            continue; // 无课则跳过
        }

        // 显示文本
        QString displayText = course.name+"@\n"+selectedOffering->teacher;
        // 高亮突出
        QColor color = QColor::fromHsl(qHash(course.id)%360, 180 , 210);

        QTableWidget* table = curTab.scheduleTable;
        const auto times = selectedOffering->times;

        // 遍历课表
        for(int day=0;day<7;day++) {
            int time = times[day];
            for(int slot=0;slot<13;slot++) {
                if((time>>slot) & 1) {
                    // 获取对应项目
                    QTableWidgetItem* item = table->item(slot,day);
                    if(!item) {
                        item=new QTableWidgetItem();
                        table->setItem(slot,day,item);
                    }
                    // 设置文本
                    if(!item->text().isEmpty()) {
                        item->setText(item->text()+"\n---\n"+displayText);
                    }else {
                        item->setText(displayText);
                    }
                    // 设置颜色
                    item->setBackground(color);
                    // 设置居中
                    item->setTextAlignment(Qt::AlignCenter);
                }
            }
        }
    }
    // 自动调整行和列的大小以适应内容
    for(const auto& tab : m_semesterTabs){
        tab.scheduleTable->resizeColumnsToContents();
        tab.scheduleTable->resizeRowsToContents();
    }

}

void MainWindow::clearScheduleView()
{
    // 遍历每一个表格， clearContents() 会移除所有单元格内的 QTableWidgetItem，但保留水平和垂直表头
    for(const SemesterTabWidgets& semestertab:m_semesterTabs) {
        semestertab.scheduleTable->clearContents();
    }
}

void MainWindow::on_action_saveCourses_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this,"保存课程","courses.json","JSON Files (*.json)");
    if(filePath.isEmpty()) return;

    saveCourses(filePath,m_allCourses);
    QMessageBox::information(this,"成功",QString("保存成功"));

}

void MainWindow::onWeekChanged(int semesterIndex)
{
    qDebug() <<  "Week changed for semester" << semesterIndex + 1 << ". Updating view.\n";
    updateScheduleView();
}

