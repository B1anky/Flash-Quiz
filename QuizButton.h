#ifndef QUIZBUTTON_H
#define QUIZBUTTON_H

#include <HoverButton.h>
#include <QDebug>
#include <QObject>

class QuizButton : public HoverButton{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QColor color1 READ color1 WRITE setColor1)
public:
    explicit QuizButton(HoverButton* parent = nullptr, QVector<bool>* standardQuizOptions = nullptr);
    void setColor(QColor color);
    void setColor1 (QColor color);
    QColor color();
    QColor color1();
    void hoverEnter(QHoverEvent* event);
    void hoverLeave(QHoverEvent* event);
    bool event(QEvent* e);
    void mouseReleaseEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent *event);
    bool selected;
    QVector<bool>* quizOptions;
};

#endif // QUIZBUTTON_H
