#include "ClockThread.h"

ClockThread::ClockThread(){

}

void ClockThread::run(){
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()), Qt::DirectConnection);
    timer->setInterval(1);
    timer->start();   // puts one event in the threads event queue
    exec();
}

void ClockThread::timerHit(){
    startingTime -= .001;
    QString newTime = QString::number(startingTime);
    if(m_lastTime != newTime ){
        m_lastTime = newTime;
        emit sendTime(newTime);
    }

    if(startingTime <= .001){
        emit sendTime("Go!");
    }

    if(startingTime <= -1.0){
        emit timerDone();
        timer->stop();
        timer->deleteLater();
        this->quit();
    }

    if(forceDone){
        timer->stop();
        timer->deleteLater();
        this->quit();
    }
}
