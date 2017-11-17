#ifndef CARD_H
#define CARD_H

#include <QtCore>
#include <QString>

class Card
{
public:
    Card();
    Card(QString english, QString pinyin, QString chinese);
    QString getEnglish();
    QString getPinyin();
    QString getChinese();
private:
    QString* englishText;
    QString* pinyinText;
    QString* chineseText;
};

#endif // CARD_H
