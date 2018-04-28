#ifndef QUIIZCARD_H
#define QUIZCARD_H

#include <QApplication>
#include <QMouseEvent>
#include <QString>
#include <QPushButton>
#include <card.h>
#include <QPalette>
#include <QtGlobal>

class QuizCard : public QPushButton {
public:
    QuizCard();
    QuizCard(Card cardIn, QVector<Card*>& selectedCards);
    //QuizCard(const QuizCard& quizCardIn, QVector<Card*>& selectedCardsIn);
    QVector<Card*>* selected;
    Card getCard() const;
    Card* getCardRef() const;
    void setClicked(bool clickedIn);
private:
    Card* card;
    bool clicked;
    void mouseReleaseEvent(QMouseEvent * event);
signals:

public slots:
};

#endif // QUIZCARD_H
