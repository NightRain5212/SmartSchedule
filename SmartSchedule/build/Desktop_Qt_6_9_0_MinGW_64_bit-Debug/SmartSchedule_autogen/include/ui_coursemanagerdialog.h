/********************************************************************************
** Form generated from reading UI file 'coursemanagerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURSEMANAGERDIALOG_H
#define UI_COURSEMANAGERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CourseManagerDialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *courseListGroupBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_search;
    QListView *listView_courses;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_addCourse;
    QPushButton *btn_deleteCourse;
    QGroupBox *detailsGroupBox;
    QGroupBox *groupBox_3;
    QPushButton *btn_saveCourseChanges;
    QWidget *widget1;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit_courseId;
    QLabel *label_2;
    QLineEdit *lineEdit_courseName;
    QLabel *label_3;
    QSpinBox *spinBox_credit;
    QWidget *widget2;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QLineEdit *lineEdit_required;
    QLabel *label_6;
    QLineEdit *lineEdit_prerequisites;
    QLabel *label_4;
    QLineEdit *lineEdit_semester;
    QGroupBox *groupBox;
    QWidget *widget3;
    QVBoxLayout *verticalLayout_2;
    QTableView *tableView_offerings;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_addOffering;
    QPushButton *btn_editOffering;
    QPushButton *btn_deleteOffering;

    void setupUi(QDialog *CourseManagerDialog)
    {
        if (CourseManagerDialog->objectName().isEmpty())
            CourseManagerDialog->setObjectName("CourseManagerDialog");
        CourseManagerDialog->resize(900, 591);
        buttonBox = new QDialogButtonBox(CourseManagerDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(540, 560, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        courseListGroupBox = new QGroupBox(CourseManagerDialog);
        courseListGroupBox->setObjectName("courseListGroupBox");
        courseListGroupBox->setGeometry(QRect(20, 10, 301, 531));
        widget = new QWidget(courseListGroupBox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 30, 258, 501));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_search = new QLineEdit(widget);
        lineEdit_search->setObjectName("lineEdit_search");

        verticalLayout->addWidget(lineEdit_search);

        listView_courses = new QListView(widget);
        listView_courses->setObjectName("listView_courses");

        verticalLayout->addWidget(listView_courses);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btn_addCourse = new QPushButton(widget);
        btn_addCourse->setObjectName("btn_addCourse");

        horizontalLayout->addWidget(btn_addCourse);

        btn_deleteCourse = new QPushButton(widget);
        btn_deleteCourse->setObjectName("btn_deleteCourse");

        horizontalLayout->addWidget(btn_deleteCourse);


        verticalLayout->addLayout(horizontalLayout);

        detailsGroupBox = new QGroupBox(CourseManagerDialog);
        detailsGroupBox->setObjectName("detailsGroupBox");
        detailsGroupBox->setEnabled(false);
        detailsGroupBox->setGeometry(QRect(330, 10, 551, 531));
        groupBox_3 = new QGroupBox(detailsGroupBox);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(20, 20, 521, 231));
        btn_saveCourseChanges = new QPushButton(groupBox_3);
        btn_saveCourseChanges->setObjectName("btn_saveCourseChanges");
        btn_saveCourseChanges->setGeometry(QRect(400, 200, 80, 18));
        widget1 = new QWidget(groupBox_3);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(10, 40, 191, 131));
        gridLayout = new QGridLayout(widget1);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_courseId = new QLineEdit(widget1);
        lineEdit_courseId->setObjectName("lineEdit_courseId");

        gridLayout->addWidget(lineEdit_courseId, 0, 1, 1, 1);

        label_2 = new QLabel(widget1);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_courseName = new QLineEdit(widget1);
        lineEdit_courseName->setObjectName("lineEdit_courseName");

        gridLayout->addWidget(lineEdit_courseName, 1, 1, 1, 1);

        label_3 = new QLabel(widget1);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        spinBox_credit = new QSpinBox(widget1);
        spinBox_credit->setObjectName("spinBox_credit");

        gridLayout->addWidget(spinBox_credit, 2, 1, 1, 1);

        widget2 = new QWidget(groupBox_3);
        widget2->setObjectName("widget2");
        widget2->setGeometry(QRect(230, 40, 271, 131));
        gridLayout_2 = new QGridLayout(widget2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget2);
        label_5->setObjectName("label_5");

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        lineEdit_required = new QLineEdit(widget2);
        lineEdit_required->setObjectName("lineEdit_required");

        gridLayout_2->addWidget(lineEdit_required, 0, 1, 1, 1);

        label_6 = new QLabel(widget2);
        label_6->setObjectName("label_6");

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        lineEdit_prerequisites = new QLineEdit(widget2);
        lineEdit_prerequisites->setObjectName("lineEdit_prerequisites");

        gridLayout_2->addWidget(lineEdit_prerequisites, 1, 1, 1, 1);

        label_4 = new QLabel(widget2);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        lineEdit_semester = new QLineEdit(widget2);
        lineEdit_semester->setObjectName("lineEdit_semester");

        gridLayout_2->addWidget(lineEdit_semester, 2, 1, 1, 1);

        groupBox = new QGroupBox(detailsGroupBox);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 260, 521, 251));
        widget3 = new QWidget(groupBox);
        widget3->setObjectName("widget3");
        widget3->setGeometry(QRect(10, 20, 501, 231));
        verticalLayout_2 = new QVBoxLayout(widget3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tableView_offerings = new QTableView(widget3);
        tableView_offerings->setObjectName("tableView_offerings");

        verticalLayout_2->addWidget(tableView_offerings);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        btn_addOffering = new QPushButton(widget3);
        btn_addOffering->setObjectName("btn_addOffering");

        horizontalLayout_2->addWidget(btn_addOffering);

        btn_editOffering = new QPushButton(widget3);
        btn_editOffering->setObjectName("btn_editOffering");

        horizontalLayout_2->addWidget(btn_editOffering);

        btn_deleteOffering = new QPushButton(widget3);
        btn_deleteOffering->setObjectName("btn_deleteOffering");

        horizontalLayout_2->addWidget(btn_deleteOffering);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(CourseManagerDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, CourseManagerDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, CourseManagerDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(CourseManagerDialog);
    } // setupUi

    void retranslateUi(QDialog *CourseManagerDialog)
    {
        CourseManagerDialog->setWindowTitle(QCoreApplication::translate("CourseManagerDialog", "Dialog", nullptr));
        courseListGroupBox->setTitle(QCoreApplication::translate("CourseManagerDialog", "\350\257\276\347\250\213\345\210\227\350\241\250", nullptr));
        btn_addCourse->setText(QCoreApplication::translate("CourseManagerDialog", "\346\226\260\345\242\236\350\257\276\347\250\213", nullptr));
        btn_deleteCourse->setText(QCoreApplication::translate("CourseManagerDialog", "\345\210\240\351\231\244\350\257\276\347\250\213", nullptr));
        detailsGroupBox->setTitle(QCoreApplication::translate("CourseManagerDialog", "\350\257\276\347\250\213\344\277\241\346\201\257\350\257\246\346\203\205", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("CourseManagerDialog", "\345\237\272\346\234\254\344\277\241\346\201\257", nullptr));
        btn_saveCourseChanges->setText(QCoreApplication::translate("CourseManagerDialog", "\344\277\235\345\255\230", nullptr));
        label->setText(QCoreApplication::translate("CourseManagerDialog", "\350\257\276\347\250\213ID", nullptr));
        label_2->setText(QCoreApplication::translate("CourseManagerDialog", "\350\257\276\347\250\213\345\220\215\347\247\260", nullptr));
        label_3->setText(QCoreApplication::translate("CourseManagerDialog", "\345\255\246\345\210\206", nullptr));
        label_5->setText(QCoreApplication::translate("CourseManagerDialog", "\350\257\276\347\250\213\346\200\247\350\264\250", nullptr));
        label_6->setText(QCoreApplication::translate("CourseManagerDialog", "\345\205\210\344\277\256\350\257\276\347\250\213", nullptr));
        label_4->setText(QCoreApplication::translate("CourseManagerDialog", "\345\274\200\350\257\276\345\255\246\346\234\237", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CourseManagerDialog", "\345\274\200\350\257\276\344\277\241\346\201\257", nullptr));
        btn_addOffering->setText(QCoreApplication::translate("CourseManagerDialog", "\346\267\273\345\212\240", nullptr));
        btn_editOffering->setText(QCoreApplication::translate("CourseManagerDialog", "\347\274\226\350\276\221", nullptr));
        btn_deleteOffering->setText(QCoreApplication::translate("CourseManagerDialog", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CourseManagerDialog: public Ui_CourseManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURSEMANAGERDIALOG_H
