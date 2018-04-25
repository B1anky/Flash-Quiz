#include "DropDownTextEdit.h"

DropDownTextEdit::DropDownTextEdit(QVector<QString> quizNamesIn){
    for(auto quiz: quizNamesIn){
        quizNames << quiz;
    }

    stringCompleter = new QCompleter(quizNames, this);
    stringCompleter->setFilterMode(Qt::MatchContains);
    stringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    this->setCompleter(stringCompleter);
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


