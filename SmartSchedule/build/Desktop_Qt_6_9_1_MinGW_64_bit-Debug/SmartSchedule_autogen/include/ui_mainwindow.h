/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_save;
    QAction *action_load;
    QAction *action_quit;
    QAction *action_globalSettings;
    QAction *action_noClassTime;
    QAction *action_generate;
    QAction *action_reset;
    QAction *action_loadCourses;
    QAction *action_viewCourses;
    QAction *action_saveCourses;
    QWidget *centralwidget;
    QTabWidget *mainTabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1100, 800);
        MainWindow->setMinimumSize(QSize(1100, 800));
        MainWindow->setMaximumSize(QSize(1100, 800));
        action_save = new QAction(MainWindow);
        action_save->setObjectName("action_save");
        action_load = new QAction(MainWindow);
        action_load->setObjectName("action_load");
        action_quit = new QAction(MainWindow);
        action_quit->setObjectName("action_quit");
        action_globalSettings = new QAction(MainWindow);
        action_globalSettings->setObjectName("action_globalSettings");
        action_noClassTime = new QAction(MainWindow);
        action_noClassTime->setObjectName("action_noClassTime");
        action_generate = new QAction(MainWindow);
        action_generate->setObjectName("action_generate");
        action_reset = new QAction(MainWindow);
        action_reset->setObjectName("action_reset");
        action_loadCourses = new QAction(MainWindow);
        action_loadCourses->setObjectName("action_loadCourses");
        action_viewCourses = new QAction(MainWindow);
        action_viewCourses->setObjectName("action_viewCourses");
        action_saveCourses = new QAction(MainWindow);
        action_saveCourses->setObjectName("action_saveCourses");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(1100, 800));
        centralwidget->setMaximumSize(QSize(1100, 800));
        mainTabWidget = new QTabWidget(centralwidget);
        mainTabWidget->setObjectName("mainTabWidget");
        mainTabWidget->setGeometry(QRect(20, 0, 1041, 736));
        tab = new QWidget();
        tab->setObjectName("tab");
        mainTabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        mainTabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1100, 17));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName("menu_3");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(action_save);
        menu->addAction(action_load);
        menu->addAction(action_quit);
        menu->addAction(action_loadCourses);
        menu->addAction(action_saveCourses);
        menu_2->addAction(action_globalSettings);
        menu_2->addAction(action_noClassTime);
        menu_3->addAction(action_generate);
        menu_3->addAction(action_reset);
        menu_3->addAction(action_viewCourses);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_save->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\346\226\271\346\241\210", nullptr));
        action_load->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\346\226\271\346\241\210", nullptr));
        action_quit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        action_globalSettings->setText(QCoreApplication::translate("MainWindow", "\345\205\250\345\261\200\344\270\216\345\255\246\345\210\206\350\256\276\347\275\256", nullptr));
        action_noClassTime->setText(QCoreApplication::translate("MainWindow", "\346\227\240\350\257\276\346\227\266\351\227\264\350\256\276\347\275\256", nullptr));
        action_generate->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\351\200\211\350\257\276\346\226\271\346\241\210", nullptr));
        action_reset->setText(QCoreApplication::translate("MainWindow", "\351\207\215\347\275\256\346\211\200\346\234\211", nullptr));
        action_loadCourses->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\350\257\276\347\250\213", nullptr));
        action_viewCourses->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\350\257\276\347\250\213\345\210\227\350\241\250", nullptr));
        action_saveCourses->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\350\257\276\347\250\213", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
