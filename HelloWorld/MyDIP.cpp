#include "MyDIP.h"
#include <QDebug>
#include <QFileDialog>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QThread>
#include <QStyle>
#include <QVector>
#include <QMessageBox>
#include "AlgorithmFactory.h"
#include "AlgRGB2GrayFactory.h"
#include "ui_ScalerSet.h"
#include <AlgRGB2Gray_CVFactory.h>
#include <QLine>
#include <QtMath>

#pragma region construct
MyDIP::MyDIP(QWidget *parent)
	: QMainWindow(parent = 0)
{
	ui.setupUi(this);

	QTime dateTime = QTime::currentTime();
	ui.labelDate->setText(dateTime.toString());

	ui.splitter_Left->setStretchFactor(0,5);
	ui.splitter_Left->setStretchFactor(1,1);
	ui.splitter_Right->setStretchFactor(0,5);
	ui.splitter_Right->setStretchFactor(1,1);

	ui.pushButton_1->setText(tr("Mat2Image"));
	ui.pushButton_2->setText(tr("Image2Mat"));
	ui.pushButton_3->setText(tr("cvOpenImage"));
	ui.pushButton_4->setText(tr("cvBGR2Gray"));
	ui.pushButton_5->setText(tr("videoCapture"));
	ui.pushButton_6->setText(tr("threadBegin"));
	ui.pushButton_7->setText(tr("ImageClear"));
	ui.pushButton_8->setText(tr("ImageJianXian"));

	
	//imageLeft = NULL;
	imageLeft = new QImage("./image/Chrysanthemum.jpg");
	imageRight = NULL;
	//sceneLeft = NULL;
	sceneLeft = new QGraphicsScene(this);
	sceneLeft->addPixmap(QPixmap(QPixmap::fromImage(*imageLeft)));
	ui.graphicsView_Left->setScene(sceneLeft);
	sceneRight = NULL;
	timer = new QTimer(this);
	timer->setInterval(30);
	timer->start(100);
	counter = 0;

	timer_date = new QTimer(this);
	timer_date->setInterval(1000);
	timer_date->start(1000);

	QObject::connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(SlotsFileActionOpen()));
	QObject::connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(SlotsFileActionSave()));
	QObject::connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(SlotsFileActionClose()));
	QObject::connect(ui.actionLoad, SIGNAL(triggered()), this, SLOT(SlotOperateActionLoad()));
	QObject::connect(ui.actionGray, SIGNAL(triggered()), this, SLOT(SlotOperateActionGray()));
	QObject::connect(ui.actionFuzzy, SIGNAL(triggered()), this, SLOT(SlotOperateActionFuzzy()));
	QObject::connect(ui.actionScaler, SIGNAL(triggered()), this, SLOT(SlotOperateActionScaler()));
	QObject::connect(ui.actionBrightness, SIGNAL(triggered()), this, SLOT(SlotOperateActionBright()));


	QObject::connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(SlotButton1Clicked()));
	QObject::connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(SlotButton2Clicked()));
	QObject::connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(SlotButton3Clicked()));
	QObject::connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(SlotButton4Clicked()));
	QObject::connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(SlotButton5Clicked()));
	QObject::connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(SlotButton6Clicked()));
	QObject::connect(ui.pushButton_7, SIGNAL(clicked()), this, SLOT(SlotButton7Clicked()));
	QObject::connect(ui.pushButton_8, SIGNAL(clicked()), this, SLOT(SlotButton8Clicked()));

	QObject::connect(timer_date, SIGNAL(timeout()), this, SLOT(SlotGetCurrentTime()));


	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(SlotVplayTimer()));
	QObject::connect(this, SIGNAL(timerStop()), this, SLOT(SlotStopTimer()));
}

MyDIP::~MyDIP()
{
	
	if(imageRight != NULL)
	{
		delete imageRight;
		imageRight = NULL;
		qDebug() << "stand";
	}
	if(imageLeft != NULL)
	{
		delete imageLeft;
		imageLeft = NULL;
	}

	if(sceneLeft != NULL)
	{
		delete sceneLeft;
		sceneLeft = NULL;
	}
	if(sceneRight != NULL)
	{
		delete sceneRight;
		sceneRight = NULL;
	}


}
#pragma endregion construct

void MyDIP::resizeEvent(QResizeEvent *ev)
{
	qDebug() << "height = " << this->height() << "  width = " <<this->width();
	//ui.graphicsView_Left->resize(0.5*this->width()-30, 0.3*this->height());
	//ui.graphicsView_Right->resize(0.5*this->width()-30, 0.3*this->height());

	ui.splitter->resize(this->width()-20, this->height()-60);
	
}

