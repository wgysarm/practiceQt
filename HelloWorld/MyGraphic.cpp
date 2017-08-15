#include "MyGraphic.h"

MyGraphic::MyGraphic(QWidget *parent)
	: QWidget(parent)
{
	_view = new QGraphicsView(this);
	_scene = new QGraphicsScene(this);

	_view->setScene(_scene);
	_scene->addLine(1,10,100,200,QPen(Qt::red));

}

MyGraphic::~MyGraphic()
{

}
void MyGraphic::paintEvent(QPaintEvent *ev)
{

}

void MyGraphic::resizeEvent(QResizeEvent *)
{
	_view->setGeometry(QRect(QPoint(0,0),size()));

}
