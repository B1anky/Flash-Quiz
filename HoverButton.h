#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QPushButton>
#include <QHoverEvent>
#include <QEvent>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QObject>
#include <QtCore>

class HoverButton : public QPushButton{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QColor color1 READ color1 WRITE setColor1)

public:
    explicit HoverButton(QPushButton* parent = nullptr);
    void setColor(QColor color);
    void setColor1(QColor color);
    QColor color();
    QColor color1();
    //void hoverEnter(QHoverEvent* event);
    //void hoverLeave(QHoverEvent* event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool clicked;
    //bool event(QEvent* e);
};

#endif // HOVERBUTTON_H
