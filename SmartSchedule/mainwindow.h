#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTableWidget>
#include "noclasstimedialog.h"
#include "settingsdialog.h"
#include "coursemanagerdialog.h"
#include "util.h"
#include <QFileDialog>
#include <QMap>
#include <QColor>
#include <qcombobox.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


// 用于管理每个学期标签页内的所有控件
struct SemesterTabWidgets {
    QWidget* mainWidget;        // 容纳所有控件的父QWidget
    QComboBox* weekSelector;    // 周次选择下拉框
    QTableWidget* scheduleTable; // 课表
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_action_globalSettings_triggered(); // 弹出全局设置对话框

    void on_action_quit_triggered();  // 退出

    void on_action_noClassTime_triggered(); // 弹出无课时间对话框

    void on_action_save_triggered();   // 保存选课方案

    void on_action_load_triggered();   // 加载选课方案

    void on_action_generate_triggered();  // 生成选课方案

    void on_action_reset_triggered();  // 重置选课方案

    void on_action_loadCourses_triggered();  // 加载课程

    void on_action_viewCourses_triggered();  // 查看课程列表

    void on_action_saveCourses_triggered();  // 保存课程

    void onWeekChanged(int semesterIndex); // 新增的槽函数，响应周次变化

private:
    Ui::MainWindow *ui;

    // ui区
    void setupSemesterTabs(); // 初始化8个学期的Tab页
    void updateScheduleView(); // 更新课表视图
    void clearScheduleView(); // 清空课表视图

    // 数据存储区
    int m_totalCredits = 200;    // 总学分下限
    int m_semesterCreditsLimit = 40;  // 单学期学分上限
    QVector<QVector<QVector<bool>>> m_mainScheduleData; // 无课状态表
    QList<Course> m_allCourses; // 所有课程的列表
    QList<ScheduledCourse> m_generatedSchedule; // 生成的选课方案
    QMap<QString,Course> courseMap;   // 建立课程id到对象的映射

    // 表格控件列表，每个Tab页一个
    QList<SemesterTabWidgets> m_semesterTabs;



};
#endif // MAINWINDOW_H
