#pragma once
#include "Algorithmfactory.h"

//继承自纯虚类AlgorithmV，实例化一个灰度转换的算法工厂
class AlgorithmRGB2Gray   :public AlgorithmV
{
public:
	int AlgorithmSay(QImage *imageSrc, QImage **imageDest);
};





class AlgRGB2GrayFactory :
	public AlgorithmFactory
{
public:
	AlgRGB2GrayFactory(void);
	~AlgRGB2GrayFactory(void);
	AlgorithmV *CreateAlgorithm(void);
};

