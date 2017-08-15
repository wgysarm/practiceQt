

#include <iostream>
#include "helloworld.h"
#include <QApplication>
#include <QObject>
#include <QDebug>
#include <QString>
#include <QCompleter>
#include <QStringList>
#include <QByteArray>



using namespace std;


HelloWorld::HelloWorld(QWidget *parent)
	: QWidget(parent)
{
	QStringList wordList;
	wordList << "alpha" << "omega" << "omicron" << "zeta";
	QCompleter completer(wordList, this);
	completer.setCaseSensitivity(Qt::CaseInsensitive);

	ui.setupUi(this);

	//fileAaction = new QAction("File",this);
	//menu = new QMenu(this);
	//menuBar = new QMenuBar(this);

	textEditInput = new QTextEdit(this);
	pbConfirm = new QPushButton(this);
	pbQuit = new QPushButton(this);
	pbFuncAddDialog = new QPushButton(this);
	lEdit = new QLineEdit(this);
	labelInput = new QLabel(this);

	vlayout = new QVBoxLayout(this);
	hlayout1 = new QHBoxLayout(this);
	hlayout2 = new QHBoxLayout(this);

	dialog = new MyDialog(this);
	dialog1 = new QDialog(this);
	pbConfirm->setText(tr("confirm"));
	pbQuit->setText(tr("quit"));
	pbFuncAddDialog->setText(tr("dialog"));
	labelInput->setText(tr("input"));
	textEditInput->setText(tr("what"));

	lEdit->setCompleter(&completer);

	//hlayout1->addWidget(pbConfirm);
	//hlayout1->addSpacing(30);
	//hlayout1->addWidget(pbQuit);
	//hlayout1->addSpacing(30);
	//hlayout1->addWidget(pbFuncAddDialog);
	//hlayout1->addStretch(4);


	hlayout2->addWidget(labelInput,1,Qt::AlignLeft);
	hlayout2->addSpacing(30);
	hlayout2->addWidget(lEdit,1,Qt::AlignLeft);
	hlayout2->addStretch(1);

	//vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);

	glayout = new QGridLayout(this);


	glayout->addWidget(pbConfirm,0,0);
	glayout->addWidget(pbQuit,0,1);
	glayout->addWidget(pbFuncAddDialog,0,2);
	glayout->setRowStretch(3,1);
	glayout->setColumnStretch(3,1);
	vlayout->addLayout(glayout);

	vlayout->addWidget(textEditInput,Qt::AlignCenter);

	QObject::connect(pbConfirm,SIGNAL(clicked()),this,SLOT(buttonConfirmClick()));
	QObject::connect(pbQuit,SIGNAL(clicked()),this,SLOT(close()));
	//QObject::connect(pbFuncAddDialog,SIGNAL(clicked()),dialog,SLOT(slotExecOpen()));
	QObject::connect(pbFuncAddDialog,SIGNAL(clicked()),this,SLOT(buttonCancleClick()));
	this->setLayout(vlayout);
	//this->addAction(fileAaction);
	
}

HelloWorld::~HelloWorld()
{

}

void HelloWorld::buttonConfirmClick(void)
{
	textEditInput->setText(tr("this time should be right"));
	qDebug() << textEditInput;
	QByteArray ba("中国人民解放");
	QString str("中中中");
	qDebug() << sizeof(ba);
	qDebug() << sizeof(str);
	qDebug() << ba.size();
	qDebug() << str.size();
	textEditInput->setText(QString::number(ba.size()).append("   ").append(QString::number(str.size())));


	qDebug() << "Confirm click  "<< endl;

}

void HelloWorld::buttonCancleClick(void)
{
	ui_dialog.setupUi(dialog1);
	dialog1->exec();
	dialog1->setWindowTitle("dialog1");
	
	qDebug() << "Cancel click   " << endl;
}


void HelloWorld::buttonQuitClick(void)
{
	this->close();
	qDebug() << "GetCode click   " << endl;
}