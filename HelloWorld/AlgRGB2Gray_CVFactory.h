#pragma once
#include "Algorithmfactory.h"

//继承纯虚类AlgotithmV，实例化一个算法工厂类，专门做灰度转换。

class AlgorithmGrayCV :public AlgorithmV
{
public:
	int AlgorithmSay(QImage *imageSrc, QImage **imageDest);
};



class AlgRGB2Gray_CVFactory :
	public AlgorithmFactory
{
public:
	AlgRGB2Gray_CVFactory(void);
	~AlgRGB2Gray_CVFactory(void);

	AlgorithmV *CreateAlgorithm(void);
};

