/********************************************************************************
** Form generated from reading UI file 'MyTCPCom.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYTCPCOM_H
#define UI_MYTCPCOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyTCPCom
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionConnect;
    QAction *actionSet;
    QAction *actionSave;
    QWidget *centralWidget;
    QGroupBox *groupBoxLeft;
    QRadioButton *radioButtonLeft1;
    QCheckBox *checkBoxLeft1;
    QCheckBox *checkBoxLeft2;
    QRadioButton *radioButtonLeft2;
    QGroupBox *groupBoxRight;
    QRadioButton *radioButtonRight2;
    QCheckBox *checkBoxRight1;
    QCheckBox *checkBoxRight2;
    QRadioButton *radioButtonRight1;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOperate;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyTCPCom)
    {
        if (MyTCPCom->objectName().isEmpty())
            MyTCPCom->setObjectName(QStringLiteral("MyTCPCom"));
        MyTCPCom->resize(566, 526);
        actionOpen = new QAction(MyTCPCom);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionClose = new QAction(MyTCPCom);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionConnect = new QAction(MyTCPCom);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionSet = new QAction(MyTCPCom);
        actionSet->setObjectName(QStringLiteral("actionSet"));
        actionSave = new QAction(MyTCPCom);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        centralWidget = new QWidget(MyTCPCom);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBoxLeft = new QGroupBox(centralWidget);
        groupBoxLeft->setObjectName(QStringLiteral("groupBoxLeft"));
        groupBoxLeft->setGeometry(QRect(100, 170, 201, 80));
        radioButtonLeft1 = new QRadioButton(groupBoxLeft);
        radioButtonLeft1->setObjectName(QStringLiteral("radioButtonLeft1"));
        radioButtonLeft1->setGeometry(QRect(20, 30, 89, 16));
        checkBoxLeft1 = new QCheckBox(groupBoxLeft);
        checkBoxLeft1->setObjectName(QStringLiteral("checkBoxLeft1"));
        checkBoxLeft1->setGeometry(QRect(120, 30, 71, 16));
        checkBoxLeft2 = new QCheckBox(groupBoxLeft);
        checkBoxLeft2->setObjectName(QStringLiteral("checkBoxLeft2"));
        checkBoxLeft2->setGeometry(QRect(120, 50, 71, 16));
        radioButtonLeft2 = new QRadioButton(groupBoxLeft);
        radioButtonLeft2->setObjectName(QStringLiteral("radioButtonLeft2"));
        radioButtonLeft2->setGeometry(QRect(20, 50, 89, 16));
        groupBoxRight = new QGroupBox(centralWidget);
        groupBoxRight->setObjectName(QStringLiteral("groupBoxRight"));
        groupBoxRight->setGeometry(QRect(330, 160, 191, 80));
        radioButtonRight2 = new QRadioButton(groupBoxRight);
        radioButtonRight2->setObjectName(QStringLiteral("radioButtonRight2"));
        radioButtonRight2->setGeometry(QRect(20, 50, 89, 16));
        checkBoxRight1 = new QCheckBox(groupBoxRight);
        checkBoxRight1->setObjectName(QStringLiteral("checkBoxRight1"));
        checkBoxRight1->setGeometry(QRect(120, 30, 71, 16));
        checkBoxRight2 = new QCheckBox(groupBoxRight);
        checkBoxRight2->setObjectName(QStringLiteral("checkBoxRight2"));
        checkBoxRight2->setGeometry(QRect(120, 50, 71, 16));
        radioButtonRight1 = new QRadioButton(groupBoxRight);
        radioButtonRight1->setObjectName(QStringLiteral("radioButtonRight1"));
        radioButtonRight1->setGeometry(QRect(20, 30, 89, 16));
        MyTCPCom->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyTCPCom);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 566, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOperate = new QMenu(menuBar);
        menuOperate->setObjectName(QStringLiteral("menuOperate"));
        MyTCPCom->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyTCPCom);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyTCPCom->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MyTCPCom);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyTCPCom->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuOperate->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionClose);
        menuOperate->addAction(actionConnect);
        menuOperate->addAction(actionSet);

        retranslateUi(MyTCPCom);

        QMetaObject::connectSlotsByName(MyTCPCom);
    } // setupUi

    void retranslateUi(QMainWindow *MyTCPCom)
    {
        MyTCPCom->setWindowTitle(QApplication::translate("MyTCPCom", "MyTCPCom", 0));
        actionOpen->setText(QApplication::translate("MyTCPCom", "Open", 0));
        actionClose->setText(QApplication::translate("MyTCPCom", "Close", 0));
        actionConnect->setText(QApplication::translate("MyTCPCom", "Connect", 0));
        actionSet->setText(QApplication::translate("MyTCPCom", "Set", 0));
        actionSave->setText(QApplication::translate("MyTCPCom", "Save", 0));
        groupBoxLeft->setTitle(QApplication::translate("MyTCPCom", "GroupBox", 0));
        radioButtonLeft1->setText(QApplication::translate("MyTCPCom", "RadioButton", 0));
        checkBoxLeft1->setText(QApplication::translate("MyTCPCom", "CheckBox", 0));
        checkBoxLeft2->setText(QApplication::translate("MyTCPCom", "CheckBox", 0));
        radioButtonLeft2->setText(QApplication::translate("MyTCPCom", "RadioButton", 0));
        groupBoxRight->setTitle(QApplication::translate("MyTCPCom", "GroupBox", 0));
        radioButtonRight2->setText(QApplication::translate("MyTCPCom", "RadioButton", 0));
        checkBoxRight1->setText(QApplication::translate("MyTCPCom", "CheckBox", 0));
        checkBoxRight2->setText(QApplication::translate("MyTCPCom", "CheckBox", 0));
        radioButtonRight1->setText(QApplication::translate("MyTCPCom", "RadioButton", 0));
        menuFile->setTitle(QApplication::translate("MyTCPCom", "File", 0));
        menuOperate->setTitle(QApplication::translate("MyTCPCom", "Operate", 0));
    } // retranslateUi

};

namespace Ui {
    class MyTCPCom: public Ui_MyTCPCom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYTCPCOM_H
