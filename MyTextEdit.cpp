#include "MyTextEdit.h"

MyTextEdit::MyTextEdit(QTextEdit *parent) : QTextEdit(parent){
    QTextEdit::setTabChangesFocus(true);
}

void MyTextEdit::setDefaultText(QString str){
    defaultText = str;
}

QString MyTextEdit::getDefaultText(){
    return defaultText;
}

void MyTextEdit::focusInEvent(QFocusEvent * event){
    if(this->toPlainText() == defaultText){
        this->setText("");
    }
     QTextEdit::focusInEvent(event);
}

void MyTextEdit::focusOutEvent(QFocusEvent* event){
    if(this->toPlainText() == ""){
        this->setText(defaultText);
    }

    QTextEdit::focusOutEvent(event);

}
