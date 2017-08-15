#include "MyTCPCom.h"
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QAction>
#include <QHostAddress>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QTimer>
#include <QTime>
#include <QIODevice>
#include <string>

using namespace std;

MyTCPCom::MyTCPCom(QWidget *parent)
	: QMainWindow(parent)
{
	QLabel *m_labelLeft, *m_labelLeftBot, *m_labelRight, *m_labelRightBot,
		   *m_labelSendLeft, *m_labelSendRight;
	QVBoxLayout *vLayoutLeft, *vLayoutRight; 
	QHBoxLayout *hLayoutLeft1, *hLayoutLeft2, *hLayoutLeft3, *hLayoutRight1, *hLayoutRight2, *hLayoutRight3;
	QGridLayout *gLayoutGroupLeft, *gLayoutGroupRight;
	QPushButton *pbSend, *pbConnect, *pbDisconnect, *pbServerSend, *pbLeft1, *pbLeft2;

	QTextEdit *textEditLeft, *textEditRight;
	
	ui.setupUi(this);

	splitterMain = new QSplitter(Qt::Horizontal,this);
	m_widgetLeft		= new QWidget(splitterMain);
	m_widgetRight		= new QWidget(splitterMain);
	m_textBrowserLeft	= new QTextBrowser(m_widgetLeft);
	m_textBrowserRight	= new QTextBrowser(m_widgetRight);

	m_labelLeft = new QLabel(tr("Left Frame"),m_widgetLeft);
	m_labelLeftBot = new QLabel(tr("Left Frame Bot"), m_widgetLeft);
	m_labelRight = new QLabel(tr("Right Frame"),m_widgetRight);
	m_labelRightBot = new QLabel(tr("Right Frame Bot"), m_widgetRight);
	m_labelSendLeft = new QLabel(tr("SendLeft"), m_widgetLeft);
	m_labelSendRight = new QLabel(tr("SendRight"), m_widgetRight);

	vLayoutLeft = new QVBoxLayout(m_widgetLeft);
	hLayoutLeft1 = new QHBoxLayout(m_widgetLeft);
	hLayoutLeft2 = new QHBoxLayout(m_widgetLeft);
	hLayoutLeft3 = new QHBoxLayout(m_widgetLeft);
	vLayoutRight = new QVBoxLayout(m_widgetRight);
	hLayoutRight1 = new QHBoxLayout(m_widgetRight);
	hLayoutRight2 = new QHBoxLayout(m_widgetRight);
	hLayoutRight3 = new QHBoxLayout(m_widgetRight);
	gLayoutGroupLeft = new QGridLayout(m_widgetLeft);
	gLayoutGroupRight = new QGridLayout(m_widgetRight);

	server = new QTcpServer(m_widgetLeft);
	serverSocket = new QTcpSocket(m_widgetLeft);
	clientSocket = new QTcpSocket(m_widgetRight);
	pbSend = new QPushButton(tr("send"),m_widgetRight);
	pbConnect = new QPushButton(tr("connect"), m_widgetRight);
	pbDisconnect = new QPushButton(tr("disconnect"),m_widgetRight);
	pbServerSend = new QPushButton(tr("send"),m_widgetLeft);
	pbLeft1 = new QPushButton(tr("Left1"),m_widgetLeft);
	pbLeft2 = new QPushButton(tr("Left2"),m_widgetLeft);

	lineEditLeft = new QLineEdit("lienEditL",m_widgetLeft);
	lineEditRight = new QLineEdit("lineEditR", m_widgetRight);

	textEditLeft = new QTextEdit("textEditLeft", m_widgetLeft);
	textEditRight = new QTextEdit("textEditRight", m_widgetRight);
	timerSend = new QTimer(this);



	splitterMain->addWidget(m_widgetLeft);
	splitterMain->addWidget(m_widgetRight);
	splitterMain->setStretchFactor(0,1);//
	splitterMain->setStretchFactor(1,1);
	splitterMain->setContentsMargins(20,20,20,20);
	splitterMain->setMidLineWidth(20);
	splitterMain->setStyleSheet("QSplitter::handle{background-color:lightgray}");
	splitterMain->handle(1)->setDisabled(true);
	splitterMain->setHandleWidth(5);

	gLayoutGroupLeft->addWidget(ui.radioButtonLeft1,0,0);
	gLayoutGroupLeft->addWidget(ui.radioButtonLeft2,1,0);
	gLayoutGroupLeft->addWidget(ui.checkBoxLeft1,0,1);
	gLayoutGroupLeft->addWidget(ui.checkBoxLeft2,1,1);
	ui.groupBoxLeft->setLayout(gLayoutGroupLeft);

	hLayoutLeft1->addWidget(m_labelLeft);
	hLayoutLeft2->addWidget(m_labelLeftBot);
	hLayoutLeft3->addWidget(m_labelSendLeft);
	hLayoutLeft3->addWidget(pbServerSend);
	hLayoutLeft3->addWidget(pbLeft1);
	hLayoutLeft3->addWidget(pbLeft2);
	hLayoutLeft3->addWidget(ui.groupBoxLeft);
	
	vLayoutLeft->addLayout(hLayoutLeft1);
	vLayoutLeft->addWidget(lineEditLeft);
	vLayoutLeft->addWidget(textEditLeft);
	vLayoutLeft->addWidget(m_textBrowserLeft);
	vLayoutLeft->addLayout(hLayoutLeft3);
	vLayoutLeft->addLayout(hLayoutLeft2);


	gLayoutGroupRight->addWidget(ui.radioButtonRight1,0,0);
	gLayoutGroupRight->addWidget(ui.radioButtonRight2,1,0);
	gLayoutGroupRight->addWidget(ui.checkBoxRight1,0,1);
	gLayoutGroupRight->addWidget(ui.checkBoxRight2,1,1);
	ui.groupBoxRight->setLayout(gLayoutGroupRight);

	hLayoutRight1->addWidget(m_labelRight);
	hLayoutRight2->addWidget(m_labelRightBot);
	hLayoutRight3->addWidget(m_labelSendRight);
	hLayoutRight3->addWidget(pbSend);
	hLayoutRight3->addWidget(pbConnect);
	hLayoutRight3->addWidget(pbDisconnect);
	hLayoutRight3->addWidget(ui.groupBoxRight);

	vLayoutRight->addLayout(hLayoutRight1);
	vLayoutRight->addWidget(lineEditRight);
	vLayoutRight->addWidget(textEditRight);	
	vLayoutRight->addWidget(m_textBrowserRight);
	vLayoutRight->addLayout(hLayoutRight3);
	vLayoutRight->addLayout(hLayoutRight2);

	this->setCentralWidget(splitterMain);//QSplitter 是QWidget的子类
	server->listen(QHostAddress::Any,8899);
	timerSend->setInterval(1000);
	
	QObject::connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
	QObject::connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(close()));
	QObject::connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));

	QObject::connect(server, SIGNAL(newConnection()), this, SLOT(slotServer()) );

	QObject::connect(clientSocket,SIGNAL(connected()), this, SLOT(slotClientSocketRW()));
	QObject::connect(pbConnect,SIGNAL(clicked()), this, SLOT(slotClientConnect()));

	QObject::connect(pbSend, SIGNAL(clicked()), this ,SLOT(slotTimerSend()));
	QObject::connect(pbDisconnect,SIGNAL(clicked()), this, SLOT(slotDisconnect()));
	QObject::connect(timerSend, SIGNAL(timeout()), this, SLOT(slotTimerOut()));
	QObject::connect(lineEditRight,SIGNAL(returnPressed()),this , SLOT(slotTimerSend()));
	QObject::connect(pbServerSend, SIGNAL(clicked()), this, SLOT(slotServerSend()));
	QObject::connect(lineEditLeft,SIGNAL(returnPressed()), this , SLOT(slotServerSend()));

}

