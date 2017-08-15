#include "MyDialog.h"
#include <QDialog>
#include <QDebug>
#include <QMessageBox>

MyDialog::MyDialog(QWidget *parent)
	: QDialog(parent)
{
	pbOk = new QPushButton(this);
	pbCancel = new QPushButton(this);
	pbOpenFile = new QPushButton(this);
	vlayout = new QVBoxLayout(this);
	vlayout->addStretch(3);
	vlayout->addWidget(pbOk);
	vlayout->addWidget(pbCancel);
	vlayout->addWidget(pbOpenFile);
	vlayout->addStretch(3);

	pbOpenFile->setText(tr("open file"));
	pbOk->setText(tr("ok"));
	pbCancel->setText(tr("cancel"));

	this->setLayout(vlayout);

	QObject::connect(pbCancel,SIGNAL(clicked()), this, SLOT(slotCancel()));
	QObject::connect(pbOk, SIGNAL(clicked()), this, SLOT(slotOk()));
}

MyDialog::~MyDialog()
{

}
void MyDialog::slotExecOpen()
{
	QMessageBox::warning(this,"warning","you are going to open a file");

	this->exec();




	if(this->exec() == QDialog::Accepted)
	{
		qDebug() << "Accepted" ;
	}else if(this->exec() == QDialog::Rejected)
	{
		qDebug() << "Rejected" ;
	}

}

void MyDialog::slotOk(void)
{
	qDebug() << "accept";
	accept();
}

void MyDialog::slotCancel(void)
{
	qDebug() << "reject";
	reject();
}