void MyDIP::SlotsFileActionOpen()
{
	QString selectFilter("Image(*.jpg *.bmp)");
	QString filePath = QFileDialog::getOpenFileName(this, tr("open image file") , "./image/", selectFilter);
	
	if(filePath == "")
	{
		return;
	}

	imageLeft = new QImage(filePath);
	sceneLeft = new QGraphicsScene(this);
	if(imageLeft == NULL || sceneLeft == NULL)
	{
		return;
	}

	sceneLeft->addPixmap(QPixmap::fromImage(*imageLeft));
	ui.graphicsView_Left->setScene(sceneLeft);
	//ui.graphicsView_Left->resize(imgeL.width()+10,imgeL.height()+10);
	ui.graphicsView_Left->show();

	QVector<QString> formatV;
	formatV << "Format_Invalid" << "Format_Mono"  <<"Format_MonoLSB" << "Format_Indexed8" << "Format_RGB32" << "Format_ARGB32" << "Format_ARGB32_Premultiplied" << "Format_RGB16";

	QSize size = imageLeft->size();
	QImage::Format format = imageLeft->format();
	uchar *addressL  = imageLeft->bits();
	int sizeofImage = imageLeft->byteCount();
	int cntofLine = imageLeft->bytesPerLine();

	int w = size.width();
	int h = size.height();

	ui.textBrowser_Left->append(QString("size of image is:%1 x %2").arg(size.width()).arg(size.height()));
	ui.textBrowser_Left->append(QString("format is: %1").arg(formatV[format]));
	ui.textBrowser_Left->append(QString("image size byte: %1 k").arg(QString::number(sizeofImage/1024)));
	ui.textBrowser_Left->append(QString("image bytes/line: %1").arg(QString::number(cntofLine)));
	ui.textBrowser_Left->append(QString("address: 0x%1").arg(QString::number(ulong(addressL),16)));
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

	if(imageLeft == NULL)
	{
		QMessageBox messageBox;
		messageBox.setText("open file is null");
		messageBox.setWindowTitle("load a image file");
		messageBox.exec();
		return;
	}
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
	ui.textBrowser_Right->append(QString("the image size : %1 * %2 ").arg(QString::number(imageRight->width())).arg(QString::number(imageRight->height())));
}



#pragma region rgb2gray



