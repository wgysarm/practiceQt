#include "MyDIP.h"
#include <QDebug>
#include <QFileDialog>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>

MyDIP::MyDIP(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.splitter_Left->setStretchFactor(0,5);
	ui.splitter_Left->setStretchFactor(1,1);
	ui.splitter_Right->setStretchFactor(0,5);
	ui.splitter_Right->setStretchFactor(1,1);
	
	imageLeft = NULL;
	imageRight = NULL;
	sceneLeft = NULL;
	sceneRight = NULL;

	QObject::connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(SlotsFileActionOpen()));
	QObject::connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(SlotsFileActionSave()));
	QObject::connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(SlotsFileActionClose()));
	QObject::connect(ui.actionLoad, SIGNAL(triggered()), this, SLOT(SlotOperateActionLoad()));
	QObject::connect(ui.actionGray, SIGNAL(triggered()), this, SLOT(SlotOperateActionGray()));

}

MyDIP::~MyDIP()
{
	
	if(imageRight != NULL)
	{
		free(imageRight->bits());
		//delete imageRight;
		qDebug() << "stand";
	}


}


void MyDIP::SlotsFileActionOpen()
{
	QString *selectFilter = new QString("*.jpg");
	QString filePath = QFileDialog::getOpenFileName(this, "open image file" , "../image/", "Image Files(*.jpg)");
	
	if(filePath == "")
	{

		return;
	}
	QImage imageL = QImage(filePath);
	sceneLeft = new QGraphicsScene(this);
	sceneLeft->addPixmap(QPixmap::fromImage(imageL));
	ui.graphicsView_Left->setScene(sceneLeft);
	//ui.graphicsView_Left->resize(imgeL.width()+10,imgeL.height()+10);
	ui.graphicsView_Left->show();

	QSize size = imageL.size();
	QImage::Format format = imageL.format();
	uchar *addressL  = imageL.bits();
	int sizeofImage = imageL.byteCount();
	int cntofLine = imageL.bytesPerLine();

	uchar *addressR = (uchar*)malloc(sizeofImage);
	int w = size.width();
	int h = size.height();

	ui.textBrowser_Left->append(QString("size of image is:%1 x %2").arg(size.width()).arg(size.height()));
	ui.textBrowser_Left->append(QString("format is:%1").arg(format));
	ui.textBrowser_Left->append(QString("image size byte: %1").arg(QString::number(sizeofImage)));
	ui.textBrowser_Left->append(QString("image bytes/line: %1").arg(QString::number(cntofLine)));
	ui.textBrowser_Left->append(QString("address: 0x%1").arg(QString::number((int)addressL),10));

	imageLeft = &imageL;

	memcpy(addressR, addressL,sizeofImage);


	imageRight = new QImage(addressR, w, h, format);

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

void MyDIP::SlotOperateActionLoad()
{
	if(imageRight == NULL)
	{
		qDebug("no input image!");
		return;
	}

	sceneRight = new QGraphicsScene(this);

	sceneRight->addPixmap(QPixmap::fromImage(*imageRight));
	
	ui.graphicsView_Right->setScene(sceneRight);

	ui.graphicsView_Right->show();
}


void MyDIP::SlotOperateActionGray()
{
	if(imageRight == NULL)
	{
		qDebug() << "no input image";
	}

	int w = imageRight->size().width();
	int h = imageRight->size().height();

	uchar *imageLinebits;

	for(int i = 0; i < h ; ++i )
	{
		imageLinebits = imageRight->scanLine(i);

		for(int j = 0; j < w; ++j)
		{
			//int r = imageLinebits[ j*4 + 2 ];
			//int g = imageLinebits[ j*4 + 1 ];
			//int b = imageLinebits[ j*4 + 0 ];
			//change r
			//if(imageLinebits[j*4 + 2] > 128)
			//{
			//	imageLinebits[j*4 + 2] = 0;
			//}
			//else
			//{
			//	imageLinebits[j*4 + 2] = 0;
			//}
			//change g
			//if(imageLinebits[j*4 + 1] > 128)
			//{
			//	imageLinebits[j*4 + 1] = 0;
			//}
			//else
			//{
			//	imageLinebits[j*4 + 1] = 0;
			//}
			//change b
			//if(imageLinebits[j*4 + 0] > 128)
			//{
			//	imageLinebits[j*4 + 0] = 0;
			//}
			//else
			//{
			//	imageLinebits[j*4 + 0] = 0;
			//}



			imageLinebits[j*4 + 2] = (imageLinebits[j*4 + 2] + imageLinebits[j*4 + 1] +imageLinebits[j*4 + 0])/3;
			imageLinebits[j*4 + 1] = (imageLinebits[j*4 + 2] + imageLinebits[j*4 + 1] +imageLinebits[j*4 + 0])/3;
			imageLinebits[j*4 + 0] = (imageLinebits[j*4 + 2] + imageLinebits[j*4 + 1] +imageLinebits[j*4 + 0])/3;

		}
	}

	
	sceneRight = new QGraphicsScene(this);
	sceneRight->addPixmap(QPixmap::fromImage(*imageRight));
	ui.graphicsView_Right->setScene(sceneRight);

	ui.graphicsView_Right->show();

}