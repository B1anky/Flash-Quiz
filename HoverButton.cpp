#include "HoverButton.h"

HoverButton::HoverButton(QPushButton *parent): QPushButton(parent){
    setAttribute(Qt::WA_Hover);
    this->setStyleSheet("background-color: rgba(255, 255, 255);");
}

void HoverButton::setColor (QColor color){
    this->setStyleSheet(QString("background-color: rgb(%1, %2, %3); color: rgb(%4, %5, %6)").arg(color.red()).arg(color.green()).arg(color.blue()).arg(255 - color.red()).arg(255 - color.green()).arg(255 - color.blue()));
}

QColor HoverButton::color(){
    return Qt::black; // getter is not really needed for now
}

void HoverButton::hoverEnter(QHoverEvent *event){
     //this->setStyleSheet("background-color: rgba(0, 0, 0); color: white");
    QPropertyAnimation *fadeToBlack = new QPropertyAnimation(this,"color");
    fadeToBlack->setDuration(500);
    fadeToBlack->setStartValue(QColor(255,255,255));
    fadeToBlack->setEndValue(QColor(0,0,0));
    fadeToBlack->start();
}

void HoverButton::hoverLeave(QHoverEvent *event){
    //this->setStyleSheet("background-color: rgba(255, 255, 255);");
    QPropertyAnimation *fadeToWhite = new QPropertyAnimation(this,"color");
    fadeToWhite->setDuration(500);
    fadeToWhite->setStartValue(QColor(0,0,0));
    fadeToWhite->setEndValue(QColor(255,255,255));
    fadeToWhite->start();
}

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
