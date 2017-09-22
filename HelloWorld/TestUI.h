#ifndef TESTUI_H
#define TESTUI_H

#include <QMainWindow>
#include "ui_MyListWidget.h"
#include "ui_helloworld.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>
#include <QLabel>


class TestUI : public QMainWindow
{
	Q_OBJECT

public:
	QTreeWidgetItem *treeItem1, *treeItem2;


	TestUI(QWidget *parent);

	QLabel *labelTab3;
	~TestUI();

private:
	Ui::MyListWidgetMainW ui;
	Ui::HelloWorldClass uiH;
signals:
	void SignalEmit(void);

	public slots:
		void SlotPrint(QTreeWidgetItem*, int);

		void SlotPrint1(void);
		void SlotPrintListWidget(QListWidgetItem*);
};

#endif // TESTUI_H
