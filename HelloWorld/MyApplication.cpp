#include "MyApplication.h"
#include <QDebug>

MyApplication::MyApplication(QObject *parent)
	: QObject(parent)
{
	timer = new QTimer(this);
	timer->setInterval(1000);
	//timer->singleShot(1000,this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));
	//timer->start();


}

MyApplication::~MyApplication()
{

}

void MyApplication::slotTimer(void)
{

	qDebug() << "timeout" ;
}

