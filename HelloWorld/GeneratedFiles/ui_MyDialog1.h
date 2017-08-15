/********************************************************************************
** Form generated from reading UI file 'MyDialog1.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDIALOG1_H
#define UI_MYDIALOG1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hLayout;
    QSpacerItem *spacer;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *label;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->setWindowModality(Qt::NonModal);
        Dialog->resize(400, 300);
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 250, 351, 33));
        hLayout = new QHBoxLayout(layoutWidget);
        hLayout->setSpacing(6);
        hLayout->setObjectName(QStringLiteral("hLayout"));
        hLayout->setContentsMargins(0, 0, 0, 0);
        spacer = new QSpacerItem(31, 131, QSizePolicy::Minimum, QSizePolicy::Expanding);

        hLayout->addItem(spacer);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));

        hLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hLayout->addWidget(cancelButton);

        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 100, 54, 12));

        retranslateUi(Dialog);
        QObject::connect(okButton, SIGNAL(clicked()), Dialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        okButton->setText(QApplication::translate("Dialog", "OK", 0));
        cancelButton->setText(QApplication::translate("Dialog", "Cancel", 0));
        label->setText(QApplication::translate("Dialog", "\346\230\257\345\220\246\351\200\200\345\207\272\357\274\237", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDIALOG1_H
