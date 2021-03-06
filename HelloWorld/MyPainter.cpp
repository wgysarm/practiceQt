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
	drawLine();
}

void MyPainter::mousePressEvent(QMouseEvent *ev)
{
	QVector<QPoint> line;
	line.append(ev->pos());
	_lineLast = line;
	//update();
}
void MyPainter::mouseReleaseEvent(QMouseEvent *ev)
{
	_lines.append(_lineLast);
	//_line.append(ev->pos());
	//update();
}
void MyPainter::mouseMoveEvent(QMouseEvent *ev)
{
	_lineLast.append(ev->pos());
	repaint();
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
	for(int j =0; j < _lines.size(); j++)
	{
		for (i = 0 ; i < _lines.at(j).size()-1; i++)
		{
			p.drawLine(_lines.at(j).at(i),_lines.at(j).at(i+1));
		}
	}


	update();
	return;

}