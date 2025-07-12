#ifndef NOCLASSTIMEDIALOG_H
#define NOCLASSTIMEDIALOG_H

#include <QDialog>

const int numSemesters = 8;
const int numWeeks = 18;
const int numDays = 7;
const int numSlots = 13;


namespace Ui {
class NoClassTimeDialog;
}

class NoClassTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoClassTimeDialog(QWidget *parent = nullptr);
    ~NoClassTimeDialog();

    // 用于数据传输

    // 设置初始数据
    void setScheduleData(const QVector<QVector<QVector<bool>>> &data);
    // 获取最终数据
    QVector<QVector<QVector<bool>>> scheduleData() const;


private slots:


    /** 每学期无课时间控制器 */

    // 当下拉框选择改变时，更新格子
    void updateScheduleView();

    // 当复选框被点击时更新数据
    void onScheduleCheckBoxStateChanged(int state,int semester,int week,int day,int slot);



private:
    Ui::NoClassTimeDialog *ui;

    /** 左侧每学期无课时间控制器 */

    // 用于生成UI

    // 初始化UI
    void setupScheduleSelectors();

    // 用于产生格子
    void populateScheduleGrid(int semester, int week);

    // 清空格子
    void clearLayout(QLayout* layout);

    // 多维数组用于存放数据，存储无课状态[8*18*7*13][学期][周次][天*13 + 课次]
    QVector<QVector<QVector<bool>>> scheduleFreeTime;
};

#endif // NOCLASSTIMEDIALOG_H
