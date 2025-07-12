#include "coursemanagerdialog.h"
#include "ui_coursemanagerdialog.h"

//  定义自定义角色，用于在Item中存储Course对象
const int CourseRole = Qt::UserRole+1;

CourseManagerDialog::CourseManagerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CourseManagerDialog)
{
    ui->setupUi(this);

    setupModels(); // 初始化
    connectSignals();
    clearDetails();

}

CourseManagerDialog::~CourseManagerDialog()
{
    delete ui;
}

void CourseManagerDialog::setCourseList(const QList<Course> &courses)
{
    m_courses = courses;
    populateCourseList(); // 产生列表
    if(!m_courses.empty()) {
        ui->listView_courses->setCurrentIndex(m_courseModel->index(0,0));
    } else {
        clearDetails();
    }
}

QList<Course> CourseManagerDialog::getCourseList() const
{
    return m_courses;
}

void CourseManagerDialog::onCourseSelectionChanged(const QModelIndex &cur, const QModelIndex &prev)
{
    Q_UNUSED(prev); // 明确标记参数 previous（前一个选中项）未被使用
    if(!cur.isValid()) {
        clearDetails();
        return;
    }
    m_currentCourseIndex = cur;
    // 获取完整的选中课程对象
    const Course& selectedCourse = m_courses[cur.row()];

    // 更新右侧UI
    displayCourseDetails(selectedCourse);
    displayOfferings(selectedCourse.offerings);
}

void CourseManagerDialog::on_btn_addCourse_clicked()
{
    // 创建新课程对象
    Course newcourse;
    newcourse.id = "请输入id";
    newcourse.name = "新课程";
    m_courses.append(newcourse);
    // 创建新的列表项
    QStandardItem *newItem = new QStandardItem(QString("%1 (%2)").arg(newcourse.name,newcourse.id));
    newItem->setData(QVariant::fromValue(newcourse),CourseRole);
    newItem->setEditable(false);
    m_courseModel->appendRow(newItem);

    // 自动选择新添加的项
    ui->listView_courses->setCurrentIndex(m_courseModel->indexFromItem(newItem));

}