MyTCPCom::~MyTCPCom()
{

}

void MyTCPCom::openFile()
{
	qDebug() << "open file debug" ;
	QString path = QFileDialog::getOpenFileName(this,
		tr("Open File"),
		".",
		tr("Text Files(*.txt)"));
	if(!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Read File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		QTextStream in(&file);
		m_textBrowserLeft->setText(in.readAll());
		in.flush();
		file.close();
	} else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
}

void MyTCPCom::saveFile()
{
	qDebug() << "action save File" ;
	QString path = QFileDialog::getSaveFileName(this, 
												QString("save file"), 
												QString("c:\\"), 
												QString("*.txt"));


	if(!path.isNull())
	{
		qDebug() << path <<"   " <<"file save yes";

		QFile file(path,this);
		file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);

		//file.write(this->m_textBrowserLeft->toPlainText().toStdString().c_str());
		QTextStream out(&file);
		out << this->m_textBrowserLeft->toPlainText();

		out.flush();

		file.close();
		return;
	}
	else
	{
		qDebug() << "file save cancel";
		return;
	}

}

void MyTCPCom::slotServer()
{
	while(server->hasPendingConnections())
	{
		serverSocket = server->nextPendingConnection();
		m_textBrowserLeft->append("New Connection....");
		QObject::connect(serverSocket,SIGNAL(readyRead()),this, SLOT(slotServerSocketRW()));

	}
}

