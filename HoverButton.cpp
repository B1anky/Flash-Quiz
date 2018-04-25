#include "HoverButton.h"

HoverButton::HoverButton(QPushButton *parent): QPushButton(parent){
    setAttribute(Qt::WA_Hover);
    this->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
}

void HoverButton::enterEvent(QHoverEvent *e){


}

void HoverButton::leaveEvent(QHoverEvent *e){

}

void HoverButton::hoverEnter(QHoverEvent *event){
     this->setStyleSheet("background-color: rgba(255, 255, 255, 25); border: 2px solid black");
}

void HoverButton::hoverLeave(QHoverEvent *event){
    this->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
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
