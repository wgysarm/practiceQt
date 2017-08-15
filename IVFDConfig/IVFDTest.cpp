#include "StdAfx.h"
#include "IVFDTest.h"
#include <iostream>

using namespace std;


IVFDTest::IVFDTest(void)
{
	
	devID = 0;
}


IVFDTest::~IVFDTest(void)
{
}


void  IVFDTest::setDevID(int id)
{
	cout << "ivfd setDevID" << endl;
	this->devID = id;
}


int  IVFDTest::getDevID(void)
{
	cout << "ivfd getDevID" << endl;
	return devID;
}