void MyDIP::SlotOperateActionGray()
{
	int i;
	ui.textBrowser_Right->clear();
	if(imageLeft == NULL)
	{
		//qDebug() << "there is no image file input";
		QMessageBox messageBox(QMessageBox::Information, tr("open image fail"), tr("imageLeft is NULL"),
			QMessageBox::NoButton, 0,
			Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
		messageBox.exec();
		return;
	}
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

	QImage **pImgDest = (QImage **)malloc(sizeof(int));
	*pImgDest = imageRight;
	//AlgrithmScaleFactory *ascale = new AlgrithmScaleFactory();
	//AlgorithmV *algScale = ascale->CreateAlgorithm();
	//algScale->AlgorithmSay(NULL, NULL);

	AlgRGB2GrayFactory *agray = new AlgRGB2GrayFactory();
	AlgorithmV *algGray = agray->CreateAlgorithm();
	algGray->AlgorithmSay(imageLeft, pImgDest);

	sceneRight = new QGraphicsScene(this);
	sceneRight->addPixmap(QPixmap::fromImage(**pImgDest));
	//sceneRight->addPixmap(QPixmap::fromImage(*imageRight));
	ui.graphicsView_Right->setScene(sceneRight);

	ui.graphicsView_Right->show();


	if(pImgDest != NULL && *pImgDest !=NULL)
	{
		delete(*pImgDest);
		*pImgDest = NULL;
		free(pImgDest);
		pImgDest = NULL;
	}

	if(pImgDest != NULL)
	{
		free(pImgDest);
		pImgDest = NULL;
	}

	ui.textBrowser_Right->append("gray convert complete");
	ui.textBrowser_Right->append(QString("format:%1").arg(QString::number((imageRight->format()))));
	ui.textBrowser_Right->append(QString::number((imageRight->size().height())));
	ui.textBrowser_Right->append(QString::number((imageRight->size().width())));
	ui.textBrowser_Right->append(QString("Algorithm = qimage c++ version"));
}

#pragma endregion rgb2gray

#pragma region qt&cv
cv::Mat MyDIP::QImage2cvMat(QImage* image)
{
	cv::Mat mat;  
	qDebug() << image->format();  
	switch(image->format())  
	{  
	case QImage::Format_ARGB32:  
	case QImage::Format_RGB32:  
		mat = cv::Mat(image->height(), image->width(), CV_8UC4, (void*)image->constBits(), image->bytesPerLine());
		break;
	case QImage::Format_ARGB32_Premultiplied:  
		mat = cv::Mat(image->height(), image->width(), CV_8UC4, (void*)image->constBits(), image->bytesPerLine());  
		break;  
	case QImage::Format_RGB888:  
		mat = cv::Mat(image->height(), image->width(), CV_8UC3, (void*)image->constBits(), image->bytesPerLine());  
		break;  
	case QImage::Format_Indexed8:  
		mat = cv::Mat(image->height(), image->width(), CV_8UC1, (void*)image->constBits(), image->bytesPerLine());  
		break;  
	}  
	return mat; 

}
int MyDIP::cvMat2QImage1(const cv::Mat* mat /*in*/, QImage **img/*out*/)
{
	QImage **imgOut = img;

	// 8-bits unsigned, NO. OF CHANNELS = 1  
	if(mat->type() == CV_8UC1)  
	{  
		QImage *image = new QImage(mat->cols, mat->rows, QImage::Format_Indexed8);  
		// Set the color table (used to translate color indexes to qRgb values)  
		image->setColorCount(256);  
		for(int i = 0; i < 256; i++)  
		{  
			image->setColor(i, qRgb(i, i, i));  
		}  
		// Copy input Mat  
		uchar *pSrc = mat->data;  
		for(int row = 0; row < mat->rows; row ++)  
		{  
			uchar *pDest = image->scanLine(row);  
			memcpy(pDest, pSrc, mat->cols);  
			pSrc += mat->step;  
		} 
		*imgOut = image;
		return 0;  
	}  
	// 8-bits unsigned, NO. OF CHANNELS = 3  
	else if(mat->type() == CV_8UC3)  
	{  
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat->data;  
		// Create QImage with same dimensions as input Mat  
		QImage *image = new QImage(pSrc, mat->cols, mat->rows, mat->step, QImage::Format_RGB888);  
		if(image == NULL)
		{
			qDebug() << "image new failed";
			return 1;
		}
		image->rgbSwapped(); 
		*imgOut = image;

		return 0;
		//return image;
	}  
	else if(mat->type() == CV_8UC4)  
	{  
		qDebug() << "CV_8UC4";  
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat->data;  
		// Create QImage with same dimensions as input Mat  
		QImage *image = new QImage(pSrc, mat->cols, mat->rows, mat->step, QImage::Format_ARGB32);  
		//return image;
		image->copy();  
		*imgOut = image;
		return 0;
	}  
	else  
	{  
		qDebug() << "ERROR: Mat could not be converted to QImage.";  
		return 1;  
	}  
}
QImage MyDIP::cvMat2QImage(const cv::Mat& mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1  
	if(mat.type() == CV_8UC1)  
	{  
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);  
		// Set the color table (used to translate color indexes to qRgb values)  
		image.setColorCount(256);  
		for(int i = 0; i < 256; i++)  
		{  
			image.setColor(i, qRgb(i, i, i));  
		}  
		// Copy input Mat  
		uchar *pSrc = mat.data;  
		for(int row = 0; row < mat.rows; row ++)  
		{  
			uchar *pDest = image.scanLine(row);  
			memcpy(pDest, pSrc, mat.cols);  
			pSrc += mat.step;  
		}  
		return image;  
	}  
	// 8-bits unsigned, NO. OF CHANNELS = 3  
	else if(mat.type() == CV_8UC3)  
	{  
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat.data;  
		// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);  
		return image.rgbSwapped();  
		//return image;
	}  
	else if(mat.type() == CV_8UC4)  
	{  
		qDebug() << "CV_8UC4";  
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat.data;  
		// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);  
		//return image;
		return image.copy();  
	}  
	else  
	{  
		qDebug() << "ERROR: Mat could not be converted to QImage.";  
		return QImage();  
	}  
}

#pragma endregion qt&cv

void MyDIP::SlotButton1Clicked()
{
	qDebug("button 1 clicked, Mat2Image");
	QString filePath = QFileDialog::getOpenFileName(this, tr("open image"),"./image/","image *.jpg *.bmp");
	if(filePath == "")
	{
		qDebug("no image files exist");
		return;
	}
	Mat matImag = imread(filePath.toStdString());
	imshow("image Hydrangeas",matImag);
	imageLeft = new QImage(AlgorithmV::cvMat2QImage(matImag));
	waitKey();
	return;


}
void MyDIP::SlotButton2Clicked()
{
	qDebug("button 2 clicked ,Image2Mat");

}

void MyDIP::SlotButton3Clicked()
{
	qDebug("button3 clicked,open QImage in a cv window ");

	const char *imagename = "mat";

	if(imageLeft == NULL)
	{
		return;
	}

	Mat img = AlgorithmV::QImage2cvMat(imageLeft);

	imshow("img", img);

	waitKey();
	return ;
}

