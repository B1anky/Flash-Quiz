#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Card.h"
#include "MyTextEdit.h"
#include "QuizCard.h"
#include "HoverButton.h"
#include "QuizButton.h"
#include "ExitButton.h"
#include "MinimizeButton.h"
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
    void applyTone(int toneNum);
    void showMakeQuizMenu();
    void showLightningQuiz();
    void hideQuizMenu();
    void cardDisplayer();
    void fireAnimation();
    void reinitializeAll();
    void allCardUpdater();
    void setScrollAreaStyleSheet(QScrollArea* scrollA);
    void allQuizButtonUpdater();

    //If starting at 1920 x 1080
   /* float heightRatio = 1;
    float widthRatio = 1;
*/

    //If starting at 1366 x 740
    float heightRatio = .7114583333;
    float widthRatio = .71111111;

    QStackedLayout* masterLayout;
    QLabel* backGround;
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

    //Qlabel that will be the drag bar on top
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
    QLabel* titleLabel;
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
    QLabel* notificationLabel;


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
    QTimer* lightningQuizTimer;
    QLabel* lightningQuizCountdown;

    QWidget *quizSelectWidget;
    QVBoxLayout *quizSelectLayout;
    QWidget *quizSelectGridWidget;
    QGridLayout *gridQuizSelectLayout;

    QGridLayout *quizSelectScrollViewer;

    //Fonts
    QFont* titleFont = new QFont();
    QFont* buttonFont = new QFont();
    QFont* cardFont = new QFont();
    QFont* pinyinButtonFont = new QFont();
    QFont* textEditFont = new QFont();
    QFont* exitAndMinimizeFont = new QFont();


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

    void backButtonClicked();
    void resetFlashCardPalette();

    void acceptNewCardButtonClicked();
    void tone0ButtonClicked();
    void tone1ButtonClicked();
    void tone2ButtonClicked();
    void tone3ButtonClicked();
    void tone4ButtonClicked();
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
    void resolutionChangedx1920x1040();

};



#endif // MAINWINDOW_H
