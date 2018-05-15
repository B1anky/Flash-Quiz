#ifndef CLOCKTHREAD_H
#define CLOCKTHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QString>
#include <QDateTime>
#include <QtCore>

class ClockThread : public QThread{
    Q_OBJECT
public:
    ClockThread();
    void run();
    bool forceDone = false;
signals:
    void sendTime(QString time);
    void timerDone();
private:
    double startingTime = 5.000;
    QString m_lastTime;
    QTimer* timer;
private slots:
    void timerHit();


};

#endif // CLOCKTHREAD_H
