#ifndef CARD_H
#define CARD_H

#include <QtCore>
#include <QString>
#include <QDebug>
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
    bool operator==(const Card& rhs) const;
private:
    QString* englishText;
    QString* pinyinText;
    QString* chineseText;
    friend QDebug operator<<(QDebug os, const Card& card);

};

#endif // CARD_H
