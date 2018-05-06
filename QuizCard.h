#ifndef QUIIZCARD_H
#define QUIZCARD_H

#include <Card.h>
#include <QPushButton>
#include <QHoverEvent>
#include <QEvent>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QObject>
#include <QColor>

class QuizCard : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QColor color1 READ color1 WRITE setColor1)
public:
    QuizCard();
    QuizCard(Card cardIn, QVector<Card*>& selectedCards);
    //QuizCard(const QuizCard& quizCardIn, QVector<Card*>& selectedCardsIn);
    QVector<Card*>* selected;
    Card getCard() const;
    Card* getCardRef() const;
    void setClicked(bool clickedIn);
    void setColor(QColor color);
    void setColor1 (QColor color);
    QColor color();
    QColor color1();
    void hoverEnter(QHoverEvent* event);
    void hoverLeave(QHoverEvent* event);
    bool event(QEvent* e);
    void mouseReleaseEvent(QMouseEvent * event);
private:
    Card* card;
    bool clicked;

signals:

public slots:
};

#endif // QUIZCARD_H
