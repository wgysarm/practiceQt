#include "EventWidget.h"
#include <QDebug>


EventWidget::EventWidget(QWidget *parent)
	: QWidget(parent)
{

}

EventWidget::~EventWidget()
{

}
bool EventWidget::event(QEvent *e)
{
	if(e->type() == QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonDblClick || e->type() == QEvent::MouseButtonRelease)
	{
		//do nothing
		qDebug() << "event deal";
		//return false;//or shield this event;
	}else if(e->type() == QEvent::User)
	{
		qDebug() << "QSend a message";
	}

	return QWidget::event(e);
}

void EventWidget::mousePressEvent(QMouseEvent *ev)
{
	if(ev->button() == Qt::RightButton)
		qDebug() << "press right button";
	else if(ev->button() == Qt::LeftButton)
		qDebug() << "press left button" ;
	else
		qDebug() << "unknown button";
}

void EventWidget::closeEvent(QCloseEvent * ev)
{

}
void EventWidget::showEvent(QShowEvent *ev)
{

}
void EventWidget::hideEvent(QHideEvent *ev)
{

}
void EventWidget::keyPressEvent(QKeyEvent *ev)
{

}
void EventWidget::paintEvent(QPaintEvent *)
{

}

