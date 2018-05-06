#include "ExitButton.h"

ExitButton::ExitButton(QPushButton *parent): QPushButton(parent){
    setAttribute(Qt::WA_Hover);
    this->setStyleSheet("background-color: rgba(255, 255, 255, 0); color: black;");
}

void ExitButton::hoverEnter(QHoverEvent *event){
     this->setStyleSheet("background-color: rgba(255, 50, 0); color: black; border: transparent; float: top;");
}

void ExitButton::hoverLeave(QHoverEvent *event){
    this->setStyleSheet("background-color: rgba(255, 255, 255, 0); color: black;");
}

bool ExitButton::event(QEvent* e){
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
