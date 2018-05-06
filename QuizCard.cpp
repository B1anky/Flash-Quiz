#include "QuizCard.h"

void QuizCard::setColor (QColor color){
    this->setStyleSheet(QString("background-color: rgba(%1, %2, %3, %4); color: rgb(%4, %5, %6)").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()).arg(255 - color.red()).arg(255 - color.red()).arg(255 - color.red()));
}

void QuizCard::setColor1 (QColor color){
    this->setStyleSheet(QString("background-color: rgb(%1, %2, %3); color: rgb(255,255,255);").arg(color.red()).arg(color.green()).arg(color.blue()));
}

QColor QuizCard::color1(){
    return QColor(0,191,255); // getter is not really needed for now
}

QColor QuizCard::color(){
    return Qt::white; // getter is not really needed for now
}

void QuizCard::hoverEnter(QHoverEvent* event){
    if(!clicked){
        //this->setStyleSheet("background-color: rgba(0, 0, 0); color: white");
        QPropertyAnimation *fadeToBlack = new QPropertyAnimation(this,"color");
        fadeToBlack->setDuration(500);
        fadeToBlack->setStartValue(QColor(255,255,255,0));
        fadeToBlack->setEndValue(QColor(0,0,0,255));
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

void QuizCard::hoverLeave(QHoverEvent* event){
    if(!clicked){
        //this->setStyleSheet("background-color: rgba(255, 255, 255);");
        QPropertyAnimation *fadeToWhite = new QPropertyAnimation(this,"color");
        fadeToWhite->setDuration(500);
        fadeToWhite->setStartValue(QColor(0,0,0,255));
        fadeToWhite->setEndValue(QColor(0,0,0,0));
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

void QuizCard::mouseReleaseEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton && !clicked){
        //this->setStyleSheet("background-color: rgb(60,120,200); color: white");
        for(auto card = selected->begin(); card != selected->end(); ++card){
            if(**card == *this->card){
                //do nothing because it's already in the list due to a load
                return;
            }
        }
        selected->push_back(this->card);
        clicked = true;

        QPropertyAnimation *fadeToDarkBlue = new QPropertyAnimation(this,"color1");
        fadeToDarkBlue->setDuration(500);
        QColor curColor = QColor(60,120,200);
        QColor darkerBlue = QColor(0,191,255);
        fadeToDarkBlue->setStartValue(curColor);
        fadeToDarkBlue->setEndValue(darkerBlue);
        fadeToDarkBlue->start();
    }else if(event->button() == Qt::LeftButton && clicked){
        //this->setStyleSheet("background-color: rgba(0, 0, 0); color: white");
        for(auto card = selected->begin(); card != selected->end(); ++card){
            if(**card == *this->card){
                selected->removeOne(*card);
                break;
            }
        }
        clicked = false;

        QPropertyAnimation *fadeToBlack = new QPropertyAnimation(this,"color");
        fadeToBlack->setDuration(500);
        fadeToBlack->setStartValue(QColor(0,191,255,255));
        fadeToBlack->setEndValue(QColor(0,0,0,255));
        fadeToBlack->start();
    }
}



QuizCard::QuizCard(){
    card = new Card;
    clicked = false;
}

QuizCard::QuizCard(Card cardIn, QVector<Card*>& selectedCardsIn){
    this->card = new Card(cardIn);
    this->selected = &selectedCardsIn;
    clicked = false;
}

/*
void QuizCard::mouseReleaseEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton && !clicked){
        this->setStyleSheet("background-color: rgb(60,120,200);");
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
*/


bool QuizCard::event(QEvent* e){
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


Card QuizCard::getCard() const{
    return *card;
}

Card* QuizCard::getCardRef() const{
    return card;
}

void QuizCard::setClicked(bool clickedIn){
    clicked = clickedIn;
}
