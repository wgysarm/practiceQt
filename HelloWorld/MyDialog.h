#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>

class MyDialog : public QDialog
{
	Q_OBJECT

public:
	MyDialog(QWidget *parent);
	~MyDialog();
	QPushButton *pbOk;
	QPushButton *pbCancel;
	QPushButton *pbOpenFile;
	QVBoxLayout *vlayout;


public slots:
	void slotExecOpen(void);
	void slotOk(void);
	void slotCancel(void);
	
private:



	
};

#endif // MYDIALOG_H
