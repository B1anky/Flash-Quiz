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
        this->setStyleSheet("background-color: rgb(255, 0, 0);");
        //Check to make sure it's not currently in the list due to a load
        for(auto card = selected->begin(); card != selected->end(); ++card){
            if(**card == *this->card){
                //do nothing because it's already in the list due to a load
                return;
            }
        }
        selected->push_back(this->card);
        clicked = true;
    }else if(event->button() == Qt::LeftButton && clicked){
        this->setStyleSheet("");
        this->clearFocus();
        //search selectedCards and remove
        for(auto card = selected->begin(); card != selected->end(); ++card){
            if(**card == *this->card){
                selected->removeOne(*card);
                break;
            }
        }

        clicked = false;
    }
}

Card QuizCard::getCard() const{
    return *card;
}

Card* QuizCard::getCardRef() const{
    return card;
}

void QuizCard::setClicked(bool clickedIn){
    clicked = clickedIn;
}