void MyDIP::SlotButton4Clicked()
{
	qDebug("button4 clicked,open QImage in a cv window ");
	ui.textBrowser_Right->clear();

	if(sceneRight == NULL)
	{
		sceneRight = new QGraphicsScene(this);
	}
	sceneRight->clear();

	const char *imagename = "mat";

	if(imageLeft == NULL)
	{
		QMessageBox messageBox;
		messageBox.setText(tr("imageLeft is NULL,please open a image"));
		messageBox.setWindowTitle("open image");
		messageBox.exec();
		return;
	}

	AlgRGB2Gray_CVFactory *agray2 = new AlgRGB2Gray_CVFactory();
	AlgorithmV *algGray2 = agray2->CreateAlgorithm();
	algGray2->AlgorithmSay(imageLeft, &imageRight);

	sceneRight->addPixmap(QPixmap::fromImage(*imageRight));
	if(ui.graphicsView_Right == NULL)
	{
		ui.graphicsView_Right = new QGraphicsView(this);
	}

	ui.graphicsView_Right->setScene(sceneRight);


	ui.textBrowser_Right->append("gray convert complete");
	ui.textBrowser_Right->append(QString("format:%1").arg(QString::number((imageRight->format()))));
	ui.textBrowser_Right->append(QString::number((imageRight->size().height())));
	ui.textBrowser_Right->append(QString::number((imageRight->size().width())));
	ui.textBrowser_Right->append(QString("Algorithm = cv version"));
	return ;
}

void MyDIP::SlotButton5Clicked()
{

	ui.actionGray->setDisabled(true);
	ui.actionLoad->setDisabled(true);
	ui.actionOpen->setDisabled(true);
	ui.actionPrint->setDisabled(true);
	ui.actionSave->setDisabled(true);
	ui.actionSave_as->setDisabled(true);

	Mat frame;
	bool statusStop = false;
	
	Mat canyFrame;

	int kernel_size = 3;  
	Mat kernel = Mat::ones(kernel_size,kernel_size,CV_32F)/(float)(kernel_size*kernel_size); 


	//QString filePath = QFileDialog::getOpenFileName(this, tr("get a image file"), "./video", tr("video files(*.avi *.mp4)"));
	QFileDialog fileDialog(this, tr("get a image file"), "./video", tr("video files(*.avi *.mp4)"));


	if(fileDialog.exec() == QFileDialog::Rejected)
	{
		ui.actionGray->setDisabled(false);
		ui.actionLoad->setDisabled(false);
		ui.actionOpen->setDisabled(false);
		ui.actionPrint->setDisabled(false);
		ui.actionSave->setDisabled(false);
		ui.actionSave_as->setDisabled(false);
		return;
	}else if(fileDialog.exec() == QFileDialog::Accepted)
	{

	}
	QString filePath = fileDialog.getOpenFileName(this, tr("open video"), "./video", tr("*.avi *.mp4"));
	//cvNamedWindow("Video Player");
	//VideoCapture capture("F:/work/cplusstudy/QtStudyHello/practiceQt/HelloWorld/video/video3.mp4");
	cv::VideoCapture capture(filePath.toStdString());
	
	if(!capture.isOpened())
	{
		qDebug("Movie open error");
		if(sceneRight != NULL)
		{
			delete sceneRight;
			sceneRight = NULL;
		}

		return ;
	}

	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
	qDebug() << tr("all Frame number is:") << totalFrameNumber << "frame" << endl;

	long frameToStart = 30;
	long frameCurrent = frameToStart;

	capture.set(CV_CAP_PROP_POS_FRAMES, frameToStart);

	long frameToStop = 207;

	double rate = capture.get(CV_CAP_PROP_FPS);

	sceneRight = new QGraphicsScene(this);
	sceneLeft = new QGraphicsScene(this);
	if(sceneRight == NULL || sceneLeft == NULL)
	{
		return;
	}

	QImage **imgDis = (QImage **)malloc(sizeof(int *));
	QImage **imgCap = (QImage **)malloc(sizeof(int *));

	*imgDis = (QImage *)malloc(sizeof(int *));
	*imgCap = (QImage *)malloc(sizeof(int *));

	if(imgDis == NULL || *imgDis == NULL || imgCap == NULL || *imgCap == NULL)
	{
		return;
	}

	if(sceneRight == NULL ||sceneLeft == NULL)
	{
		return;
	}


	QPixmap pixmapL, pixmapR;

	while(!statusStop)
	{
		if(!capture.read(frame))
		{
			capture.release();
			cv::destroyWindow("Video player");
			cv::destroyWindow("Extracted frame");
			return;

		}		

		Canny(frame, canyFrame, 50, 200);

		cvMat2QImage1(&canyFrame,imgDis) ;
		cvMat2QImage1(&frame,imgCap) ;

		imageRight = *imgDis;
		imageLeft =	*imgCap;
		//开始检测每一帧图像

		pixmapR = QPixmap::fromImage(*imageRight);
		pixmapL = QPixmap::fromImage(*imageLeft);
		QGraphicsPixmapItem *pitemR = sceneRight->addPixmap(pixmapR);//这一句话造成了内存泄漏,因为返回了一个指针，指向了再函数内部分配的空间。如果没有释放，就会造成内存泄漏。
		QGraphicsPixmapItem *pitemL = sceneLeft->addPixmap(pixmapL);

		ui.graphicsView_Right->setScene(sceneRight);
		ui.graphicsView_Right->show();

		ui.graphicsView_Left->setScene(sceneLeft);
		ui.graphicsView_Left->show();


		imshow(QString("Extracted frame %1").toStdString(),frame);  
		//imshow("Video player", canyFrame);
		qDebug() << "MyDIP thread is :"<<this->thread()->currentThreadId();
		waitKey(30);

		if(pitemL != NULL)//记得一定要释放，不然内存泄漏。
		{
			delete pitemL;
			pitemL = NULL;
		}
		if(pitemR != NULL)//记得一定要释放，不然内存泄漏。
		{
			delete pitemR;
			pitemR = NULL;
		}
	}

	capture.release();
	if(imgDis != NULL )
	{
		free(imgDis);
		imgDis = NULL;
	}

	if(imgCap != NULL)
	{
		free(imgCap);
		imgCap = NULL;
	}

	ui.actionGray->setDisabled(false);
	ui.actionLoad->setDisabled(false);
	ui.actionOpen->setDisabled(false);
	ui.actionPrint->setDisabled(false);
	ui.actionSave->setDisabled(false);
	ui.actionSave_as->setDisabled(false);
	return;
}

