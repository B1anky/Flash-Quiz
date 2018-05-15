#include "HoverButton.h"

HoverButton::HoverButton(QPushButton *parent): QPushButton(parent){
    setAttribute(Qt::WA_Hover);
    this->setStyleSheet("background-color: rgba(255, 255, 255);");
}

void HoverButton::setColor (QColor color){
    this->setStyleSheet(QString("background-color: rgb(%1, %2, %3); color: rgb(%4, %5, %6)").arg(color.red()).arg(color.green()).arg(color.blue()).arg(255 - color.red()).arg(255 - color.green()).arg(255 - color.blue()));
}

void HoverButton::setColor1 (QColor color){
    this->setStyleSheet(QString("background-color: rgb(%1, %2, %3); color: rgb(255,255,255);").arg(color.red()).arg(color.green()).arg(color.blue()));
}


QColor HoverButton::color(){
    return Qt::black; // getter is not really needed for now
}

QColor HoverButton::color1(){
    return QColor(0,191,255); // getter is not really needed for now
}

void HoverButton::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        QPropertyAnimation *fadeToBlue = new QPropertyAnimation(this,"color1");
        fadeToBlue->setDuration(100);
        fadeToBlue->setStartValue(QColor(0,0,0));
        fadeToBlue->setEndValue(QColor(60,120,200));
        fadeToBlue->start();
        QPushButton::mousePressEvent(event);
    }

}

void HoverButton::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton && this->rect().contains(event->localPos().toPoint())){
        //Don't process click and just change color back
        QPropertyAnimation *fadeToWhite = new QPropertyAnimation(this,"color");
        fadeToWhite->setDuration(100);
        fadeToWhite->setStartValue(QColor(60,120,200));
        fadeToWhite->setEndValue(QColor(255,255,255));
        fadeToWhite->start();
        QPushButton::mouseReleaseEvent(event);
    }
}

void HoverButton::enterEvent(QEvent *event){
    QPropertyAnimation *fadeToBlack = new QPropertyAnimation(this,"color");
    fadeToBlack->setDuration(500);
    fadeToBlack->setStartValue(QColor(255,255,255));
    fadeToBlack->setEndValue(QColor(0,0,0));
    fadeToBlack->start();
    QPushButton::enterEvent(event);
}

void HoverButton::leaveEvent(QEvent *event){
    QPropertyAnimation *fadeToWhite = new QPropertyAnimation(this,"color");
    fadeToWhite->setDuration(500);
    fadeToWhite->setStartValue(QColor(0,0,0));
    fadeToWhite->setEndValue(QColor(255,255,255));
    fadeToWhite->start();
    QPushButton::leaveEvent(event);
}
/*
bool HoverButton::event(QEvent* e){
    switch(e->type()){
        case QEvent::HoverEnter:
            hoverEnter(static_cast<QHoverEvent*>(e));
            return true;
            break;
        case QEvent::HoverLeave:
            hoverLeave(static_cast<QHoverEvent*>(e));
            return true;
            break;
        default:
            break;
    }
    return QWidget::event(e);
}
*/
