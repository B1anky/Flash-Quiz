#ifndef EXITBUTTON_H
#define EXITBUTTON_H

#include <QPushButton>
#include <QHoverEvent>
#include <QEvent>

class ExitButton : public QPushButton{
    Q_OBJECT
public:
    explicit ExitButton(QPushButton* parent = nullptr);

    void hoverEnter(QHoverEvent* event);
    void hoverLeave(QHoverEvent* event);
    bool event(QEvent* e);
};

#endif // EXITBUTTON_H
