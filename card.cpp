#include "Card.h"

Card::Card(){
    englishText = new QString();
    pinyinText = new QString();
    chineseText = new QString();
}

Card::Card(QString english, QString pinyin, QString chinese){
    englishText = new QString(english);
    pinyinText = new QString(pinyin);
    chineseText = new QString(chinese);
}

QString Card::getEnglish(){
    return *englishText;
}

QString Card::getPinyin(){
    return *pinyinText;
}

QString Card::getChinese(){
    return *chineseText;
}
