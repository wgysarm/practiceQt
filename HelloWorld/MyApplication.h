#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QObject>
#include <QTimer>



class MyApplication : public QObject
{
	Q_OBJECT

public:
	MyApplication(QObject *parent);
	~MyApplication();


public slots:
	void slotTimer(void);


private:
	QTimer *timer;
	
};

#endif // MYAPPLICATION_H
