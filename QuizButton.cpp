#include "QuizButton.h"

QuizButton::QuizButton(HoverButton *parent) : HoverButton(parent){
    setAttribute(Qt::WA_Hover);
    selected = false;
    this->setStyleSheet("background-color: rgba(255, 255, 255);");
}

void QuizButton::setColor (QColor color){
    this->setStyleSheet(QString("background-color: rgb(%1, %2, %3); color: rgb(%4, %5, %6)").arg(color.red()).arg(color.green()).arg(color.blue()).arg(255 - color.red()).arg(255 - color.red()).arg(255 - color.red()));
}

void QuizButton::setColor1 (QColor color){
    this->setStyleSheet(QString("background-color: rgb(%1, %2, %3); color: rgb(255,255,255);").arg(color.red()).arg(color.green()).arg(color.blue()));
}

QColor QuizButton::color1(){
    return QColor(0,191,255); // getter is not really needed for now
}

QColor QuizButton::color(){
    return Qt::white; // getter is not really needed for now
}

void QuizButton::hoverEnter(QHoverEvent* event){
    if(!selected){
        //this->setStyleSheet("background-color: rgba(0, 0, 0); color: white");
        QPropertyAnimation *fadeToBlack = new QPropertyAnimation(this,"color");
        fadeToBlack->setDuration(500);
        fadeToBlack->setStartValue(QColor(255,255,255));
        fadeToBlack->setEndValue(QColor(0,0,0));
        fadeToBlack->start();
    }else{
        QPropertyAnimation *fadeToDarkBlue = new QPropertyAnimation(this,"color1");
        fadeToDarkBlue->setDuration(500);
        QColor curColor = QColor(60,120,200);
        QColor darkerBlue = QColor(0,191,255);
        fadeToDarkBlue->setStartValue(curColor);
        fadeToDarkBlue->setEndValue(darkerBlue);
        fadeToDarkBlue->start();
    }
}

void QuizButton::hoverLeave(QHoverEvent* event){
    if(!selected){
        //this->setStyleSheet("background-color: rgba(255, 255, 255);");
        QPropertyAnimation *fadeToWhite = new QPropertyAnimation(this,"color");
        fadeToWhite->setDuration(500);
        fadeToWhite->setStartValue(QColor(0,0,0));
        fadeToWhite->setEndValue(QColor(255,255,255));
        fadeToWhite->start();
    }else{
        QPropertyAnimation *fadeToLighterBlue = new QPropertyAnimation(this,"color1");
        fadeToLighterBlue->setDuration(500);
        QColor curColor = QColor(0,191,255);
        QColor lighterBlue = QColor(60,120,200);
        fadeToLighterBlue->setStartValue(curColor);
        fadeToLighterBlue->setEndValue(lighterBlue);
        fadeToLighterBlue->start();
    }
}

void QuizButton::mouseReleaseEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton && !selected){
        //this->setStyleSheet("background-color: rgb(60,120,200); color: white");
        QPropertyAnimation *fadeToDarkBlue = new QPropertyAnimation(this,"color1");
        fadeToDarkBlue->setDuration(500);
        QColor curColor = QColor(60,120,200);
        QColor darkerBlue = QColor(0,191,255);
        fadeToDarkBlue->setStartValue(curColor);
        fadeToDarkBlue->setEndValue(darkerBlue);
        fadeToDarkBlue->start();
        selected = true;
    }else if(event->button() == Qt::LeftButton && selected){
        //this->setStyleSheet("background-color: rgba(0, 0, 0); color: white");
        QPropertyAnimation *fadeToBlack = new QPropertyAnimation(this,"color");
        fadeToBlack->setDuration(500);
        fadeToBlack->setStartValue(QColor(255,255,255));
        fadeToBlack->setEndValue(QColor(0,0,0));
        fadeToBlack->start();
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

