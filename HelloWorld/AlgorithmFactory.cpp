#include "AlgorithmFactory.h"
#include <QColor>

AlgorithmFactory::AlgorithmFactory(void)
{


}

AlgorithmFactory::~AlgorithmFactory(void)
{


}



AlgorithmV::AlgorithmV()
{
	qDebug() << "AlgorithmV construct!" ;
}

AlgorithmV::~AlgorithmV()
{

}

cv::Mat AlgorithmV::QImage2cvMat(QImage* image)
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



int AlgorithmV::cvMat2QImage1(const cv::Mat* mat /*in*/, QImage **img/*out*/)
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


QImage AlgorithmV::cvMat2QImage(const cv::Mat& mat)
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
		return image.rgbSwapped();  //low copy
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
		return image.copy();  //deep copy
	}  
	else  
	{  
		qDebug() << "ERROR: Mat could not be converted to QImage.";  
		return QImage();  
	}  
}

#pragma region brightness
//
//int AlgorithmV::BrightnessAdjust(QImage *oldImage, int val, QImage **newImage)
//{
//	if(oldImage == NULL || newImage == NULL)
//	{
//		return -1;
//	}
//
//	if(val <-255 || val > 255)
//	{
//		return -2;
//	}
//	int w = oldImage->width();
//	int h = oldImage->height();
//	
//	QImage *img = new QImage(w, h, QImage::Format_ARGB32);
//	QRgb *lineOld;
//	QRgb *lineNew;
//	QColor oldColor;
//	qint32 r,g,b;
//	for( int i = 0; i < h; i++)
//	{
//		lineOld = (QRgb *)oldImage->scanLine(i);
//		lineNew = (QRgb *)img->scanLine(i);
//		for(int j = 0; j < w; j++)
//		{
//			r = qRed(lineOld[j]) + val;//qBound(0, qRed(lineOld[j]) + val, 255);
//			g = qGreen(lineOld[j]) + val;//qBound(0, qRed(lineOld[j]) + val, 255);
//			b = qBlue(lineOld[j]) + val;//qBound(0, qRed(lineOld[j]) + val, 255);
//			r = qBound(0, r, 255);
//			g = qBound(0, g, 255);
//			b = qBound(0, b, 255);
//			img->setPixel(j, i, qRgb(r, g, b));
//		}
//
//		//for(int j = 0; j < w; j++)
//		//{
//		//	oldColor = QColor(oldImage->pixel(j, i));
//		//	r = oldColor.red() + val;
//		//	g = oldColor.green() + val;
//		//	b = oldColor.blue() + val;
//
//		//	r = qBound(0, r, 255);
//		//	g = qBound(0, g, 255);
//		//	b = qBound(0, b, 255);
//		//	img->setPixel(j, i, qRgb(r, g, b));
//		//}
//
//
//
//	}
//	*newImage = img;
//	return 0;
//}


QImage AlgorithmV::BrightnessAdjust(QImage *oldImage, int val)
{
	if(oldImage == NULL )
	{
		exit(-1);
	}

	if(val <-255 || val > 255)
	{
		exit(-2);
	}
	int w = oldImage->width();
	int h = oldImage->height();

	QImage img(w, h, QImage::Format_ARGB32);
	QRgb *lineOld;
	QRgb *lineNew;
	QColor oldColor;
	qint32 r,g,b;
	for( int i = 0; i < h; i++)
	{
		lineOld = (QRgb *)oldImage->scanLine(i);
		lineNew = (QRgb *)img.scanLine(i);
		for(int j = 0; j < w; j++)
		{
			r = qRed(lineOld[j]) + val;//qBound(0, qRed(lineOld[j]) + val, 255);
			g = qGreen(lineOld[j]) + val;//qBound(0, qRed(lineOld[j]) + val, 255);
			b = qBlue(lineOld[j]) + val;//qBound(0, qRed(lineOld[j]) + val, 255);
			r = qBound(0, r, 255);
			g = qBound(0, g, 255);
			b = qBound(0, b, 255);
			img.setPixel(j, i, qRgb(r, g, b));
		}

		//for(int j = 0; j < w; j++)
		//{
		//	oldColor = QColor(oldImage->pixel(j, i));
		//	r = oldColor.red() + val;
		//	g = oldColor.green() + val;
		//	b = oldColor.blue() + val;

		//	r = qBound(0, r, 255);
		//	g = qBound(0, g, 255);
		//	b = qBound(0, b, 255);
		//	img->setPixel(j, i, qRgb(r, g, b));
		//}



	}
	return img;
}

QImage AlgorithmV::RGBAdjust(QImage *oldImage, int deltaR, int deltaG, int deltaB)
{
	if(oldImage == NULL )
	{
		exit(-1);
	}

	if(deltaR <-255 || deltaR > 255 || deltaG <-255 || deltaG > 255 || deltaB <-255 || deltaB > 255)
	{
		exit(-2);
	}
	int w = oldImage->width();
	int h = oldImage->height();

	QImage img(w, h, QImage::Format_ARGB32);
	QRgb *lineOld;
	QRgb *lineNew;
	QColor oldColor;
	qint32 r,g,b;
	for( int i = 0; i < h; i++)
	{
		lineOld = (QRgb *)oldImage->scanLine(i);
		lineNew = (QRgb *)img.scanLine(i);
		for(int j = 0; j < w; j++)
		{
			r = qRed(lineOld[j]) + deltaR;//qBound(0, qRed(lineOld[j]) + val, 255);
			g = qGreen(lineOld[j]) + deltaG;//qBound(0, qRed(lineOld[j]) + val, 255);
			b = qBlue(lineOld[j]) + deltaB;//qBound(0, qRed(lineOld[j]) + val, 255);
			r = qBound(0, r, 255);
			g = qBound(0, g, 255);
			b = qBound(0, b, 255);
			img.setPixel(j, i, qRgb(r, g, b));
		}

		//for(int j = 0; j < w; j++)
		//{
		//	oldColor = QColor(oldImage->pixel(j, i));
		//	r = oldColor.red() + val;
		//	g = oldColor.green() + val;
		//	b = oldColor.blue() + val;

		//	r = qBound(0, r, 255);
		//	g = qBound(0, g, 255);
		//	b = qBound(0, b, 255);
		//	img->setPixel(j, i, qRgb(r, g, b));
		//}



	}
	return img;
}


#pragma endregion brightness


#pragma region saturation

QImage AlgorithmV::SaturationAdjust(QImage *oldImage, int deltaH, int deltaS, int deltaL)
{
	if(oldImage == NULL)
	{
		exit(-1);
	}

	int w = oldImage->width();
	int h = oldImage->height();
	QImage img(w, h, QImage::Format_ARGB32);
	//if(img == NULL)
	//{
	//	return NULL;
	//}

	QColor colorRGB, colorHSL;
	int hue, satuation, lightness;

	for(int i = 0; i < h; i++)
	{

		for(int j = 0; j < w; j++)
		{
			colorRGB = QColor(oldImage->pixel(j, i));
			colorHSL = colorRGB.toHsl();
			hue = colorHSL.hue() + deltaH;
			satuation = colorHSL.saturation() + deltaS;
			lightness = colorHSL.lightness() + deltaL;
			hue = qBound(0, hue, 255);
			satuation = qBound(0, satuation, 255);
			lightness = qBound(0, lightness, 255);
			colorHSL.setHsl(hue, satuation, lightness);

			img.setPixel(j,i, qRgb(colorHSL.red(), colorHSL.green(), colorHSL.blue()));

		}

	}

	return img;
}

#pragma endregion saturation






