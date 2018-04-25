#include "QuizCard.h"

QuizCard::QuizCard(){
    card = new Card;
    clicked = false;
}

QuizCard::QuizCard(Card cardIn){
    this->card = new Card(cardIn);
    clicked = false;
}

void QuizCard::mouseReleaseEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton && !clicked){
        qInfo() << "PLSSSSSS";
        QPalette palette = this->palette();
        this->setStyleSheet("background-color: rgb(255, 0, 0);");
        clicked = true;
    }else if(event->button() == Qt::LeftButton && clicked){
        this->setStyleSheet("");
        this->clearFocus();
        clicked = false;
    }
};

Card QuizCard::getCard() const{
    return *card;
}
