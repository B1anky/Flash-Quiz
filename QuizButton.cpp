#include "QuizButton.h"

QuizButton::QuizButton(HoverButton *parent) : HoverButton(parent){
    setAttribute(Qt::WA_Hover);
    selected = false;
    this->setStyleSheet("background-color: rgba(255, 255, 255);");
}

void QuizButton::hoverEnter(QHoverEvent* event){
    if(!selected){
        this->setStyleSheet("background-color: rgba(0, 0, 0); color: white");
    }
}

void QuizButton::hoverLeave(QHoverEvent* event){
    if(!selected){
        this->setStyleSheet("background-color: rgba(255, 255, 255);");
    }
}

void QuizButton::mouseReleaseEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton && !selected){
        this->setStyleSheet("background-color: rgb(60,120,200); color: white");
        selected = true;
    }else if(event->button() == Qt::LeftButton && selected){
        this->setStyleSheet("background-color: rgba(0, 0, 0); color: white");
        selected = false;
    }
}

bool QuizButton::event(QEvent* e){
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

