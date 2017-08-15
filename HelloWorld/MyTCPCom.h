#ifndef MYTCPCOM_H
#define MYTCPCOM_H

#include <QMainWindow>
#include <QSplitter>
#include <QListWidget>
#include <QTableWidget>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QTextBrowser>
#include <QTcpServer>
#include <QByteArray>
#include <QTcpSocket>

#include "ui_MyTCPCom.h"

typedef struct InfoAlarm{
	int infoHead;
	int alarmType;
	char data[100];
};

class MyTCPCom : public QMainWindow
{
	Q_OBJECT

public:

	QSplitter *splitterMain;
	QWidget *m_widgetLeft, *m_widgetRight;		;
	QPixmap *m_pixmapLeft,*m_pixmapRigt;
	QTextEdit *m_textEditLeft, *m_textEditRight ;
	QTextBrowser *m_textBrowserLeft, *m_textBrowserRight;

	QLineEdit *lineEditLeft, *lineEditRight;
	QTcpServer *server;
	QTcpSocket *serverSocket, *clientSocket;
	QTimer *timerSend;

	InfoAlarm *infoAlarm;


	MyTCPCom(QWidget *parent = 0);
	~MyTCPCom();

private:
	Ui::MyTCPCom ui;


	
	//QTableWidget *m_table;
public slots:
	void openFile();
	void saveFile();
	void slotServer();
	void slotServerSocketRW();
	void slotServerSend();

	void slotClientSocketRW();
	void slotClientConnect();
	void slotClientRead();

	void slotDisconnect();
	void slotTimerSend();
	void slotTimerOut();

};

#endif // MYTCPCOM_H
