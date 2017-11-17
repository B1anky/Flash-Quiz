#ifndef QUIIZCARD_H
#define QUIZCARD_H

#include <QApplication>
#include <QMouseEvent>
#include <QString>
#include <QListWidgetItem>

class QuizCard : public QListWidgetItem {
public:
    QuizCard(QString english, QString pinyin, QString chinese);
private:
    QString englishText;
    QString pinyinText;
    QString chineseText;
    bool clicked;
    void mouseReleaseEvent(QMouseEvent * event);
signals:

public slots:
};

#endif // QUIZCARD_H
