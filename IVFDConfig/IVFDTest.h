#pragma once

//#define IVFDAPI _declspec(dllexport) 

class IVFDTest
{
public:
	IVFDTest(void);
	~IVFDTest(void);
	int devID;
	//IVFDAPI void  setDevID(int id);
	//IVFDAPI int  getDevID(void);
	void  setDevID(int id);
	int  getDevID(void);
};

