/********************************************************************************
** Form generated from reading UI file 'helloworld.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLOWORLD_H
#define UI_HELLOWORLD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HelloWorldClass
{
public:

    void setupUi(QWidget *HelloWorldClass)
    {
        if (HelloWorldClass->objectName().isEmpty())
            HelloWorldClass->setObjectName(QStringLiteral("HelloWorldClass"));
        HelloWorldClass->resize(600, 400);

        retranslateUi(HelloWorldClass);

        QMetaObject::connectSlotsByName(HelloWorldClass);
    } // setupUi

    void retranslateUi(QWidget *HelloWorldClass)
    {
        HelloWorldClass->setWindowTitle(QApplication::translate("HelloWorldClass", "HelloWorld", 0));
    } // retranslateUi

};

namespace Ui {
    class HelloWorldClass: public Ui_HelloWorldClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLOWORLD_H
