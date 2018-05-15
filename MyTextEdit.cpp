#include "MyTextEdit.h"

MyTextEdit::MyTextEdit(QTextEdit *parent) : QTextEdit(parent){
    QTextEdit::setTabChangesFocus(true);
    this->setFrameStyle(QFrame::NoFrame);
    this->setAttribute(Qt::WA_TranslucentBackground);
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

void MyTextEdit::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_Return)
        return;
    else{
        QTextEdit::keyPressEvent(e);
    }
}

void MyTextEdit::focusOutEvent(QFocusEvent* event){
    if(this->toPlainText() == ""){
        this->setText(defaultText);
    }

    QTextEdit::focusOutEvent(event);

}
