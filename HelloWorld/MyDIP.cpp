#include "MyDIP.h"
#include <QDebug>
#include <QFileDialog>
#include <QImage>

MyDIP::MyDIP(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.splitter_Left->setStretchFactor(0,5);
	ui.splitter_Left->setStretchFactor(1,1);
	ui.splitter_Right->setStretchFactor(0,5);
	ui.splitter_Right->setStretchFactor(1,1);


	QObject::connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(SlotsFileActionOpen()));
	QObject::connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(SlotsFileActionSave()));
	QObject::connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(SlotsFileActionClose()));

}

MyDIP::~MyDIP()
{
	



}


void MyDIP::SlotsFileActionOpen()
{

	QString filePath = QFileDialog::getOpenFileName(this, "open image file" , "../image/", "*.jpg,*.bmp");
	
	QImage imgeL = QImage(filePath);
	imageLeft = &imgeL;

	qDebug() << "Open"  << filePath;
}


void MyDIP::SlotsFileActionSave()
{

	qDebug() << "Save";
}

void MyDIP::SlotsFileActionClose()
{

	close();
}