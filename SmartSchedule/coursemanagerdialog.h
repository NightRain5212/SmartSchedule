#ifndef COURSEMANAGERDIALOG_H
#define COURSEMANAGERDIALOG_H

#include <QDialog>
#include "util.h"
#include "offeringdialog.h"
#include <QList>
#include <QVector>
#include <QStandardItemModel>

namespace Ui {
class CourseManagerDialog;
}

class CourseManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CourseManagerDialog(QWidget *parent = nullptr);
    ~CourseManagerDialog();

    // 用于数据传输
    void setCourseList(const QList<Course> &courses);
    QList<Course> getCourseList() const;

private slots:

    // 当在左侧列表中选择的课程变化时
    void onCourseSelectionChanged(const QModelIndex& cur,const QModelIndex& prev);

    // 课程管理按钮的槽函数
    void on_btn_addCourse_clicked();   // 添加课程
    void on_btn_deleteCourse_clicked();  // 删除课程
    void on_btn_saveCourseChanges_clicked(); // 保存课程信息

    // Offering管理按钮的槽函数
    void on_btn_addOffering_clicked();   // 添加开课信息
    void on_btn_editOffering_clicked();  // 编辑开课信息
    void on_btn_deleteOffering_clicked(); // 删除开课信息

    // 搜索框文本变化时的槽函数
    void on_lineEdit_search_textChanged(const QString &text);

private:
    Ui::CourseManagerDialog *ui;

    // 用于管理tableView 和 listView
    QStandardItemModel *m_courseModel;
    QStandardItemModel *m_offeringsModel;

    QList<Course> m_courses; // 对话框持有的数据副本
    QModelIndex m_currentCourseIndex; // 记录当前选中的课程

    // UI更新函数
    void setupModels(); // 初始化

    void connectSignals(); // 显式连接所有信号和槽，比自动连接更稳健

    void populateCourseList(); // 产生列表
    void displayCourseDetails(const Course &course);  // 显示右侧课程详情
    void displayOfferings(const QList<Offering> &offerings);  // 显示开课详情
    void clearDetails(); // 清空并禁用右侧面板

    // 辅助函数，将位掩码转为可读字符串
    QString weeksToSummary(int weeks) const;
    QString timesToSummary(const QVector<int>& times) const;
};

#endif // COURSEMANAGERDIALOG_H
