#ifndef MYDIP_H
#define MYDIP_H

#include <QMainWindow>
#include "ui_MyDIP.h"
#include <QImage>

class MyDIP : public QMainWindow
{
	Q_OBJECT

public:
	MyDIP(QWidget *parent = 0);
	~MyDIP();

	
	
public slots:
	void SlotsFileActionOpen(void);
	void SlotsFileActionSave(void);
	void SlotsFileActionClose(void);





private:
	Ui::MyDIP ui;

	QImage *imageLeft ,*imageRight;



};

#endif // MYDIP_H
