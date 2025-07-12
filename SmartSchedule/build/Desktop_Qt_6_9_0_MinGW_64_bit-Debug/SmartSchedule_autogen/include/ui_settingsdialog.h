/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinBox_totalCredits;
    QLabel *label_2;
    QSpinBox *spinBox_semesterCreditsLimit;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName("SettingsDialog");
        SettingsDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(SettingsDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        groupBox = new QGroupBox(SettingsDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(60, 40, 291, 181));
        widget = new QWidget(groupBox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 30, 231, 121));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBox_totalCredits = new QSpinBox(widget);
        spinBox_totalCredits->setObjectName("spinBox_totalCredits");
        spinBox_totalCredits->setMaximum(500);
        spinBox_totalCredits->setDisplayIntegerBase(10);

        gridLayout->addWidget(spinBox_totalCredits, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        spinBox_semesterCreditsLimit = new QSpinBox(widget);
        spinBox_semesterCreditsLimit->setObjectName("spinBox_semesterCreditsLimit");
        spinBox_semesterCreditsLimit->setMaximum(500);
        spinBox_semesterCreditsLimit->setDisplayIntegerBase(10);

        gridLayout->addWidget(spinBox_semesterCreditsLimit, 1, 1, 1, 1);


        retranslateUi(SettingsDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, SettingsDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, SettingsDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SettingsDialog", "\345\205\250\345\261\200\347\272\246\346\235\237", nullptr));
        label->setText(QCoreApplication::translate("SettingsDialog", "\347\233\256\346\240\207\346\200\273\345\255\246\345\210\206\344\270\213\351\231\220", nullptr));
        label_2->setText(QCoreApplication::translate("SettingsDialog", "\345\215\225\345\255\246\346\234\237\345\255\246\345\210\206\344\270\212\351\231\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
