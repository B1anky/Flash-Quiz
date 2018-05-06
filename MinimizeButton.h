#ifndef MINIMIZEBUTTON_H
#define MINIMIZEBUTTON_H

#include <QPushButton>
#include <QHoverEvent>
#include <QEvent>

class MinimizeButton : public QPushButton{
    Q_OBJECT
public:
    explicit MinimizeButton(QPushButton* parent = nullptr);
    void hoverEnter(QHoverEvent* event);
    void hoverLeave(QHoverEvent* event);
    bool event(QEvent* e);
};

#endif // MINIMIZEBUTTON_H
