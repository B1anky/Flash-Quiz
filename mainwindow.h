#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Card.h"
#include "MyTextEdit.h"
#include "QuizCard.h"
#include "QuizEditor.h"
#include "HoverButton.h"
#include <MyInputDialog.h>
#include <DropDownTextEdit.h>
#include <QMainWindow>
#include <QtCore>
#include <QLabel>
#include <QHBoxLayout>
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
#include <QPair>
#include <QFileDialog>
#include <QInputDialog>
#include <QSizePolicy>
#include <QDesktopWidget>


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
    virtual int heightForWidth ( int w ) const { return w*9/16;};
private:

    void initializeMenuButtons();
    bool loadProfile();
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
    void cardDisplayer();

    Ui::MainWindow *ui;
    QGridLayout *mainLayout;
    QLabel* backGround;

    QVector<HoverButton*> buttonList;
    QVector<MyTextEdit*> newCardList;
    QVector<HoverButton*> pinButtonList;
    QVector<Card*> userCards;
    QVector<Card*> selectedCards;
    QVector<QPair<QString, QVector<Card*>*>> quizList;
    QVector<QuizCard*> physicalCardButtonList;

    //Current profile's name
    QString profileName = "Guest";

    //QObjects for main menu
    QLabel* titleLabel;
    HoverButton* newCardButton;
    HoverButton* newQuizButton;
    HoverButton* loadProfileButton;
    HoverButton* quizSelectButton;
    HoverButton* randomAllButton;
    HoverButton* lightningQuizButton;
    HoverButton* statisticsButton;
    QPixmap* pix1;
    QHBoxLayout *backGroundLayout;

    //QObject for every screen's back button
    HoverButton* backButton;

    //QObjects for new card menu
    MyTextEdit* englishText;
    MyTextEdit* pinyinText;
    MyTextEdit* chineseText;
    HoverButton* acceptNewCardButton;
    HoverButton* tone0Button;
    HoverButton* tone1Button;
    HoverButton* tone2Button;
    HoverButton* tone3Button;
    HoverButton* tone4Button;
    //QVector<Card> cardList;
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
    DropDownTextEdit *quizTextEdit;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer;
    HoverButton *createEditQuizButton;
    QSpacerItem *verticalSpacer_2;
    HoverButton *saveQuizButton;
    QSpacerItem *verticalSpacer_4;
    HoverButton *loadQuizButton;
    QSpacerItem *verticalSpacer_7;
    HoverButton *deleteQuizButton;
    QSpacerItem *verticalSpacer_3;
    HoverButton *deleteSelectedCardsButton;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_9;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    //Fonts
    QFont* titleFont = new QFont();
    QFont* buttonFont = new QFont();
    QFont* cardFont = new QFont();
    QFont* pinyinButtonFont = new QFont();
    QFont* textEditFont = new QFont();


    //Default widget heights/ widths
    int buttonHeight = 50;
    int buttonWidth = 350;

private slots:
    void on_newCardButton_clicked();
    void on_newQuizButton_clicked();
    void on_loadProfileButton_clicked();
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
    void createEditQuizButton_clicked();
    void saveQuizButton_clicked();
    QString constructSaveFile();
    void loadQuizButton_clicked();
    void quizLoader(QString quizName);
    void deleteQuizButton_clicked();
    void deleteSelectedCardsButton_clicked();
};

#endif // MAINWINDOW_H