void MyDIP::SlotButton6Clicked()
{

}

void MyDIP::SlotButton7Clicked()
{
	if(this->imageRight == NULL || this->sceneRight == NULL)
	{
		QMessageBox messageBox;
		messageBox.setWindowTitle(tr("warn no image address"));
		messageBox.setText(QString(tr("no image file")));
		messageBox.exec();
		return;
	}
	sceneRight->clear();
	ui.graphicsView_Right->setScene(sceneRight);
	sceneRight = NULL;
	imageRight = NULL;
}
#pragma region jianxian
void MyDIP::SlotButton8Clicked()
{
	qDebug() << "Jianxian" ;

	if(imageLeft == NULL)
	{
		return;
	}

	sceneRight->clear();

	AlgRGB2Gray_CVFactory getGrayFV;
	QImage **img = (QImage**)malloc(sizeof(int*));
	getGrayFV.CreateAlgorithm()->AlgorithmSay(imageLeft,img);
	cv::Mat matimg = AlgorithmV::QImage2cvMat(*img);
	//cv::imshow("matImage",matimg);
	qint32 w = /*imageLeft*/(*img)->size().width();
	qint32 h = /*imageLeft*/(*img)->size().height();
	uchar *addressImage = (uchar *)/*imageLeft*/(*img)->bits();
	QImage::Format format = /*imageLeft*/(*img)->format();
	QImage *imageShow = new QImage(addressImage, w, h, format);//0xffRRGGBB
	uchar *addressDest = (uchar *)imageShow->bits();
	uchar *destTemp = addressDest;
	uchar *imgTemp = addressImage;
	//memcpy(addressImage, addressImage, imageLeft->byteCount());
	uchar *imageLinebits;

	if(sceneRight == NULL)
	{
		sceneRight = new QGraphicsScene(this);
	}

	for(int n = 0; n < 255; n++)
	{
		//addressDest = destTemp;
		//addressImage = imgTemp;
		for(int i = 0; i < h ; ++i )
		{
			//imageLinebits = imageShow->scanLine(i);
			//addressDest = imageLinebits;
			//for(int j = 0; j < w; ++j)
			//{
			//	uchar r = imageLinebits[ j*4 + 2 ];
			//	uchar g = imageLinebits[ j*4 + 1 ];
			//	uchar b = imageLinebits[ j*4 + 0 ];
			//	*addressDest++ = (uchar)((0.29900*r +0.58700*g + 0.11400*b)*(float)(n/50.00));
			//	*addressDest++ = (uchar)((0.29900*r +0.58700*g + 0.11400*b)*(float)(n/50.00));
			//	*addressDest++ = (uchar)((0.29900*r +0.58700*g + 0.11400*b)*(float)(n/50.00));
			//	addressDest++ ;
			//} 


			//qDebug() << (float)(n/50.00);
		}

		//ui.graphicsView_Right->show();
		//sceneRight->addPixmap(QPixmap(QPixmap::fromImage(**img/*imageShow*/)));
		//ui.graphicsView_Right->update();
		//QThread::msleep(50);
		sceneRight->addLine(QLine(QPoint(100,100), QPoint((100+100*qCos(360.00*n/255.00)),(100+100*qSin(360.00*n/255.00)))));
		ui.graphicsView_Right->setScene(sceneRight);
		QThread::msleep(25);

		//ui.graphicsView_Right->viewport()->repaint();
		ui.graphicsView_Right->viewport()->repaint();

	}
}

