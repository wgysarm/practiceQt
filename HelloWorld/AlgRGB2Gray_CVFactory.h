#pragma once
#include "Algorithmfactory.h"

//�̳д�����AlgotithmV��ʵ����һ���㷨�����࣬ר�����Ҷ�ת����

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

