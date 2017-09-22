#include "AlgRGB2Gray_CVFactory.h"



int AlgorithmGrayCV::AlgorithmSay(QImage *imageSrc, QImage **imageDest)
{
	cv::Mat img = QImage2cvMat(imageSrc);
	cv::Mat grayImg ;
	cv::cvtColor(img, grayImg, CV_BGR2GRAY);
	AlgorithmV::cvMat2QImage1(&grayImg,imageDest);
	return 0;
}



AlgRGB2Gray_CVFactory::AlgRGB2Gray_CVFactory(void)
{
}


AlgRGB2Gray_CVFactory::~AlgRGB2Gray_CVFactory(void)
{
}


AlgorithmV *AlgRGB2Gray_CVFactory::CreateAlgorithm()
{
	return new AlgorithmGrayCV();
}