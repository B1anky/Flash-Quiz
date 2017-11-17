#include "QuizCard.h"


QuizCard::QuizCard(QString english, QString pinyin, QString chinese){
    englishText = english;
    pinyinText = pinyin;
    chineseText = chinese;
    clicked = false;
}

void QuizCard::mouseReleaseEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton && !clicked){
        //this->setLineWidth(3);
        //this->setMidLineWidth(3);
        //this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        clicked = true;
    }else if(event->button() == Qt::LeftButton && clicked){
        //this->setLineWidth(0);
        //this->setMidLineWidth(0);
        //this->setFrameStyle(QFrame::Box | QFrame::Plain);
        clicked = false;
    }
};
