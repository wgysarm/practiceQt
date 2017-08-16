#ifndef MYDIP_H
#define MYDIP_H

#include <QMainWindow>
#include "ui_MyDIP.h"
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>

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
	void SlotOperateActionLoad(void);
	void SlotOperateActionGray(void);





private:
	Ui::MyDIP ui;

	QImage *imageLeft ,*imageRight;
	QGraphicsScene *sceneLeft, *sceneRight;



};

#endif // MYDIP_H
