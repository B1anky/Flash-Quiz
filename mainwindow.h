#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Card.h"
#include "MyTextEdit.h"
#include "QuizCard.h"
#include "HoverButton.h"
#include "QuizButton.h"
#include "ExitButton.h"
#include "MinimizeButton.h"
#include "DynamicFontSizeLabel.h"
#include "ClockThread.h"
#include <DragBarLabel.h>
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
#include <QResizeEvent>
#include <QStackedLayout>
#include <QThread>



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
    bool loadProfile();
    void initializeDragBar();
    void initializeExitAndMinimize();
    void initializeNotificationLabel();
    void initializeFonts();
    void initializeImageFiles();
    void initializeBackButton();
    void initializeQuizCreatorBackButton();
    void initializeNewCard();
    void initializeNewQuiz();
    void initializeOptions();
    void initializeQuizSelect();
    void initializeLightningQuiz();
    void hideMenu();
    void showMenu();
    void showNewCard();
    void hideNewCard();
    void applyTone(int toneNum, MyTextEdit* pinyinT);
    void showMakeQuizMenu();
    void showLightningQuiz();
    void hideQuizMenu();
    void cardDisplayer();
    void fireAnimation();
    void reinitializeAll();
    void allCardUpdater();
    void setScrollAreaStyleSheet(QScrollArea* scrollA);
    void allQuizButtonUpdater();
    void startStandardQuiz();
    bool lightningQuizRound();

    //If starting at 1920 x 1080
   /* float heightRatio = 1;
    float widthRatio = 1;
*/

    //If starting at 1366 x 740
    float heightRatio = .7114583333;
    float widthRatio = .71111111;

    QStackedLayout* masterLayout;
    DynamicFontSizeLabel* backGround;
    Ui::MainWindow *ui;

    QWidget* mainMenuWidget;
    QVBoxLayout *mainMenuLayout;

    QWidget* newCardWidget;
    //QGridLayout* newCardLayout;

    QWidget* quizCreateWidget;
    QHBoxLayout* quizCreateLayout;

    QWidget* optionsWidget;

    QVector<HoverButton*> buttonList;
    QVector<MyTextEdit*> newCardTextEditList;
    QVector<HoverButton*> pinButtonList;
    QVector<Card*> userCards;
    QVector<Card*> selectedCards;
    QMap<QString, QuizButton*> selectedQuizzes;
    QVector<QPair<QString, QVector<Card*>*>> quizList;
    QVector<QuizCard*> physicalCardButtonList;

    //Current profile's name
    QString profileName = "Guest";

    //DynamicFontSizeLabel that will be the drag bar on top
    DragBarLabel* dragBarLabel;

    //QObjects for Exit and minimize
    ExitButton* exit;
    MinimizeButton* minimize;

    //QObjects for options
    HoverButton* x1366x740;
    HoverButton* x1920x1040;
    QVector<int> resolutionCompareList;
    QVector<HoverButton*> resolutionButtonList;

    //QObjects for main menu
    DynamicFontSizeLabel* titleLabel;
    HoverButton* newCardButton;
    HoverButton* newQuizButton;
    HoverButton* loadProfileButton;
    HoverButton* quizSelectButton;
    HoverButton* randomAllButton;
    HoverButton* lightningQuizButton;
    HoverButton* statisticsButton;
    HoverButton* optionsButton;
    QPixmap* flashCardImageBase;
    QPixmap* penImageBase;
    QPixmap* flashCardImageScaled;
    QPixmap* penImageScaled;
    QPixmap* deskImageBase;
    QPixmap* deskImageScaled;
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
    DynamicFontSizeLabel* notificationLabel;


    //QObjects for new / Edit Quiz
    QGridLayout *inner;
    QWidget *viewport;
    QScrollArea *scrollArea;

    QWidget *quizWidget;
    QWidget *quizCreateVerticalWidget;
    QVBoxLayout *verticalLayout;

    DropDownTextEdit* quizTextEdit;
    HoverButton* createEditQuizButton;
    HoverButton* saveQuizButton;
    HoverButton* loadQuizButton;
    HoverButton* deleteQuizButton;
    HoverButton* deleteSelectedCardsButton;
    QVector<HoverButton*> quizCreateMenuButtonList;
    QWidget* gridLayoutWidget;
    QGridLayout* gridLayout;
    QWidget * quizViewport;
    QScrollArea *qscrollArea ;
    QVBoxLayout *quizInner;
    QWidget *quizGridLayoutWidget;
    QVBoxLayout *quizGridLayout;

    QRect lightingQuizQRect;
    QWidget* lightningQuizWidget;
    QVBoxLayout* lightningQuizLayout;
    QVBoxLayout* lightningQuizInner;
    QWidget* lightningQuizViewport;
    ClockThread* clockThread = nullptr;
    QLabel* lightningQuizCountdown = nullptr;

    //QObjects for Quiz select
    QWidget *quizSelectWidget;
    QVBoxLayout *quizSelectLayout;
    QWidget *quizSelectGridWidget;
    QGridLayout *gridQuizSelectLayout;
    QGridLayout *quizSelectScrollViewer;
    QVector<bool> standardQuizOptions;

    HoverButton* startQuizButton;
    HoverButton* studyQuizButton;
    QuizButton* englishSelectedButton;
    QuizButton* pinyinSelectedButton;
    QuizButton* chineseSelectedButton;


    //QObjects for standard quiz
    QVector<Card> standardQuizCards;
    QWidget* standardQuizWidget;
    HoverButton* nextCardButton;
    MyTextEdit* englishQuizText;
    MyTextEdit* pinyinQuizText;
    MyTextEdit* chineseQuizText;
    DynamicFontSizeLabel* remainingCardsLabel;
    DynamicFontSizeLabel* englishQuizLabel;
    DynamicFontSizeLabel* pinyinQuizLabel;
    DynamicFontSizeLabel* chineseQuizLabel;
    QVector<MyTextEdit*> standardQuizTextEditList;
    QVector<DynamicFontSizeLabel*> standardQuizTextLabel;
    HoverButton* tone0ButtonSQ;
    HoverButton* tone1ButtonSQ;
    HoverButton* tone2ButtonSQ;
    HoverButton* tone3ButtonSQ;
    HoverButton* tone4ButtonSQ;
    QVector<HoverButton*> pinButtonListSQ;
    QVector<Card>::iterator iteratorSQ;
    int cardCount;


    //Fonts
    QFont* titleFont = new QFont();
    QFont* buttonFont = new QFont();
    QFont* cardFont = new QFont();
    QFont* pinyinButtonFont = new QFont();
    QFont* cardTextEditFont = new QFont();
    QFont* quizNameTextEditFont = new QFont();
    QFont* exitAndMinimizeFont = new QFont();
    QFont* standardQuizFont = new QFont();


    //Default widget heights/ widths
    int buttonHeight = 50 * heightRatio;
    int buttonWidth = 350 * widthRatio;

