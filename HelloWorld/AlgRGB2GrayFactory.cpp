#include "AlgRGB2GrayFactory.h"

#include <QColor>
#include <QRgb>


QImage* GrayConvert(QImage *origin)//w h,不能搞反，否则会溢出。
{
	if(origin == NULL)
	{
		return NULL;
	}
	int w = origin->width();
	int h = origin->height();
	int average;
	QImage *newImage = new QImage(w, h, QImage::Format_ARGB32);
	QColor oldColor;
	for(int i = 0; i < h; i++) 
	{
		//uchar *lineAddress = origin->scanLine(i);
		for (int j = 0; j < w; j++)
		{
			oldColor = QColor(origin->pixel(j,i));
			average = (oldColor.red() + oldColor.green() + oldColor.blue())/3;
			newImage->setPixel(j, i, qRgb(average, average, average));
		}
	}
	qDebug() << "pause";

	return newImage;
}

QImage* GrayConvert1(QImage *origin)
{
	uchar *rgbImageData = origin->bits();
	uchar *addressBackRGB = rgbImageData;
	int widthRGB = origin->bytesPerLine();
	
	uchar *imageLinebits;
	int w = origin->size().width();
	int h = origin->size().height();
	QImage *newImage = new QImage(w, h, QImage::Format_ARGB32);
	if(newImage == NULL)
	{
		return NULL;
	}

	uchar *grayImageData = newImage->bits();
	uchar *addressBackGray = grayImageData;

	for(int i = 0; i < h ; ++i )
	{
		imageLinebits = origin->scanLine(i);
		grayImageData = newImage->scanLine(i);
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
	return newImage;
}


QImage *GrayConvert2(QImage *oldImage)
{
	if(oldImage == NULL)
	{
		return NULL;
	}
	qint16 w = oldImage->width();
	qint16 h = oldImage->height();

	//QImage *newImage = new QImage(w, h, QImage::Format_ARGB32 );
	QImage *newImage = new QImage(w, h, QImage::Format_Indexed8);
	QVector<QRgb> ColorTable;
	for(int i = 0; i < 255; i++)
	{
		ColorTable.push_back(qRgb(i, i, i));
	}
	newImage->setColorTable(ColorTable);

	if(newImage == NULL)
	{
		return NULL;
	}

	QRgb *lineRgb;
//int widthGray = (*pImgDest)->bytesPerLine();
	for(int i = 0; i < h; i++)
	{
		lineRgb = (QRgb *)oldImage->scanLine(i);
		//uchar *lineGray = newImage->scanLine(i);
		for(int j = 0; j < w; j++)
		{
			int average = (qRed(lineRgb[j])+qGreen(lineRgb[j])+qBlue(lineRgb[j]))/3;
			//newImage->setPixel(j, i, qRgb(average, average, average));
			newImage->setPixel(j, i, average);
		}
	}

	return newImage;
}

int AlgorithmRGB2Gray::AlgorithmSay(QImage *imageSrc, QImage **imageDest)
{
	qDebug() << " do Algorithm GrayConvert!";

	QImage *pImgSrc = imageSrc;
	QImage **pImgDest = imageDest;

	if(pImgSrc == NULL || pImgDest == NULL)
	{
		return -1;
	}
	if(imageSrc->allGray())
	{
		*pImgDest = pImgSrc;
		return 1;
	}

	//*pImgDest = GrayConvert(pImgSrc);
	//*pImgDest = GrayConvert1(pImgSrc);
	*pImgDest = GrayConvert2(pImgSrc);
	return 0;
}





AlgRGB2GrayFactory::AlgRGB2GrayFactory(void)
{
}


AlgRGB2GrayFactory::~AlgRGB2GrayFactory(void)
{
}


AlgorithmV* AlgRGB2GrayFactory::CreateAlgorithm()
{
	return new AlgorithmRGB2Gray();
}
