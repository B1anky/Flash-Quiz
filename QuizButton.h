#ifndef QUIZBUTTON_H
#define QUIZBUTTON_H

#include <HoverButton.h>

class QuizButton : public HoverButton{
        Q_OBJECT
public:
    explicit QuizButton(HoverButton* parent = nullptr);
    void hoverEnter(QHoverEvent* event);
    void hoverLeave(QHoverEvent* event);
    bool event(QEvent* e);
    void mouseReleaseEvent(QMouseEvent * event);
    bool selected;
};

#endif // QUIZBUTTON_H
