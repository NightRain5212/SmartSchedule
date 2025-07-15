/********************************************************************************
** Form generated from reading UI file 'noclasstimedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOCLASSTIMEDIALOG_H
#define UI_NOCLASSTIMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NoClassTimeDialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *scheduleGridLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBox_semester;
    QLabel *label_2;
    QComboBox *comboBox_week;

    void setupUi(QDialog *NoClassTimeDialog)
    {
        if (NoClassTimeDialog->objectName().isEmpty())
            NoClassTimeDialog->setObjectName("NoClassTimeDialog");
        NoClassTimeDialog->resize(562, 567);
        buttonBox = new QDialogButtonBox(NoClassTimeDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(200, 520, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        groupBox = new QGroupBox(NoClassTimeDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(40, 20, 481, 451));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 80, 431, 351));
        scheduleGridLayout = new QGridLayout(gridLayoutWidget);
        scheduleGridLayout->setObjectName("scheduleGridLayout");
        scheduleGridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(groupBox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(40, 20, 311, 50));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox_semester = new QComboBox(widget);
        comboBox_semester->setObjectName("comboBox_semester");
        comboBox_semester->setMaxVisibleItems(10);

        gridLayout->addWidget(comboBox_semester, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        comboBox_week = new QComboBox(widget);
        comboBox_week->setObjectName("comboBox_week");
        comboBox_week->setMaxVisibleItems(500);

        gridLayout->addWidget(comboBox_week, 1, 1, 1, 1);


        retranslateUi(NoClassTimeDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, NoClassTimeDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, NoClassTimeDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(NoClassTimeDialog);
    } // setupUi

    void retranslateUi(QDialog *NoClassTimeDialog)
    {
        NoClassTimeDialog->setWindowTitle(QCoreApplication::translate("NoClassTimeDialog", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("NoClassTimeDialog", "\350\256\276\347\275\256\346\257\217\345\255\246\346\234\237\346\227\240\350\257\276\346\227\266\351\227\264", nullptr));
        label->setText(QCoreApplication::translate("NoClassTimeDialog", "\351\200\211\346\213\251\345\255\246\346\234\237", nullptr));
        label_2->setText(QCoreApplication::translate("NoClassTimeDialog", "\351\200\211\346\213\251\345\221\250\346\254\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NoClassTimeDialog: public Ui_NoClassTimeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOCLASSTIMEDIALOG_H
