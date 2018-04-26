#include "QuizCard.h"

QuizCard::QuizCard(){
    card = new Card;
    clicked = false;
}

QuizCard::QuizCard(Card cardIn, QVector<Card*>& selectedCardsIn){
    this->card = new Card(cardIn);
    this->selected = &selectedCardsIn;
    clicked = false;
}

void QuizCard::mouseReleaseEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton && !clicked){
        QPalette palette = this->palette();
        this->setStyleSheet("background-color: rgb(255, 0, 0);");
        selected->push_back(this->card);
        clicked = true;
    }else if(event->button() == Qt::LeftButton && clicked){
        this->setStyleSheet("");
        this->clearFocus();
        //search selectedCards and remove
        for(auto card : *selected){
            if(card == this->card){
                selected->removeOne(this->card);
                break;
            }
        }

        clicked = false;
    }
};

Card QuizCard::getCard() const{
    return *card;
}

Card* QuizCard::getCardRef() const{
    return card;
}
