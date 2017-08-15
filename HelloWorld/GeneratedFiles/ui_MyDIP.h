/********************************************************************************
** Form generated from reading UI file 'MyDIP.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDIP_H
#define UI_MYDIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyDIP
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyDIP)
    {
        if (MyDIP->objectName().isEmpty())
            MyDIP->setObjectName(QStringLiteral("MyDIP"));
        MyDIP->resize(400, 300);
        menuBar = new QMenuBar(MyDIP);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MyDIP->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyDIP);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyDIP->addToolBar(mainToolBar);
        centralWidget = new QWidget(MyDIP);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MyDIP->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MyDIP);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyDIP->setStatusBar(statusBar);

        retranslateUi(MyDIP);

        QMetaObject::connectSlotsByName(MyDIP);
    } // setupUi

    void retranslateUi(QMainWindow *MyDIP)
    {
        MyDIP->setWindowTitle(QApplication::translate("MyDIP", "MyDIP", 0));
    } // retranslateUi

};

namespace Ui {
    class MyDIP: public Ui_MyDIP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDIP_H
