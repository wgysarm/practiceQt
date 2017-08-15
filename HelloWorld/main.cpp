
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
#include <qDebug>

#include "MyWidget.h"
#include "EventWidget.h"
#include "MyPainter.h"
#include "MyGraphic.h"
#include "MyApplication.h"
#include "MyDialog.h"
#include "MyTCPCom.h"
#include "MyDIP.h"

int testw(QApplication &a);
void testc(void);

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	/*З­вы*/
	QTranslator translator;
	translator.load("myhello.qm");
	a.installTranslator(&translator);
	return testw(a);

	//testc();
	return a.exec();

}

int testw(QApplication &a)
{
	//MyTCPCom w(0);
	//HelloWorld w(0);
	//MyWidget w(0);
	//EventWidget w(0y
	//MyGraphic w(0);
	//MyDialog d(0);
	//MyApplication app(0);
	MyDIP w(0);
	//a.sendEvent(&w,new QEvent(QEvent::User));
	//a.postEvent(&w,new QEvent(QEvent::User));
	//qDebug() << "a.sendEvent accomplished";

	w.setWindowTitle(QObject::tr("Helleo,World"));
	//d.setWindowTitle(QObject::tr("dialog"));
	w.show();
	//d.show();
	return a.exec();

}

void testc()
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
	return;

}

