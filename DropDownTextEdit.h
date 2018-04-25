#ifndef DROPDOWNTEXTEDIT_H
#define DROPDOWNTEXTEDIT_H

#include <QCompleter>
#include <QStringList>
#include <QLineEdit>

class DropDownTextEdit : public QLineEdit {
    Q_OBJECT
public:
    explicit DropDownTextEdit(QLineEdit *parent = nullptr);
    explicit DropDownTextEdit(QVector<QString> quizNames);
    void focusInEvent(QFocusEvent *e);
    void setDefaultText(QString str);
    QString getDefaultText();
private:
    QString defaultText;
    QCompleter* stringCompleter;
    QStringList quizNames;

signals:

public slots:
};

#endif // DROPDOWNTEXTEDIT_H
