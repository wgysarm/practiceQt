
#include <iostream>
#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QCompleter>
#include <QStringList>
#include <QTranslator>
#include "helloworld.h"
#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QThread>

#include "MyWidget.h"
#include "EventWidget.h"
#include "MyPainter.h"
#include "MyGraphic.h"
#include "MyApplication.h"
#include "MyDialog.h"
#include "MyTCPCom.h"
#include "MyDIP.h"
#include "main.h"
#include "AlgorithmFactory.h"



#include <stdlib.h>
#include <crtdbg.h>
#define CRTDBG_MAP_ALLOC
#define New   new(_NORMAL_BLOCK, __FILE__, __LINE__) 
int testw(QApplication &a);
//int testc(QApplication &a);
int testc(void);

using namespace std;



class AlgorithmScale  :public AlgorithmV
{
public:
	int AlgorithmSay(QImage *imageSrc, QImage **imageDest);
};

int AlgorithmScale::AlgorithmSay(QImage *imageSrc, QImage **imageDest)
{
	qDebug() << " do Algorithm ScaleConvert!";
	return 0;
}





class AlgrithmScaleFactory :public AlgorithmFactory{
public:
	AlgorithmV* CreateAlgorithm()
	{
		return new AlgorithmScale();
	}
};




int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	/*翻译*/
	QTranslator translator;
	translator.load("myhello.qm");
	a.installTranslator(&translator);

	qDebug() << "main thread:" << QThread::currentThreadId();
	//_CrtDumpMemoryLeaks();
	return testw(a);
	//testc(a);
	//testc();
	//return a.exec();
	qDebug() << "what";
	//_CrtDumpMemoryLeaks();
	return 0;
}

int testw(QApplication &a)
{
	//MyTCPCom w(0);
	//HelloWorld w(0);
	//MyWidget w(0);
	//EventWidget w(0y
	//MyGraphic w(0);
	//MyDialog w(0);
	//MyApplication app(0);
	//MyPainter w(0);
	MyDIP w(0);
	//TestUI w(0);

	//a.sendEvent(&w,new QEvent(QEvent::User));
	//a.postEvent(&w,new QEvent(QEvent::User));
	//qDebug() << "a.sendEvent accomplished";


	//w.setWindowFlags(Qt::WindowFullscreenButtonHint/*&Qt::WindowCloseButtonHint*/);
	w.setWindowTitle(QObject::tr("Helleo,World"));

	//w.showMaximized();

	//d.setWindowTitle(QObject::tr("dialog"));

	//MyThread thread1(&w);

	//MyThreadObj threadObj(0);


	//QThread thread2(&w);

	//QThread thread3(&w);

	//threadObj.moveToThread(&thread2);

	//QObject::connect(&thread1, SIGNAL(finished()), &w, SLOT(SlotDebugPrint()));
	//QObject::connect(&thread1, SIGNAL(finished()), &thread1, SLOT(QObject::deleteLater()));
	////处理
	//QObject::connect(&thread2, SIGNAL(started()), &threadObj, SLOT(SlotProcessFuc()));
	////信号处理完成，发射sigFinished信号，线程退出
	//QObject::connect(&threadObj, SIGNAL(sigFinished()), &thread2, SLOT(quit()));
	//////信号处理类自我删除。
	//QObject::connect(&threadObj, SIGNAL(sigFinished()), &threadObj, SLOT(QObject::deleteLater()));
	//////线程退出，自我删除。
	//QObject::connect(&thread2, SIGNAL(finished()), &thread2, SLOT(QObject::deleteLater()));


	//thread1.start();
	//thread2.start();

	AlgrithmScaleFactory *ascale = new AlgrithmScaleFactory();
	AlgorithmV *algScale = ascale->CreateAlgorithm();
	algScale->AlgorithmSay(NULL, NULL);
	//AlgrithmScaleFactory ascale;

	QThread threadDIP(0);
	w.moveToThread(&threadDIP);
	threadDIP.start();

	w.show();
	//d.show();
	return a.exec();

}

//int testc(QApplication &a)
int testc(void)
{

	char *ch = New char;
	*ch = 27;
	//char array[20];
	////qDebug() << *ch;
	//qDebug() << array << endl;
	//qDebug() << &array << endl;
	//qDebug() << &array[20] << endl;

	//typedef int(array1)[20];
	//array1 a1 ;
	//qDebug() << a1 << endl;
	//qDebug() << &a1 << endl;
	//qDebug() << &a1[0] << "  " << &a1[1]  << endl;

	//array1 *p = &a1;
	//qDebug() << "p:" <<p ;
	//p++;
	//qDebug() << "p++:" << p << endl ;

	//int *p1 = (int *)a1;
	//qDebug() << p1;
	//p1++;
	//qDebug() << p1;
	qDebug() << "WHAT   " << ch ;


	system("pause");
	//return a.exec();
	_CrtDumpMemoryLeaks();
	return 0;
}