#pragma endregion jianxian

void MyDIP::SlotVplayTimer()
{
	qDebug() << QString("3 thread MyDIP %1").arg(counter) << QThread::currentThreadId();

	if(counter == 100)
	{
		emit timerStop();
		return;
	}
	counter ++;
	return;
}


#pragma region paintevent
void MyDIP::paintEvent(QPaintEvent *ev)
{
	//QPainter pt(ui.graphicsView_Right->viewport());

	//pt.setPen(Qt::red);
	//pt.drawLine(80, 100, 650, 500);
	ui.graphicsView_Right->setScene(sceneRight);
	ui.graphicsView_Right->show();
}
#pragma endregion paintevent

void MyDIP::SlotDebugPrint()
{
	qDebug() << "4 Thread finished"  << QThread::currentThreadId();
	return;
}

void MyDIP::SlotStopTimer()
{
	timer->stop();
	return;
}

void MyDIP::SlotGetCurrentTime()
{
	ui.labelDate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss dddd"));
	update();
}



#pragma region scaler
void MyDIP::SlotOperateActionScaler()
{
	qint32 w, h;

	if(imageLeft == NULL || imageRight == NULL)
	{
		QMessageBox message("Image not exist", "please open and load a image file",QMessageBox::Information,0,0,0);
		message.exec();

		return;
	}
	sceneRight->clear();

	//QDialog messageBox;
	//messageBox.setWindowTitle("test message");
	//messageBox.exec();

	QDialog *scalerDialog = new QDialog(this);
	Ui::ScalerForm *scalerForm = new Ui::ScalerForm();
	scalerForm->setupUi(scalerDialog);

	scalerForm->horizontalSliderHeight->setMaximum(imageLeft->height());
	scalerForm->horizontalSliderHeight->setMinimum(288);
	scalerForm->horizontalSliderWidth->setMaximum(imageLeft->width());
	scalerForm->horizontalSliderWidth->setMinimum(352);

	scalerForm->lineEditHeightSet->setText(QString(QString::number(288)));
	scalerForm->lineEditWidthSet->setText(QString(QString::number(352)));

	scalerForm->verticalSliderB->setDisabled(true);
	scalerForm->verticalSliderG->setDisabled(true);
	scalerForm->verticalSliderR->setDisabled(true);
	scalerForm->verticalSliderH->setDisabled(true);
	scalerForm->verticalSliderL->setDisabled(true);
	scalerForm->verticalSliderS->setDisabled(true);




	QObject::connect(scalerForm->horizontalSliderHeight, &QSlider::valueChanged, [&](){scalerForm->lineEditHeightSet->setText(QString::number(scalerForm->horizontalSliderHeight->value()));} );
	QObject::connect(scalerForm->horizontalSliderWidth, &QSlider::valueChanged, [&](){scalerForm->lineEditWidthSet->setText(QString::number(scalerForm->horizontalSliderWidth->value()));});

	QObject::connect(scalerForm->pushButtonConfirm, &QPushButton::clicked, [&](){w = scalerForm->lineEditWidthSet->text().toInt(); h = scalerForm->lineEditHeightSet->text().toInt();
	*imageRight = (*imageRight).scaled(w,h);sceneRight->addPixmap(QPixmap::fromImage(*imageRight));ui.graphicsView_Right->setScene(sceneRight);});

	QObject::connect(scalerDialog, &QDialog::destroyed, [&](){qDebug() << "ok";});

	//QObject::connect(scalerDialog, &QDialog::destroyed, [&](){	scalerDialog->accept();});
	scalerDialog->setWindowTitle("Scaler Set");
	scalerDialog->exec();

	if(scalerDialog != NULL)
	{
		delete scalerDialog;
		scalerDialog = NULL;
	}
	if(scalerForm != NULL)
	{
		delete scalerForm;
		scalerForm = NULL;
	}

	//

	return;
}

#pragma endregion scaler

void MyDIP::SlotOperateActionFuzzy()
{

}
//xxx

#pragma region bright

