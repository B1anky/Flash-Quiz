#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QApplication>
#include <QTextEdit>
#include <QString>

class MyTextEdit : public QTextEdit {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QTextEdit)
public:
    Q_DECLARE_FLAGS(AutoFormatting, AutoFormattingFlag)
    explicit MyTextEdit(QTextEdit *parent = nullptr);
    void setDefaultText(QString str);
    QString getDefaultText();
private:
    QString defaultText;
    void focusInEvent(QFocusEvent * event);
    void focusOutEvent(QFocusEvent* event);
signals:

public slots:
};

#endif // MYTEXTEDIT_H
