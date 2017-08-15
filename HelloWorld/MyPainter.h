#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QWidget>
#include <QPaintEvent>
#include <QVector>
#include <QMouseEvent>
#include <QPoint>


class MyPainter : public QWidget
{
	Q_OBJECT

public:
	MyPainter(QWidget *parent);
	~MyPainter();

	QVector<QPoint> _line;

private:
	void drawTest(void);
	void drawLine(void);

protected:
	void paintEvent(QPaintEvent *ev);

	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);

	
};

#endif // MYPAINTER_H
