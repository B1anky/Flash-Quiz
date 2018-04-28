#ifndef DROPDOWNTEXTEDIT_H
#define DROPDOWNTEXTEDIT_H

#include "card.h"
#include <QCompleter>
#include <QStringList>
#include <QLineEdit>
#include <QVector>
#include <QPair>
#include <QString>

class DropDownTextEdit : public QLineEdit {
    Q_OBJECT
public:
    explicit DropDownTextEdit(QLineEdit *parent = nullptr);
    explicit DropDownTextEdit(QVector<QPair<QString, QVector<Card*>*>> quizList);
    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);
    void setDefaultText(QString str);
    QString getDefaultText();
    void updateCompleter(QVector<QPair<QString, QVector<Card*>*>> quizListIn);
private:
    QString defaultText;
    //QCompleter* stringCompleter;
    QStringList quizNames;

signals:

public slots:
};

#endif // DROPDOWNTEXTEDIT_H
