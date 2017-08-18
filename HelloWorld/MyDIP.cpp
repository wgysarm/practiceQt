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
		//free(imageRight->bits());
		delete imageRight;
		qDebug() << "stand";
	}
	if(imageLeft != NULL)
	{
		//free(imageLeft->bits());
		delete imageLeft;
	}
}


void MyDIP::SlotsFileActionOpen()
{
	QString *selectFilter = new QString("*.jpg");
	QString filePath = QFileDialog::getOpenFileName(this, "open image file" , "./image/", "Image Files(*.jpg)");
	
	if(filePath == "")
	{

		return;
	}

	imageLeft = new QImage(filePath);
	sceneLeft = new QGraphicsScene(this);
	sceneLeft->addPixmap(QPixmap::fromImage(*imageLeft));
	ui.graphicsView_Left->setScene(sceneLeft);
	//ui.graphicsView_Left->resize(imgeL.width()+10,imgeL.height()+10);
	ui.graphicsView_Left->show();

	QSize size = imageLeft->size();
	QImage::Format format = imageLeft->format();
	uchar *addressL  = imageLeft->bits();
	int sizeofImage = imageLeft->byteCount();
	int cntofLine = imageLeft->bytesPerLine();

	int w = size.width();
	int h = size.height();

	ui.textBrowser_Left->append(QString("size of image is:%1 x %2").arg(size.width()).arg(size.height()));
	ui.textBrowser_Left->append(QString("format is:%1").arg(format));
	ui.textBrowser_Left->append(QString("image size byte: %1").arg(QString::number(sizeofImage)));
	ui.textBrowser_Left->append(QString("image bytes/line: %1").arg(QString::number(cntofLine)));
	ui.textBrowser_Left->append(QString("address: 0x%1").arg(QString::number((int)addressL),10));

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
	ui.textBrowser_Right->clear();
	QSize size = imageLeft->size();
	int sizeofImage = imageLeft->byteCount();
	uchar *addressL  = imageLeft->bits();
	uchar *addressR = (uchar*)malloc(sizeofImage);

	memcpy(addressR, addressL,sizeofImage);
	QImage::Format format = imageLeft->format();
	int w = size.width();
	int h = size.height();
	imageRight = new QImage(addressR, w, h, format);
	if(imageRight == NULL)
	{
		qDebug("no input image!");
		return;
	}

	sceneRight = new QGraphicsScene(this);
	sceneRight->addPixmap(QPixmap::fromImage(*imageRight));
	
	ui.graphicsView_Right->setScene(sceneRight);

	ui.graphicsView_Right->show();

	ui.textBrowser_Right->append("Image Load complete");

}


void MyDIP::SlotOperateActionGray()
{
	int i;
	ui.textBrowser_Right->clear();
	QSize size = imageLeft->size();
	int sizeofImage = imageLeft->byteCount();
	uchar *addressL = imageLeft->bits();
	uchar *addressR = (uchar*)malloc(sizeofImage) ;


	if(addressR == NULL || addressL == NULL)
	{
		return;
	}
	int wL = size.width();
	int hL = size.height();


	memcpy(addressR, addressL,sizeofImage);

	//imageRight = new QImage(addressR, wL, hL, QImage::Format_Indexed8);
	imageRight = new QImage(addressR, wL, hL, imageLeft->format());
	if(imageRight == NULL)
	{
		return;
	}

	if(imageLeft->allGray())
	{
		*imageRight = *imageLeft;
		return;
	}

	uchar *rgbImageData = imageLeft->bits();
	uchar *grayImageData = imageRight->bits();

	int widthRGB = imageLeft->bytesPerLine();
	int widthGray = imageRight->bytesPerLine();

	uchar *addressBackRGB = rgbImageData;
	uchar *addressBackGray = grayImageData;

	int w = imageRight->size().width();
	int h = imageRight->size().height();

	uchar *imageLinebits;

	for(int i = 0; i < h ; ++i )
	{
		imageLinebits = imageRight->scanLine(i);
		grayImageData = imageLinebits;

		for(int j = 0; j < w; ++j)
		{

			uchar r = imageLinebits[ j*4 + 2 ];
			uchar g = imageLinebits[ j*4 + 1 ];
			uchar b = imageLinebits[ j*4 + 0 ];
			*grayImageData++ = (uchar)(0.29900*r +0.58700*g + 0.11400*b);
			*grayImageData++ = (uchar)(0.29900*r +0.58700*g + 0.11400*b);
			*grayImageData++ = (uchar)(0.29900*r +0.58700*g + 0.11400*b);
			//grayImageData++;
			//uchar r = *rgbImageData++;
			//uchar g = *(rgbImageData++);
			//uchar b = *(rgbImageData++);
			//rgbImageData++;

			//*grayImageData = r;
			//*(grayImageData + 1) = g;
			//*(grayImageData + 2) = b;
			//grayImageData +=3;

			//*grayImageData = (uchar)(0.29900*r +0.58700*g + 0.11400*b);
			grayImageData++ ;
		} 
		//rgbImageData = addressBackRGB + widthRGB * i;
		//grayImageData = addressBackGray + widthGray * i;

	}
	
	sceneRight = new QGraphicsScene(this);
	sceneRight->addPixmap(QPixmap::fromImage(*imageRight));
	ui.graphicsView_Right->setScene(sceneRight);

	ui.graphicsView_Right->show();

	ui.textBrowser_Right->append("gray convert complete");
	ui.textBrowser_Right->append(QString("format:%1").arg(QString::number((imageRight->format()))));
	ui.textBrowser_Right->append(QString::number((imageRight->size().height())));
	ui.textBrowser_Right->append(QString::number((imageRight->size().width())));

}