void MyTCPCom::slotServerSocketRW()
{
	
	QByteArray buf ;

	while(serverSocket->bytesAvailable() > 0)
	{
		buf = serverSocket->readAll();

		InfoAlarm *ptr = (InfoAlarm *)buf.data();
		qDebug() << ptr->alarmType  << "  ------   "  << ptr->infoHead ;
		qDebug("%s",&ptr->data);

		//m_textBrowserLeft->append(QString(buf));
		//if(buf.at(buf.size()-1) == '2')
		//{
		//		serverSocket->write("receive 2");
		//}
		m_textBrowserLeft->append(QString(buf));
	}
}
void MyTCPCom::slotClientSocketRW()
{
	qDebug() << "connected" ;
	QString str("hello,server");
	clientSocket->write(str.toUtf8());
	QObject::connect(clientSocket,SIGNAL(readyRead()),this, SLOT(slotClientRead()));
}

void MyTCPCom::slotClientConnect()
{
	clientSocket->connectToHost("127.0.0.1", 8899);
}

void MyTCPCom::slotDisconnect()
{
	timerSend->stop();
	clientSocket->close();
}

void MyTCPCom::slotTimerSend()
{
	timerSend->start();
	QString strtmp = lineEditRight->text();
	//QTextStream stream(&strtmp,QIODevice::ReadWrite) ;

	clientSocket->write(strtmp.toUtf8());
	lineEditRight->clear();
}


void MyTCPCom::slotTimerOut()
{
	static QString str("12345678901234567890");
	InfoAlarm info;
	info.infoHead = 0x5555;
	info.alarmType = 0x0001;
	
	memcpy(info.data,&str,sizeof(str));

	QByteArray send;
	send.resize(sizeof(info));

	memcpy(send.data(),&info,sizeof(info) );

	qDebug() << "timerout";
	//QString str1("hello,timer print per sec");
	//QTextStream text(&send,QIODevice::ReadWrite);
	//text << QTime::currentTime().toString(Qt::TextDate);
	//clientSocket->write(str1.toUtf8());
	clientSocket->write(send);
}


void MyTCPCom::slotClientRead()
{
	while(clientSocket->bytesAvailable() > 0)
	{
		QByteArray array = clientSocket->readAll();
		m_textBrowserRight->append(QString(array));
	}

}


void MyTCPCom::slotServerSend()
{
	QString str = lineEditLeft->text();


	serverSocket->write(str.toUtf8());
	lineEditLeft->clear();
}

