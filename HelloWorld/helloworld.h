#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <QtWidgets/QWidget>
#include "ui_helloworld.h"
#include "ui_MyDialog1.h"
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include "MyDialog.h"
#include <QDialog>
#include <QMenu>
#include <QMenuBar>
#include <QAction>


class HelloWorld : public QWidget
{
	Q_OBJECT

public:
	//QMenu *menu;
	//QMenuBar *menuBar;
	//QAction *fileAaction;
	QTextEdit *textEditInput ;
	QPushButton *pbConfirm;
	QPushButton *pbQuit;
	QPushButton *pbFuncAddDialog;
	QLineEdit *lEdit;
	QLabel *labelInput;


	
	QVBoxLayout *vlayout;
	QHBoxLayout *hlayout1;
	QHBoxLayout *hlayout2;
	QGridLayout *glayout;
	QDialog *dialog1;

	MyDialog *dialog;

public:
	HelloWorld(QWidget *parent = 0);
	~HelloWorld();

private:
	Ui::HelloWorldClass ui;
	Ui::Dialog ui_dialog;

public slots:
		void buttonConfirmClick(void);
		void buttonCancleClick(void);
		void buttonQuitClick(void);

};

#endif // HELLOWORLD_H
