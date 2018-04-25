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
    QuizCard(Card cardIn);
    Card getCard() const;
private:
    Card* card;
    bool clicked;
    void mouseReleaseEvent(QMouseEvent * event);
signals:

public slots:
};

#endif // QUIZCARD_H
