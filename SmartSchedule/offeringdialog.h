#ifndef OFFERINGDIALOG_H
#define OFFERINGDIALOG_H

#include <QDialog>
#include "util.h"
#include <QCheckBox>
#include <QList>
#include <QVector>
namespace Ui {
class OfferingDialog;
}

class OfferingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OfferingDialog(QWidget *parent = nullptr);
    ~OfferingDialog();

    // 用于数据传输
    void setOffering(const Offering &offering);
    Offering getOffering() const;

private:
    Ui::OfferingDialog *ui;

    // 将 int weeks 转换为18个复选框的状态
    void weeksToCheckBoxes(int weeks);

    // 将18个复选框的状态转换为 int weeks
    int checkBoxesToWeeks() const;

    // 将 开课时间 转换为7*13个复选框的状态
    void timesToCheckBoxes(const QVector<int> &times);

    // 将  7*13个复选框的状态 转换为 开课时间
    QVector<int> checkBoxesToTimes() const;

    // ... 存放18个周次和91个时间复选框指针的容器
    QList<QCheckBox*> m_weekCheckBoxes;
    QList<QList<QCheckBox*>> m_timeCheckBoxes;

    // 初始化函数
    void setupCheckBoxes();

    // 数据<->UI转换函数
    void offeringToUi(const Offering &offering);
    Offering uiToOffering() const;

};

#endif // OFFERINGDIALOG_H
