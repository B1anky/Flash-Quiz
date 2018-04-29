#ifndef MYINPUTDIALOG_H
#define MYINPUTDIALOG_H

#include <QString>
#include <QDialog>
#include <QKeyEvent>
#include <QDebug>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>

class MyInputDialog : QDialog{
    Q_OBJECT
public:
    explicit MyInputDialog(QWidget* parent = nullptr, int height = 0, int width = 0);
    QString getText(QString profileName,  bool* okayPressed);
    QString updateText(QString profileName,  bool* okayPressed);
    void keyPressEvent(QKeyEvent *e) override;
private:
    QVBoxLayout* vbox;
    QLineEdit* textValue;
    QDialogButtonBox* buttonBox;
    QAction *exitAction;
private slots:
};

#endif // MYINPUTDIALOG_H
