#include "HoverButton.h"

HoverButton::HoverButton(QPushButton *parent): QPushButton(parent){
    setAttribute(Qt::WA_Hover);
    this->setStyleSheet("background-color: rgba(255, 255, 255);");
}

void HoverButton::hoverEnter(QHoverEvent *event){
     this->setStyleSheet("background-color: rgba(0, 0, 0); color: white");
}

void HoverButton::hoverLeave(QHoverEvent *event){
    this->setStyleSheet("background-color: rgba(255, 255, 255);");
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
