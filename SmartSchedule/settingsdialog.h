#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();


    // 数据接口
    void setValues(int totalCredits, int semesterLimit);
    int totalCredits() const;
    int semesterCreditsLimit() const;

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
