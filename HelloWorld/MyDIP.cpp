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

	ui.pushButton_1->setText(tr("Mat2Image"));
	ui.pushButton_2->setText(tr("Image2Mat"));
	ui.pushButton_3->setText(tr("cvOpenImage"));
	ui.pushButton_4->setText(tr("cvBGR2Gray"));
	ui.pushButton_5->setText(tr("videoCapture"));

	
	imageLeft = NULL;
	imageRight = NULL;
	sceneLeft = NULL;
	sceneRight = NULL;

	QObject::connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(SlotsFileActionOpen()));
	QObject::connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(SlotsFileActionSave()));
	QObject::connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(SlotsFileActionClose()));
	QObject::connect(ui.actionLoad, SIGNAL(triggered()), this, SLOT(SlotOperateActionLoad()));
	QObject::connect(ui.actionGray, SIGNAL(triggered()), this, SLOT(SlotOperateActionGray()));

	QObject::connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(SlotButton3Clicked()));
	QObject::connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(SlotButton1Clicked()));
	QObject::connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(SlotButton2Clicked()));
	QObject::connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(SlotButton4Clicked()));
	QObject::connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(SlotButton5Clicked()));
	QObject::connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(SlotButton6Clicked()));
}

MyDIP::~MyDIP()
{
	
	if(imageRight != NULL)
	{
		//free(imageRight->bits());
		delete imageRight;
		imageRight = NULL;
		qDebug() << "stand";
	}
	if(imageLeft != NULL)
	{
		//free(imageLeft->bits());
		delete imageLeft;
		imageLeft = NULL;
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

	if(imageLeft == NULL)
	{
		qDebug()<<(tr("there is no source image file"));
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

}


void MyDIP::SlotOperateActionGray()
{
	int i;
	ui.textBrowser_Right->clear();
	if(imageLeft == NULL)
	{
		qDebug() << "there is no image file input";
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
			grayImageData++ ;
		} 

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

	imageLeft = new QImage(cvMat2QImage(matImag));


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

	Mat img = QImage2cvMat(imageLeft);

	imshow("img", img);

	waitKey();
	return ;
}

void MyDIP::SlotButton4Clicked()
{
	qDebug("button4 clicked,open QImage in a cv window ");

	const char *imagename = "mat";

	if(imageLeft == NULL)
	{
		return;
	}

	Mat img = QImage2cvMat(imageLeft);

	imshow("img", img);


	Mat grayImg ;
	cvtColor(img, grayImg, CV_BGR2GRAY);

	imshow("gray", grayImg);

	waitKey();
	return ;




}

void MyDIP::SlotButton5Clicked()
{

	Mat frame;
	bool statusStop = false;
	
	Mat canyFrame;

	int kernel_size = 3;  
	Mat kernel = Mat::ones(kernel_size,kernel_size,CV_32F)/(float)(kernel_size*kernel_size); 


	QString filePath = QFileDialog::getOpenFileName(this, "get a image file", "./video", "video file *.avi,*.mp4");


	cvNamedWindow("Video Player");
	//VideoCapture capture("F:/work/cplusstudy/QtStudyHello/practiceQt/HelloWorld/video/video3.mp4");
	VideoCapture capture(filePath.toStdString());
	
	if(!capture.isOpened())
	{
		qDebug("Movie open error");
		if(sceneRight != NULL)
		{
			delete sceneRight;
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

	QImage **imgDis = (QImage**)malloc(sizeof(int *));

	*imgDis = (QImage*)malloc(sizeof(int *));

	if(imgDis == NULL || *imgDis == NULL)
	{
		return;
	}

	if(sceneRight == NULL)
	{
		return;
	}


	QPixmap pixmap;

	while(!statusStop)
	{
		if(!capture.read(frame))
		{
			capture.release();
			cv::destroyWindow("Video player");
			cv::destroyWindow("Extracted frame");
			return;

		}
			
		cvMat2QImage1(&frame,imgDis) ;

		imageRight = *imgDis;

		pixmap = QPixmap::fromImage(*imageRight);
		sceneRight->addPixmap(pixmap);
		//ui.graphicsView_Right->setScene(sceneRight);
		//ui.graphicsView_Right->show();
		//开始检测每一帧图像
		imshow("Extracted frame",frame);  
		//filter2D(frame,frame,-1,kernel); 

		//Canny(frame, canyFrame, 50, 200);
		//imshow("Video player", canyFrame);
		//if(*imgDis != NULL)
		//{
		//	delete *imgDis;
		//	imgDis = NULL;
		//}

		waitKey(30);

	}

	capture.release();
	if(imgDis != NULL)
	{
		free(imgDis);
		imgDis = NULL;
	}
	waitKey(0);


	return;
}

void MyDIP::SlotButton6Clicked()
{

}

void MyDIP::SlotButton7Clicked()
{

}

void MyDIP::SlotButton8Clicked()
{

}