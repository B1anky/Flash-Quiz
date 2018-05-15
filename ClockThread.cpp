#include "ClockThread.h"

ClockThread::ClockThread(){

}

void ClockThread::run(){
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()), Qt::DirectConnection);
    timer->setInterval(10);
    timer->start();   // puts one event in the threads event queue
    exec();
    timer->stop();
    timer->deleteLater();
}

void ClockThread::timerHit(){
    startingTime -= .01;
    QString newTime = QString::number(startingTime);
    if(m_lastTime != newTime ){
        m_lastTime = newTime;
        emit sendTime(newTime) ;
    }

    if(startingTime <= .001){
        emit sendTime("Go!");
    }

    if(startingTime <= -.500){
        this->quit();
        timer->stop();
        emit timerDone();
    }
}
