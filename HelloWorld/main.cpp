
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

int testw(QApplication &a);
int testc(QApplication &a);

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	/*翻译*/
	QTranslator translator;
	translator.load("myhello.qm");
	a.installTranslator(&translator);

	qDebug() << "main thread:" << QThread::currentThreadId();

	return testw(a);
	//testc();
	//return a.exec();

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



	w.show();
	//d.show();
	return a.exec();

}

int testc(QApplication &a)
{
	char array[20];
	qDebug() << array << endl;
	qDebug() << &array << endl;
	qDebug() << &array[20] << endl;

	typedef int(array1)[20];
	array1 a1 ;
	qDebug() << a1 << endl;
	qDebug() << &a1 << endl;
	qDebug() << &a1[0] << endl;

	array1 *p = &a1;
	qDebug() << p ;
	p++;
	qDebug() << p << endl ;

	int *p1 = (int *)a1;
	qDebug() << p1;
	p1++;
	qDebug() << p1;
	

	system("pause");
	return a.exec();

}

