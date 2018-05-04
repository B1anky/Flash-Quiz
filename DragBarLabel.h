#ifndef DRAGBARLABEL_H
#define DRAGBARLABEL_H

#include <QEvent>
#include <QObject>
#include <QLabel>
#include <QMouseEvent>

class DragBarLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DragBarLabel(QWidget *parent = 0);

    QPoint currentPos;

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // DRAGBARLABEL_H
