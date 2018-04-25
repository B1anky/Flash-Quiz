#ifndef CARD_H
#define CARD_H

#include <QtCore>
#include <QString>

class Card
{
public:
    Card();
    Card(QString english, QString pinyin, QString chinese);
    Card(const Card& cardIn);
    QString getEnglish() const;
    QString getPinyin() const;
    QString getChinese() const;
    void setEnglish(QString english);
    void setPinyin(QString pinyin);
    void setChinese(QString chinese);
private:
    QString* englishText;
    QString* pinyinText;
    QString* chineseText;
};

#endif // CARD_H
