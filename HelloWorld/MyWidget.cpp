#include "MyWidget.h"
#include <QDebug>
#include <QCompleter>
using namespace std;


MyWidget::MyWidget(QWidget *parent)
	: QWidget(parent)//初始化列表，用parent参数去初始化父类，继承自父类。
{

	vlayout = new QVBoxLayout(this);
	operatorNum = 0;
	ivfdtest = new IVFDTest();
	if (ivfdtest != NULL)
		ivfdtest->setDevID(33);


	QStringList completions;
	completions << "aaa" << "bbb" << "ccc";

	labeltmp = new QLabel(tr("test label:"),this);
	QRadioButton *radioButtontmp = new QRadioButton(this);
	QCheckBox *checkBoxtmp = new QCheckBox(this);
	QComboBox *comboBoxtmp = new QComboBox(this);
	textEdit = new QTextEdit(this);
	lineEdittmp = new QLineEdit(this);
	QSlider *slidertmp = new QSlider(this);
	QSpinBox *spinBoxtmp = new QSpinBox(this);
	QDateEdit *dateEdittmp = new QDateEdit(this);

	QHBoxLayout *hlayout1 = new QHBoxLayout(this);
	QHBoxLayout *hlayout2 = new QHBoxLayout(this);
	QPushButton *pushButtontmp1 = new QPushButton(tr("key1"),this);
	QPushButton *pushButtontmp2 = new QPushButton(tr("key2"),this);

	labeltmp->setStyleSheet("QLabel{color:red;font:bold}");
	spinBoxtmp->setRange(0,100);
	slidertmp->setOrientation(Qt::Horizontal);
	slidertmp->setRange(0,100);
	textEdit->installEventFilter(this);
	comboBoxtmp->setEditable(true);
	comboBoxtmp->setCompleter(new QCompleter(completions,this));


	vlayout->addWidget(labeltmp);
	vlayout->addWidget(lineEdittmp);
	vlayout->addWidget(radioButtontmp);
	vlayout->addWidget(checkBoxtmp);
	vlayout->addWidget(comboBoxtmp);
	vlayout->addWidget(textEdit);

	vlayout->addWidget(dateEdittmp);
	hlayout1->addWidget(pushButtontmp1,0,Qt::AlignLeft);
	hlayout1->addWidget(pushButtontmp2,0,Qt::AlignRight);
	hlayout2->addWidget(spinBoxtmp);
	hlayout2->addWidget(slidertmp);

	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);

	QObject::connect(pushButtontmp1,SIGNAL(clicked()),this,SLOT(mySlotInput()));
	QObject::connect(pushButtontmp2,SIGNAL(clicked()),this,SLOT(mySlotClear()));
	QObject::connect(slidertmp,SIGNAL(valueChanged(int)),spinBoxtmp,SLOT(setValue(int)));
	QObject::connect(spinBoxtmp,SIGNAL(valueChanged(int)),slidertmp,SLOT(setValue(int)));




	//disconnect(pushButtontmp2,SIGNAL(clicked()),this,SLOT(mySlotClear()));

}

MyWidget::~MyWidget()
{
	if (ivfdtest != NULL)
		delete ivfdtest;
}

void MyWidget::mySlotInput(void)
{
	operatorNum++;
	//textEdit->setText(tr("mySlot"));
	textEdit->append(("mySlot"+QString::number(operatorNum,10)));
	//textEdit->append(QString::number(operatorNum,10));
	qDebug() << QString::number(ivfdtest->getDevID(),10)<< endl ;
}

void MyWidget::mySlotClear(void)
{
	textEdit->clear();
}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
	qDebug() << "mousePress"  ;
	return;
}

bool MyWidget::event(QEvent *event)
{
	if(event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		if(keyEvent->key() == Qt::Key_Space)
		{
			qDebug() << "you press space" ;
			return true;
		}

	}

	return QWidget::event(event);
}

bool MyWidget::eventFilter(QObject * obj, QEvent * event)
{
	if (obj == textEdit) {//侦听对象textEdit
		if (event->type() == QEvent::KeyPress) {//过滤KeyPress事件
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
			qDebug() << "Ate key press" << keyEvent->key();
			doTextEdit();
			return true;//返回true说明已经处理
		} else {
			return false;//返回false说明未处理
		}
	} else {
		// pass the event on to the parent class
		return MyWidget::eventFilter(obj, event);
	}


}

int MyWidget::doTextEdit(void)
{
	//lineEdittmp->setText(textEdit->toPlainText());

	QString str = textEdit->toPlainText();
	lineEdittmp->setText(str);
	return 0;
}