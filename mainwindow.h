#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Card.h"
#include "MyTextEdit.h"
#include "QuizCard.h"
#include "QuizEditor.h"
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
#include <QPainter>


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
    void initializeQuizCreatorBackButton();
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
    QGridLayout *mainLayout;
    QLabel* backGround;

    QVector<QPushButton*> buttonList;
    QVector<MyTextEdit*> newCardList;
    QVector<QPushButton*> pinButtonList;
    QVector<Card*> userCards;

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
    QVector<Card> cardList = {Card("pls", "pls", "pls"), Card("pls", "pls", "pls")};
    QLabel* cardMadeLabel;


    //QObjects for new / Edit Quiz
    QGridLayout *inner;
    QWidget *viewport;
    QScrollArea *scrollArea;

    QWidget *quizWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer_1;
    QSpacerItem *verticalSpacer_5;
    QTextEdit *textEdit;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_7;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_3;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    //Fonts
    QFont* titleFont = new QFont();
    QFont* buttonFont = new QFont();
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
    void cardUpdater(Card newCard);
    void cardLoader();
};

#endif // MAINWINDOW_H
