#include "MyPainter.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>

MyPainter::MyPainter(QWidget *parent)
	: QWidget(parent)
{

}

MyPainter::~MyPainter()
{

}

void MyPainter::paintEvent(QPaintEvent *ev)
{
	//drawTest();
	drawLine();
	//repaint();
	//update();
}

void MyPainter::mousePressEvent(QMouseEvent *ev)
{
	_line.append(ev->pos());
	update();
}
void MyPainter::mouseReleaseEvent(QMouseEvent *ev)
{
	_line.append(ev->pos());
	update();
}
void MyPainter::mouseMoveEvent(QMouseEvent *ev)
{
	_line.append(ev->pos());
	update();
}

void MyPainter::drawTest()
{
	QPixmap pixmap(this->size());
	QPainter painter(&pixmap);

	painter.setPen(QColor("yellow"));
	painter.drawLine(10,10,200,100);
	painter.drawArc(100,200,100,100,0,180*16);

	painter.drawEllipse(QPoint(100,100),200,240);
	painter.setPen(Qt::DashLine);

	painter.drawText(QPoint(300,200),"hewlloo");
	painter.drawRect(QRect(40,60,100,60));

	painter.end();//this is very important

	painter.begin(this);//重新定义画布
	painter.drawPixmap(20,20,pixmap);//整体画一个PixMap

	qDebug() << "repaint" ;

	//update();
	return;
}


void MyPainter::drawLine()
{
	QPainter p(this);

	//QVector<QPoint>::iterator it ;
	//for(it = _line.begin(); it < _line.end(); it++)
	//{
	//	QPainter p(this);
	//	p.drawLine(*it,*it++);
	//}


	int i = 0 ;
	for (i = 0 ; i < _line.size()-1; i++)
	{
		p.drawLine(_line.at(i),_line.at(i+1));
	}

	update();
	return;

}