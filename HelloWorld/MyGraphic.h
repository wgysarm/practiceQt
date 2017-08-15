#ifndef MYGRAPHIC_H
#define MYGRAPHIC_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>


class MyGraphic : public QWidget
{
	Q_OBJECT

public:
	MyGraphic(QWidget *parent);
	~MyGraphic();

	QGraphicsView *_view;
	QGraphicsScene *_scene;


	void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent *);


private:
	
};

#endif // MYGRAPHIC_H
