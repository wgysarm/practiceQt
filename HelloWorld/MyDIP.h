#ifndef MYDIP_H
#define MYDIP_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>



#include <QMainWindow>
#include "ui_MyDIP.h"
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
using namespace cv;



class MyDIP : public QMainWindow
{
	Q_OBJECT

public:
	MyDIP(QWidget *parent = 0);
	~MyDIP();

	QImage cvMat2QImage(const cv::Mat& mat);
	cv::Mat QImage2cvMat(QImage *image);
	int cvMat2QImage1(const cv::Mat* mat /*in*/, QImage **img/*out*/);
	
	
public slots:
	void SlotsFileActionOpen(void);
	void SlotsFileActionSave(void);
	void SlotsFileActionClose(void);
	void SlotOperateActionLoad(void);
	void SlotOperateActionGray(void);

	void SlotButton1Clicked(void);
	void SlotButton2Clicked(void);
	void SlotButton3Clicked(void);
	void SlotButton4Clicked(void);
	void SlotButton5Clicked(void);
	void SlotButton6Clicked(void);
	void SlotButton7Clicked(void);
	void SlotButton8Clicked(void);


private:
	Ui::MyDIP ui;

	QImage *imageLeft ,*imageRight;
	QGraphicsScene *sceneLeft, *sceneRight;



};

#endif // MYDIP_H
