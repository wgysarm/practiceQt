#ifndef EVENTWIDGET_H
#define EVENTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QPaintEvent>
#include <QShowEvent>
#include <QHideEvent>
#include <QKeyEvent>


class EventWidget : public QWidget
{
	Q_OBJECT

public:
	EventWidget(QWidget *parent);
	~EventWidget();
	QLabel *label;
	QLineEdit *lineEdit;
	QTextEdit *textEdit;
	QHBoxLayout *hlayout;
	QVBoxLayout *vlayout;
	bool event(QEvent *);

private:

protected:
	void mousePressEvent(QMouseEvent *event);
	bool event(void);
	void closeEvent(QCloseEvent * ev);
	void showEvent(QShowEvent *ev);
	void hideEvent(QHideEvent *ev);
	void keyPressEvent(QKeyEvent *ev);
	void paintEvent(QPaintEvent *);


	
};

#endif // EVENTWIDGET_H
