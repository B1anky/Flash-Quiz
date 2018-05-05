#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QPushButton>
#include <QHoverEvent>
#include <QEvent>

class HoverButton : public QPushButton{
    Q_OBJECT
public:
    explicit HoverButton(QPushButton* parent = nullptr);
    //void enterEvent(QHoverEvent *e);
    //void leaveEvent(QHoverEvent *e);
    void hoverEnter(QHoverEvent* event);
    void hoverLeave(QHoverEvent* event);
    bool event(QEvent* e);
};

#endif // HOVERBUTTON_H
