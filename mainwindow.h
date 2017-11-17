#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Card.h"
#include "MyTextEdit.h"
#include "QuizCard.h"
#include <QMainWindow>
#include <QtCore>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVector>
#include <QFont>
#include <fstream>
#include <string>
#include <locale.h>
#include <QVector>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>
#include <QScrollArea>
#include <QListWidget>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool languageEnglish;
private:

    void initializeMenuButtons();
    void initializeBackButton();
    void initializeNewCard();
    void initializeNewQuiz();
    void hideMenu();
    void showMenu();
    void showNewCard();
    void hideNewCard();
    void applyTone(int toneNum);
    void showMakeQuizMenu();
    void hideQuizMenu();

    Ui::MainWindow *ui;

    QVector<QPushButton*> buttonList;
    QVector<MyTextEdit*> newCardList;
    QVector<QPushButton*> pinButtonList;

    //QObjects for main menu
    QLabel* titleLabel;
    QPushButton* newCardButton;
    QPushButton* newQuizButton;
    QPushButton* quizSelectButton;
    QPushButton* randomAllButton;
    QPushButton* lightningQuizButton;
    QPushButton* statisticsButton;
    QPixmap* pix1;
    QHBoxLayout *backGroundLayout;

    //QObject for every screen's back button
    QPushButton* backButton;

    //QObjects for new card menu
    MyTextEdit* englishText;
    MyTextEdit* pinyinText;
    MyTextEdit* chineseText;
    QPushButton* acceptNewCardButton;
    QPushButton* tone0Button;
    QPushButton* tone1Button;
    QPushButton* tone2Button;
    QPushButton* tone3Button;
    QPushButton* tone4Button;
    QVector<Card> cardList;
    QLabel* cardMadeLabel;


    //QObjects for new / Edit Quiz
    MyTextEdit* quizTitleText;
    QPushButton* makeNewQuizButton;
    QVector<QVector<Card>> quizList;
    QVBoxLayout* newQuizLayout;
    QListWidget* userCards;
    QScrollArea* cardArea;

    //Fonts
    QFont* titleFont = new QFont();
    QFont* cardFont = new QFont();
    QFont* pinyinButtonFont = new QFont();


    //Default widget heights/ widths
    int buttonHeight = 50;
    int buttonWidth = 350;

private slots:
    void on_newCardButton_clicked();
    void on_newQuizButton_clicked();
    void on_quizSelectButton_clicked();
    void on_randomAllButton_clicked();
    void on_lightningQuizButton_clicked();
    void on_statisticsButton_clicked();
    void on_backButton_clicked();
    void on_acceptNewCardButton_clicked();
    void on_tone0Button_clicked();
    void on_tone1Button_clicked();
    void on_tone2Button_clicked();
    void on_tone3Button_clicked();
    void on_tone4Button_clicked();
    void on_hideNewCardMadeLabel();
};

#endif // MAINWINDOW_H