private slots:
    void showQuizSelect();
    void exitClicked();
    void minimizeClicked();
    void newCardButtonClicked();
    void newQuizButtonClicked();
    void loadProfileButtonClicked();
    void quizSelectButtonClicked();
    void randomAllButtonClicked();
    void lightningQuizButtonClicked();
    void statisticsButtonClicked();
    void optionsButtonClicked();
    void lightningQuizStart();
    void beginStandardQuiz();

    void backButtonClicked();
    void resetFlashCardPalette();

    void acceptNewCardButtonClicked();
    void tone0ButtonClicked();
    void tone1ButtonClicked();
    void tone2ButtonClicked();
    void tone3ButtonClicked();
    void tone4ButtonClicked();

    void tone0ButtonClickedSQ();
    void tone1ButtonClickedSQ();
    void tone2ButtonClickedSQ();
    void tone3ButtonClickedSQ();
    void tone4ButtonClickedSQ();

    void hideNotificationLabel();

    void cardAdder(Card newCard);
    void createEditQuizButton_clicked();
    void saveQuizButton_clicked();
    QString constructSaveFile();
    void loadQuizButton_clicked();
    void quizLoader(QString quizName);
    void deleteQuizButton_clicked();
    void deleteSelectedCardsButton_clicked();

    void resolutionChangedx1366x740();
    void checkValidation();
    void resolutionChangedx1920x1040();

    void nextCardSQ();

};



#endif // MAINWINDOW_H