void CourseManagerDialog::on_btn_deleteCourse_clicked()
{
    // 检查选中是否有效
    if(!m_currentCourseIndex.isValid()) {
        QMessageBox::warning(this,"提示","请先选择要删除的课程");
        return;
    }

    // 弹出消息框询问是否确定删除
    int ret = QMessageBox::question(this,"确定删除","确定要删除选中课程吗？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);

    // 如果用户确定则删除，删除后重新刷新列表，如果为空，清空右侧界面
    if(ret == QMessageBox::Yes)
    {
        m_courses.removeAt(m_currentCourseIndex.row());
        populateCourseList();
        if(m_courseModel->rowCount() > 0) {
            ui->listView_courses->setCurrentIndex(m_courseModel->index(0,0));
        } else {
            clearDetails();
        }
    }
}

void CourseManagerDialog::on_btn_saveCourseChanges_clicked()
{
    // 检查选中是否合法
    if(!m_currentCourseIndex.isValid()) {
        QMessageBox::warning(this,"提示","没有要选中的课程以供保存");
        return;
    }
    // 直接修改选中课程的信息
    Course& courseToUpdate = m_courses[m_currentCourseIndex.row()];
    courseToUpdate.id = ui->lineEdit_courseId->text();
    courseToUpdate.name = ui->lineEdit_courseName->text();
    courseToUpdate.semester = ui->lineEdit_semester->text();
    courseToUpdate.required = ui->lineEdit_required->text();
    courseToUpdate.credit = ui->spinBox_credit->value();
    courseToUpdate.prerequisites = ui->lineEdit_prerequisites->text().split(",",Qt::SkipEmptyParts); // 跳过空白部分，以逗号分隔

    // 修改UI显示的内容

    QStandardItem* item = m_courseModel->itemFromIndex(m_currentCourseIndex);
    item->setText(QString("%1 (%2)").arg(courseToUpdate.name,courseToUpdate.id));

    // 更新项附加的数据
    item->setData(QVariant::fromValue(courseToUpdate),CourseRole);

    QMessageBox::information(this,"提示","已经保存相关信息");
}

void CourseManagerDialog::on_btn_addOffering_clicked()
{
    if(!m_currentCourseIndex.isValid()) {
        QMessageBox::warning(this,"提示","请先选择课程");
        return;
    }
    OfferingDialog dialog(this);

    if(dialog.exec() == QDialog::Accepted) {
        Offering newOffering = dialog.getOffering();
        m_courses[m_currentCourseIndex.row()].offerings.append(newOffering);
        displayOfferings(m_courses[m_currentCourseIndex.row()].offerings);
    }
}

void CourseManagerDialog::on_btn_editOffering_clicked()
{
    // 检查选中有效
    if(!m_currentCourseIndex.isValid()) {
        QMessageBox::warning(this,"提示","请先选择课程");
        return;
    }
    // 获取选中项目的下标
    QModelIndexList selected = ui->tableView_offerings->selectionModel()->selectedRows();
    if(selected.empty()) {
        QMessageBox::warning(this,"提示","请先选择开课信息");
        return;
    }
    int selectedrow = selected.first().row();

    // 打开对话框进行数据交换
    OfferingDialog dialog(this);
    // 传入原始数据
    dialog.setOffering(m_courses[m_currentCourseIndex.row()].offerings[selectedrow]);

    if(dialog.exec() == QDialog::Accepted) {
        // 保存更改数据
        m_courses[m_currentCourseIndex.row()].offerings[selectedrow] = dialog.getOffering();
        // 刷新ui
        displayOfferings(m_courses[m_currentCourseIndex.row()].offerings);
    }
}

void CourseManagerDialog::on_btn_deleteOffering_clicked()
{
    // 检查选中有效
    if(!m_currentCourseIndex.isValid()) {
        QMessageBox::warning(this,"提示","请先选择课程");
        return;
    }
    // 获取选中项目的下标
    QModelIndexList selected = ui->tableView_offerings->selectionModel()->selectedRows();
    if(selected.empty()) {
        QMessageBox::warning(this,"提示","请先选择开课信息");
        return;
    }

    // 弹出消息框询问是否确定删除
    int ret = QMessageBox::question(this,"确定删除","确定要删除选中开课信息吗？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);

    // 如果用户确定则删除，删除后重新刷新列表，如果为空，清空右侧界面
    if(ret == QMessageBox::Yes)
    {
        m_courses[m_currentCourseIndex.row()].offerings.removeAt(selected.first().row());
        displayOfferings(m_courses[m_currentCourseIndex.row()].offerings);
    }
}

void CourseManagerDialog::on_lineEdit_search_textChanged(const QString &text)
{
    // 遍历所有课程项，隐藏不匹配的项
    for(int i=0;i<m_courseModel->rowCount();i++) {
        bool match = m_courseModel->item(i)->text().contains(text,Qt::CaseInsensitive);
        ui->listView_courses->setRowHidden(i,!match);
    }
}

void CourseManagerDialog::setupModels()
{
    // 新建并连接模型
    m_courseModel = new QStandardItemModel(this);
    m_offeringsModel = new QStandardItemModel(this);

    ui->listView_courses->setModel(m_courseModel);
    ui->tableView_offerings->setModel(m_offeringsModel);

    ui->tableView_offerings->setSelectionBehavior(QAbstractItemView::SelectRows); // 整行选择
    ui->tableView_offerings->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 不可编辑

    m_offeringsModel->setHorizontalHeaderLabels({"开课编号", "教师", "周次(摘要)", "时间(摘要)"}); // 设置水平标签（表头）
}

void CourseManagerDialog::connectSignals()
{
    // 当右侧选中的项目变化
    connect(ui->listView_courses->selectionModel(),&QItemSelectionModel::currentChanged,
            this,&CourseManagerDialog::onCourseSelectionChanged);

    // 当按钮点击
    // connect(ui->btn_addCourse,&QPushButton::clicked,this,&CourseManagerDialog::on_btn_addCourse_clicked);
    // connect(ui->btn_deleteCourse,&QPushButton::clicked,this,&CourseManagerDialog::on_btn_deleteCourse_clicked);
    // connect(ui->btn_saveCourseChanges,&QPushButton::clicked,this,&CourseManagerDialog::on_btn_saveCourseChanges_clicked);

    // connect(ui->btn_addOffering,&QPushButton::clicked,this,&CourseManagerDialog::on_btn_addOffering_clicked);
    // connect(ui->btn_editOffering,&QPushButton::clicked,this,&CourseManagerDialog::on_btn_editOffering_clicked);
    // connect(ui->btn_deleteOffering,&QPushButton::clicked,this,&CourseManagerDialog::on_btn_deleteOffering_clicked);

    // 当搜索框的文本变化
    connect(ui->lineEdit_search,&QLineEdit::textChanged,this,&CourseManagerDialog::on_lineEdit_search_textChanged);
}

void CourseManagerDialog::populateCourseList()
{
    m_courseModel->clear();
    for(const Course& course:m_courses)
    {
        // 创建列表项并设置显示文本
        QStandardItem* newitem = new QStandardItem(QString("%1 (%2)").arg(course.name,course.id));
        // 禁止项编辑
        newitem->setEditable(false);
        // 绑定课程对象到自定义角色
        newitem->setData(QVariant::fromValue(course),CourseRole);
        // 将项添加到模型
        m_courseModel->appendRow(newitem);
    }
}

void CourseManagerDialog::displayCourseDetails(const Course &course)
{
    ui->detailsGroupBox->setEnabled(true);
    // 显示数据
    ui->lineEdit_courseId->setText(course.id);
    ui->lineEdit_courseName->setText(course.name);
    ui->lineEdit_semester->setText(course.semester);
    ui->lineEdit_prerequisites->setText(course.prerequisites.join(","));
    ui->lineEdit_required->setText(course.required);
    ui->spinBox_credit->setValue(course.credit);
}

void CourseManagerDialog::displayOfferings(const QList<Offering> &offerings)
{
    m_offeringsModel->removeRows(0,m_offeringsModel->rowCount());
    for(const Offering& offering:offerings)
    {
        // 创建一行的数据
        QList<QStandardItem*> rowItems;
        rowItems.append(new QStandardItem(offering.id));
        rowItems.append(new QStandardItem(offering.teacher));
        rowItems.append(new QStandardItem(weeksToSummary(offering.weeks)));
        rowItems.append(new QStandardItem(timesToSummary(offering.times)));
        // 设置不可编辑
        for(auto item:rowItems) item->setEditable(false);
        // 添加新行
        m_offeringsModel->appendRow(rowItems);
    }
}

void CourseManagerDialog::clearDetails()
{
    ui->detailsGroupBox->setEnabled(false);
    ui->lineEdit_courseId->clear();
    ui->lineEdit_courseName->clear();
    ui->lineEdit_prerequisites->clear();
    ui->lineEdit_required->clear();
    ui->lineEdit_semester->clear();
    ui->spinBox_credit->setValue(0);
    m_offeringsModel->removeRows(0,m_offeringsModel->rowCount());
}

QString CourseManagerDialog::weeksToSummary(int weeks) const
{
    QStringList enableWeeks;
    for(int i=0;i<18;i++) {
        if(weeks & (1<<i)) {
            enableWeeks << QString::number(i+1);
        }
    }
    if(enableWeeks.empty()) return "无";
    else return QString("第 %1 周").arg(enableWeeks.join(","));
}

QString CourseManagerDialog::timesToSummary(const QVector<int> &times) const
{
    int count=0;
    if(times.size() != 7) return "数据错误";
    for(int time:times) {
        for(int i=0;i<13;i++) {
            if(time & (1<<i)) {
                count++;
            }
        }
    }
    return QString("共 %1 节").arg(count);
}


