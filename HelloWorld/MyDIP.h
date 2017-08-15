#ifndef MYDIP_H
#define MYDIP_H

#include <QMainWindow>
#include "ui_MyDIP.h"

class MyDIP : public QMainWindow
{
	Q_OBJECT

public:
	MyDIP(QWidget *parent = 0);
	~MyDIP();

private:
	Ui::MyDIP ui;
};

#endif // MYDIP_H