void MyDIP::SlotOperateActionBright()
{
	qint32 w, h;

	if(imageLeft == NULL || imageRight == NULL)
	{
		QMessageBox message("Image not exist", "please open and load a image file",QMessageBox::Information,0,0,0);
		message.exec();

		return;
	}
	sceneRight->clear();

	//QDialog messageBox;
	//messageBox.setWindowTitle("test message");
	//messageBox.exec();

	QDialog *scalerDialog = new QDialog(this);

	Ui::ScalerForm *scalerForm = new Ui::ScalerForm();
	scalerForm->setupUi(scalerDialog);

	scalerForm->horizontalSliderHeight->setDisabled(true);
	scalerForm->horizontalSliderWidth->setDisabled(true);
	scalerForm->lineEditHeightSet->setDisabled(true);
	scalerForm->lineEditWidthSet->setDisabled(true);


	scalerForm->horizontalSliderBright->setMaximum(255);
	scalerForm->horizontalSliderBright->setMinimum(0);
	scalerForm->lineEditBrightness->setText(QString("0"));
	scalerForm->verticalSliderB->setMaximum(255);
	scalerForm->verticalSliderB->setMinimum(0);

	scalerForm->verticalSliderG->setMaximum(255);
	scalerForm->verticalSliderG->setMinimum(0);
	scalerForm->verticalSliderR->setMaximum(255);
	scalerForm->verticalSliderR->setMinimum(0);
	scalerForm->verticalSliderB->setValue(0);
	scalerForm->verticalSliderG->setValue(0);
	scalerForm->verticalSliderR->setValue(0);
	//scalerForm->labelRGB->setText(QString("R:%1, G:%2, B:%3").arg(QString::number(scalerForm->verticalSliderR->value()))
	//															.arg(QString::number(scalerForm->verticalSliderG->value()))
	//															.arg(QString::number(scalerForm->verticalSliderB->value())));

	scalerForm->labelRGB->setText(QString("R:%1, G:%2, B:%3").arg(QString::number(scalerForm->verticalSliderR->value()))
																.arg(QString::number(scalerForm->verticalSliderG->value()))
																.arg(QString::number(scalerForm->verticalSliderB->value())));
	scalerForm->labeHSL->setText(QString("H:%1, S:%2, L:%3").arg(QString::number(scalerForm->verticalSliderH->value()))
																.arg(QString::number(scalerForm->verticalSliderS->value()))
																.arg(QString::number(scalerForm->verticalSliderL->value())));
	//QImage **imageNew = (QImage **)malloc(sizeof(QImage *));
	QImage img;

	int valAdj = scalerForm->lineEditBrightness->text().toInt();
	QObject::connect(scalerForm->horizontalSliderBright, &QSlider::valueChanged, [&](){scalerForm->lineEditBrightness->setText(QString::number(scalerForm->horizontalSliderBright->value()));
					valAdj = scalerForm->lineEditBrightness->text().toInt();
					//AlgorithmV::BrightnessAdjust(imageRight, valAdj, imageNew);
					img = AlgorithmV::BrightnessAdjust(imageRight, valAdj);
					qDebug() <<  scalerForm->lineEditBrightness->text();
					//if(imageNew != NULL && *imageNew != NULL)
					//{
						//sceneRight->addPixmap(QPixmap::fromImage(**imageNew));
						sceneRight->addPixmap(QPixmap::fromImage(img));
					//}
					ui.graphicsView_Right->setScene(sceneRight);});

	QObject::connect(scalerDialog, &QDialog::destroyed, [&](){qDebug() << "ok";});
	QObject::connect(scalerForm->pushButtonConfirm, &QPushButton::clicked, [&](){valAdj = scalerForm->lineEditBrightness->text().toInt();
						//AlgorithmV::BrightnessAdjust(imageRight, valAdj, imageNew);
						img = AlgorithmV::BrightnessAdjust(imageRight, valAdj);
						qDebug() <<  scalerForm->lineEditBrightness->text();
						//if(imageNew != NULL && *imageNew != NULL)
						//{
							//sceneRight->addPixmap(QPixmap::fromImage(**imageNew));
							sceneRight->addPixmap(QPixmap::fromImage(img));
						//}
						ui.graphicsView_Right->setScene(sceneRight);});

	QObject::connect(scalerForm->verticalSliderR, &QSlider::valueChanged,[&](){scalerForm->labelRGB->setText(QString("R%1, G%2, B%3").arg(QString::number(scalerForm->verticalSliderR->value())).
																							arg(QString::number(scalerForm->verticalSliderG->value())).arg(QString::number(scalerForm->verticalSliderB->value())));});
	QObject::connect(scalerForm->verticalSliderG, &QSlider::valueChanged,[&](){scalerForm->labelRGB->setText(QString("R%1, G%2, B%3").arg(QString::number(scalerForm->verticalSliderR->value())).
																							arg(QString::number(scalerForm->verticalSliderG->value())).arg(QString::number(scalerForm->verticalSliderB->value())));});
	QObject::connect(scalerForm->verticalSliderB, &QSlider::valueChanged,[&](){scalerForm->labelRGB->setText(QString("R%1, G%2, B%3").arg(QString::number(scalerForm->verticalSliderR->value())).
																							arg(QString::number(scalerForm->verticalSliderG->value())).arg(QString::number(scalerForm->verticalSliderB->value())));});

	int deltaR, deltaG, deltaB;
	QObject::connect(scalerForm->verticalSliderB, &QSlider::valueChanged,[&](){	deltaR = scalerForm->verticalSliderR->value();
																				deltaG = scalerForm->verticalSliderG->value();
																				deltaB = scalerForm->verticalSliderB->value();
																				img = AlgorithmV::RGBAdjust(imageRight, deltaR, deltaG, deltaB);
																				sceneRight->addPixmap(QPixmap::fromImage(img));
																				ui.graphicsView_Right->setScene(sceneRight);
																				});

	QObject::connect(scalerForm->verticalSliderG, &QSlider::valueChanged,[&](){	deltaR = scalerForm->verticalSliderR->value();
																				deltaG = scalerForm->verticalSliderG->value();
																				deltaB = scalerForm->verticalSliderB->value();
																				img = AlgorithmV::RGBAdjust(imageRight, deltaR, deltaG, deltaB);
																				sceneRight->addPixmap(QPixmap::fromImage(img));
																				ui.graphicsView_Right->setScene(sceneRight); 
																				});

	QObject::connect(scalerForm->verticalSliderR, &QSlider::valueChanged,[&](){	deltaR = scalerForm->verticalSliderR->value();
																				deltaG = scalerForm->verticalSliderG->value();
																				deltaB = scalerForm->verticalSliderB->value();
																				img = AlgorithmV::RGBAdjust(imageRight, deltaR, deltaG, deltaB);
																				sceneRight->addPixmap(QPixmap::fromImage(img));
																				ui.graphicsView_Right->setScene(sceneRight);
																				});



	QObject::connect(scalerForm->verticalSliderH, &QSlider::valueChanged,[&](){scalerForm->labeHSL->setText(QString("H%1, S%2, L%3").arg(QString::number(scalerForm->verticalSliderH->value())).
																							arg(QString::number(scalerForm->verticalSliderS->value())).arg(QString::number(scalerForm->verticalSliderL->value())));});
	QObject::connect(scalerForm->verticalSliderS, &QSlider::valueChanged,[&](){scalerForm->labeHSL->setText(QString("H%1, S%2, L%3").arg(QString::number(scalerForm->verticalSliderH->value())).
																							arg(QString::number(scalerForm->verticalSliderS->value())).arg(QString::number(scalerForm->verticalSliderL->value())));});
	QObject::connect(scalerForm->verticalSliderL, &QSlider::valueChanged,[&](){scalerForm->labeHSL->setText(QString("H%1, S%2, L%3").arg(QString::number(scalerForm->verticalSliderH->value())).
																							arg(QString::number(scalerForm->verticalSliderS->value())).arg(QString::number(scalerForm->verticalSliderL->value())));});

	int deltaH, deltaS, deltaL;
	QObject::connect(scalerForm->verticalSliderH, &QSlider::valueChanged,[&](){	deltaH = scalerForm->verticalSliderH->value();
																				deltaS = scalerForm->verticalSliderS->value();
																				deltaL = scalerForm->verticalSliderL->value();
																				img = AlgorithmV::SaturationAdjust(imageRight, deltaH, deltaS, deltaL);
																				sceneRight->addPixmap(QPixmap::fromImage(img));
																				ui.graphicsView_Right->setScene(sceneRight);
																				});

	QObject::connect(scalerForm->verticalSliderS, &QSlider::valueChanged,[&](){	deltaH = scalerForm->verticalSliderH->value();
																				deltaS = scalerForm->verticalSliderS->value();
																				deltaL = scalerForm->verticalSliderL->value();
																				img = AlgorithmV::SaturationAdjust(imageRight, deltaH, deltaS, deltaL);
																				sceneRight->addPixmap(QPixmap::fromImage(img));
																				ui.graphicsView_Right->setScene(sceneRight); 
																				});

	QObject::connect(scalerForm->verticalSliderL, &QSlider::valueChanged,[&](){	deltaH = scalerForm->verticalSliderH->value();
																				deltaS = scalerForm->verticalSliderS->value();
																				deltaL = scalerForm->verticalSliderL->value();
																				img = AlgorithmV::SaturationAdjust(imageRight, deltaH, deltaS, deltaL);
																				sceneRight->addPixmap(QPixmap::fromImage(img));
																				ui.graphicsView_Right->setScene(sceneRight);
																				});






	scalerDialog->setWindowTitle("Brightness Set");

	scalerDialog->exec();


	//if(*imageNew != NULL)
	//{
	//	delete *imageNew;
	//}

	//if(imageNew != NULL)
	//{
	//	free(imageNew);
	//}

	if(scalerDialog != NULL)
	{
		delete scalerDialog;
		scalerDialog = NULL;
	}
	if(scalerForm != NULL)
	{
		delete scalerForm;
		scalerForm = NULL;
	}

	//
	return;
}

#pragma endregion bright
