#include "DragBarLabel.h"

DragBarLabel::DragBarLabel(QWidget *parent) : QLabel(parent){

}

void DragBarLabel::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() && Qt::LeftButton){
        QPoint diff = event->pos() - currentPos;
        this->parentWidget()->move(this->parentWidget()->pos() + diff);
    }
}

void DragBarLabel::mousePressEvent(QMouseEvent * event){
    currentPos = event->pos();
}
