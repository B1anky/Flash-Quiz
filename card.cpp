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

Card::Card(const Card& cardIn){
    englishText = new QString(cardIn.getEnglish());
    pinyinText = new QString(cardIn.getPinyin());
    chineseText = new QString(cardIn.getChinese());
}

QString Card::getEnglish() const{
    return *englishText;
}

QString Card::getPinyin() const{
    return *pinyinText;
}

QString Card::getChinese() const{
    return *chineseText;
}

void Card::setEnglish(QString english){
    englishText = new QString(english);
}

void Card::setPinyin(QString pinyin){
    pinyinText = new QString(pinyin);
}

void Card::setChinese(QString chinese){
    chineseText = new QString(chinese);
}
