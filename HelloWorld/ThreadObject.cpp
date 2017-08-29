#include "ThreadObject.h"
#include <QDebug>


ThreadObject::ThreadObject(QObject *parent)
	: QObject(parent)
{
	qDebug() << "Construct ThreadObject:" << this->thread()->currentThread();
	QObject::connect(this, SIGNAL(sig_finished()), this, SLOT(SlotGetSingal()));
}

ThreadObject::~ThreadObject()
{
	
}

void ThreadObject::SlotProcessFunc()
{

	qDebug() << "ThreadObject : do Process" << this->thread()->currentThread();
	for(int i = 0 ; i <100 ; i++)
	{
		QThread::msleep(20);
	}

	emit sig_finished();
}


void ThreadObject::SlotGetSingal()
{
	qDebug() << "get a sigFinshed" << this->thread()->currentThread();

}
