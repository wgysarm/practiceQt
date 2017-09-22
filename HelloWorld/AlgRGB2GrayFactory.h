#pragma once
#include "Algorithmfactory.h"

//�̳��Դ�����AlgorithmV��ʵ����һ���Ҷ�ת�����㷨����
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

