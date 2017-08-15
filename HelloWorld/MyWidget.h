#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

#include <QpushButton>
#include <QRadioButton>
#include <QLabel>

#include <QLineEdit>
#include <QTextEdit>
#include <QTextBrowser>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>

#include <QCheckBox>
#include <QSlider>
#include <QTimeEdit>
#include <QDateEdit>
#include <QDateTimeEdit>

#include <QVBoxLayout>
#include <QHBoxLayout>


#include <QEvent>
#include <QMouseEvent>

#include "IVFDTest.h"

class MyWidget : public QWidget
{
	Q_OBJECT

public:
	MyWidget(QWidget *parent);
	~MyWidget();

	QVBoxLayout *vlayout;
	QTextEdit *textEdit;
	QLabel *labeltmp ;
	QLineEdit *lineEdittmp;
	int operatorNum;
	IVFDTest *ivfdtest ;

	public slots:
		void mySlotInput(void);
		void mySlotClear(void);


private:
	bool event(QEvent * e);
	bool eventFilter(QObject * watched, QEvent * event);
	int doTextEdit(void);

protected:
	void mousePressEvent(QMouseEvent *event);
	bool event(void);
};

#endif // MYWIDGET_H
