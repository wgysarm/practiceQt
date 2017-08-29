#ifndef THREADOBJECT_H
#define THREADOBJECT_H

#include <QObject>
#include <QThread>


class ThreadObject : public QObject
{
	Q_OBJECT

public:
	ThreadObject(QObject *parent);
	~ThreadObject();
signals:
	void sig_finished();
public slots:
	void SlotProcessFunc(void);
	void SlotGetSingal(void);
private:
	
};

#endif // THREADOBJECT_H
