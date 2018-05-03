#include "DropDownTextEdit.h"

DropDownTextEdit::DropDownTextEdit(QLineEdit*){

}

DropDownTextEdit::DropDownTextEdit(QVector<QPair<QString, QVector<Card*>*>> quizListIn){
    updateCompleter(quizListIn);
}

void DropDownTextEdit::setDefaultText(QString str){
    defaultText = str;
}

QString DropDownTextEdit::getDefaultText(){
    return defaultText;
}

void DropDownTextEdit::focusInEvent(QFocusEvent *e){
    if(this->text() == defaultText){
        this->setText("");
    }

    QLineEdit::focusInEvent(e);
}

void DropDownTextEdit::focusOutEvent(QFocusEvent *e){
    if(this->text() == ""){
        this->setText(defaultText);
    }

    QLineEdit::focusInEvent(e);
}

void DropDownTextEdit::updateCompleter(QVector<QPair<QString, QVector<Card*>*>> quizListIn){
    if(quizListIn.empty()){
        this->setCompleter(nullptr);
        return;
    }
    quizNames.clear();
    for(auto quiz: quizListIn){
        qInfo() << quiz.first;
        quizNames << quiz.first;
    }

    QCompleter* stringCompleter = new QCompleter(quizNames, this);
    stringCompleter->setFilterMode(Qt::MatchContains);
    stringCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    if(stringCompleter){
        this->disconnect(stringCompleter);
    }

    if(!stringCompleter){
        return;
    }

    this->setCompleter(stringCompleter);
}

