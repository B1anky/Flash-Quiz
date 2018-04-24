#ifndef QUIZEDITOR_H
#define QUIZEDITOR_H

#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QTableWidget>

namespace Ui {
    class QuizEditor;
}

class QuizEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuizEditor(QWidget *parent = 0);
    ~QuizEditor();

private:
    Ui::QuizEditor *ui;
};

#endif // QUIZEDITOR_H
