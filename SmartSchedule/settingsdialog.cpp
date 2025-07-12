#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setValues(int totalCredits, int semesterLimit)
{
    ui->spinBox_semesterCreditsLimit->setValue(semesterLimit);
    ui->spinBox_totalCredits->setValue(totalCredits);
}

int SettingsDialog::totalCredits() const
{
    return ui->spinBox_totalCredits->value();
}

int SettingsDialog::semesterCreditsLimit() const
{
    return ui->spinBox_semesterCreditsLimit->value();
}

