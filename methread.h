#ifndef METHREAD_H
#define METHREAD_H
#include <QtGui>
#include <QThread>

class METhread : public QThread
{
    Q_OBJECT
public:
    explicit METhread(QObject *parent = 0);
    QObject* getThreadParam()const;
    void setThreadParam(QObject* param);
protected:
    virtual void run();
signals:

public slots:


private:
    QObject* m_threadParament;
};

#endif // METHREAD_H
