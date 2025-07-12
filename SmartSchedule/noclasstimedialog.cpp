#include "noclasstimedialog.h"
#include "ui_noclasstimedialog.h"
#include <QCheckBox> // 需要包含QCheckBox头文件
#include <QDebug>    // 用于调试输出


NoClassTimeDialog::NoClassTimeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NoClassTimeDialog)
{
    ui->setupUi(this);

    // 初始化
    setupScheduleSelectors();
}

NoClassTimeDialog::~NoClassTimeDialog()
{
    delete ui;
}

void NoClassTimeDialog::setScheduleData(const QVector<QVector<QVector<bool> > > &data)
{
    scheduleFreeTime = data;

    // 检查传入的数据是否有效，防止MainWindow传来空数据
    if (scheduleFreeTime.isEmpty() || scheduleFreeTime[0].isEmpty()) {
        qWarning() << "Warning: Received empty schedule data!";
        return; // 不进行刷新，避免崩溃
    }
    // 刷新显示
    updateScheduleView();
}

QVector<QVector<QVector<bool> > > NoClassTimeDialog::scheduleData() const
{
    return scheduleFreeTime;
}


void NoClassTimeDialog::updateScheduleView()
{
    if (scheduleFreeTime.isEmpty()) return;

    // 获得选择的索引
    int currentSemester = ui->comboBox_semester->currentData().toInt();
    int currentWeek = ui->comboBox_week->currentData().toInt();

    // 根据选择填充格子
    populateScheduleGrid(currentSemester,currentWeek);

}

void NoClassTimeDialog::onScheduleCheckBoxStateChanged(int state, int semester, int week, int day, int slot)
{
    // 更改数据结构中的状态
    scheduleFreeTime[semester][week][day*numSlots+slot] = (state == Qt::Checked);
    // 用于调试
    qDebug() << "Data updated:" << "S" << semester+1 << "W" << week+1 << "D" << day+1 << "S" << slot+1 << "=" << scheduleFreeTime[semester][week][day * numSlots + slot]<<"\n";
}


void NoClassTimeDialog::setupScheduleSelectors()
{

    // 填充下拉框内容
    for(int i=1;i<=numSemesters;i++) {
        ui->comboBox_semester->addItem(QString("第 %1 学期").arg(i),i-1); // 显示文本和存储的数据(索引)
    }

    for(int i=1;i<=numWeeks;i++) {
        ui->comboBox_week->addItem(QString("第 %1 周").arg(i),i-1); // 显示文本和存储的数据(索引)
    }

    // 连接信号与槽，更新下方状态表，当用户改变下拉框选择时，调用updateScheduleView
    connect(ui->comboBox_semester,&QComboBox::currentIndexChanged,this,&NoClassTimeDialog::updateScheduleView);
    connect(ui->comboBox_week,&QComboBox::currentIndexChanged,this,&NoClassTimeDialog::updateScheduleView);

    // 第一次显示界面
    updateScheduleView();
}

void NoClassTimeDialog::populateScheduleGrid(int semester, int week)
{
    // 先清空布局
    clearLayout(ui->scheduleGridLayout);

    // 先创建表头
    QStringList headers = {"一","二","三","四","五","六","日"};
    for(int day=0;day<numDays;day++) {
        QLabel* dayLabel = new QLabel(headers[day]);
        dayLabel->setAlignment(Qt::AlignCenter);
        ui->scheduleGridLayout->addWidget(dayLabel,0,day+1); // 对象，行，列
    }

    // 添加行头
    for(int slot=0;slot<numSlots;slot++) {
        QLabel* slotLabel = new QLabel(QString::number(slot+1));
        slotLabel->setAlignment(Qt::AlignCenter);
        ui->scheduleGridLayout->addWidget(slotLabel,slot+1,0); // 对象，行，列
    }

    // 创建7*13的选择框
    for(int day = 0;day<numDays;day++) {
        for(int slot=0;slot<numSlots;slot++) {
            // 创建复选框
            QCheckBox* checkbox = new QCheckBox();
            // 读取状态并设置
            bool isChecked = scheduleFreeTime[semester][week][day*numSlots+slot];
            checkbox->setChecked(isChecked);
            // 加入网格布局
            ui->scheduleGridLayout->addWidget(checkbox,slot+1,day+1);
            // 连接槽函数
            connect(checkbox,&QCheckBox::stateChanged,this,[this,semester,week,day,slot](int state){
                onScheduleCheckBoxStateChanged(state,semester,week,day,slot);
            });
        }
    }

}

void NoClassTimeDialog::clearLayout(QLayout *layout)
{
    // 空指针直接返回
    if(layout == nullptr) return;
    QLayoutItem* item = nullptr;
    // 从布局中移除第 0 个位置的子项（QLayoutItem*），并返回它。直到没有子项
    while((item = layout->takeAt(0)))
    {
        // 如果子项是布局
        if(item->layout()) {
            // 递归删除布局
            clearLayout(item->layout());
            // 删除布局对象
            delete item->layout();
        }
        // 如果子项是控件
        if(item->widget()) {
            // 安全删除控件
            item->widget()->deleteLater();
            // 删除子控件对象
            delete item;
        }
    }
}

