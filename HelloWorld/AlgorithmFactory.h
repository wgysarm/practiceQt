#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QDebug>
#include <QImage>
//定义了一个纯虚类，必须通过继承实例化
class AlgorithmV{
public:
	AlgorithmV();
	~AlgorithmV();
	QImage static cvMat2QImage(const cv::Mat& mat);
	cv::Mat static QImage2cvMat(QImage *image);
	int static cvMat2QImage1(const cv::Mat* mat /*in*/, QImage **img/*out*/);
	virtual int AlgorithmSay(QImage *imageSrc/*in*/, QImage **imageDest) = 0;
	//int static BrightnessAdjust(QImage *oldImage, int val, QImage **newImage);
	QImage static BrightnessAdjust(QImage *oldImage, int val);
	QImage static SaturationAdjust(QImage *oldImage, int deltaH, int deltaS, int deltaL);
	QImage static RGBAdjust(QImage *oldImage, int deltaR, int deltaG, int deltaB);


protected:

private:
};


class AlgorithmFactory
{
public:
	AlgorithmFactory(void);
	~AlgorithmFactory(void);

	virtual AlgorithmV* CreateAlgorithm(void) =0;

};

