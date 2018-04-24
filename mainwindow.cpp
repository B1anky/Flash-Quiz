#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    languageEnglish = true;

    backGroundLayout = new QHBoxLayout();

    //Flashcard set up
    int windowH = 1080;
    int windowW = 1500;
    backGround = new QLabel();
    backGround->setGeometry(QRect(203, 10, windowW, windowH));

    pix1 = new QPixmap(":/new/pictures/flash-card.png");
    backGround->setPixmap(*pix1);


    initializeMenuButtons();
    initializeBackButton();
    initializeNewCard();
    // don't init until button clicked initializeNewQuiz();
    showMenu();


    backGroundLayout->addWidget(backGround);
    backGroundLayout->setAlignment(Qt::AlignCenter);

    mainLayout = new QGridLayout(this);
    mainLayout->addLayout(backGroundLayout, 0, 0, Qt::AlignCenter);

    this->centralWidget()->setLayout(mainLayout);
    this->setWindowState(Qt::WindowMaximized);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newCardButton_clicked(){
    //Hide old menu
    hideMenu();
    //Show the new card menu
    showNewCard();
}

void MainWindow::applyTone(int toneNum){
    QString vowels = "aeiou";
    QString tones1 = "āēīōū";
    QString tones2 = "áéíóú";
    QString tones3 = "ǎěǐǒǔ";
    QString tones4 = "àèìòù";
    QVector<QString> toneCheck = {tones1, tones2, tones3, tones4};
    QTextCursor cursor = pinyinText->textCursor();
    QString oldText = pinyinText->toPlainText();
    QString str = cursor.selectedText();
    int olderAnchor;
    int oldPos;
    int oldLen;
    bool moveRight = true;
    int right = 0;
    int ind;

    //nothing highlighted
    if(str.size() == 0){
       cursor.setPosition(0);
       while(oldText[right] != ' ' && right < oldText.size()) right++;
       cursor.setPosition(right, QTextCursor::KeepAnchor);
       pinyinText->setTextCursor(cursor);
       str = cursor.selectedText();

    }else{
        //In case user manually selects right to left need to swap
        if(cursor.anchor() > cursor.position()){
            int temp = cursor.anchor();
            cursor.setPosition(cursor.position());
            cursor.setPosition(temp, QTextCursor::KeepAnchor);
        }

        while(oldText.mid(cursor.anchor(), oldText.size())[right] != ' ' && right < oldText.size()) right++;
        cursor.setPosition(cursor.anchor() + right, QTextCursor::KeepAnchor);
        pinyinText->setTextCursor(cursor);
        str = cursor.selectedText();
    }

    oldLen = str.length();
    olderAnchor = cursor.anchor();
    oldPos = cursor.position();

    //check if highlighted str contains pinyin already, if it does then skip everything else
    bool hasTone = true;
    int wordsSkipped = 0;
    int toneCnt = 0;
    while(hasTone){
        if(oldPos > oldText.size() - 1) break;
        toneCnt = 0;
        right = 0;
        for(auto tones : toneCheck){
            for(int i = 0; i < tones.length(); i++){
                if(str.contains(tones[i])){
                    toneCnt++;
                }
            }
        }
        if(toneCnt > 0){
            wordsSkipped++;
            qInfo() << "Tone found" << wordsSkipped;
            //found a pinyin tone, don't process this word at all, just skip ahead with new anchor
            qInfo() << "Original old anchor: " << olderAnchor;
            qInfo() << "Original old position: " << oldPos;
            cursor.setPosition(oldPos + 1);
            while(oldText.mid(oldPos + 1, oldText.size())[right] != ' ' && oldPos + 1 + right < oldText.size()) right++;
            qInfo() << "Right : " << right;
            cursor.setPosition(oldPos + 1 + right, QTextCursor::KeepAnchor);
            pinyinText->setTextCursor(cursor);
            str = cursor.selectedText();
            qInfo() << str;
            oldLen = str.length();
            olderAnchor = cursor.anchor();
            oldPos = cursor.position();
            qInfo() << "New old anchor: " << olderAnchor;
            qInfo() << "New old position: " << oldPos;

        }else{
            hasTone = false;
        }
    }

    QString pin;
    //a and e take precedence over all other vowels
    if(str.contains("a") || str.contains("e")){
        if(str.contains("a")){
            ind = str.indexOf("a");
            if(toneNum == 1){
                pin = tones1[0];
            }else if(toneNum == 2){
                pin = tones2[0];
            }else if(toneNum == 3){
                pin = tones3[0];
            }else if(toneNum == 4){
                pin = tones4[0];
            }

        }else{
            ind = str.indexOf("e");
            if(toneNum == 1){
                pin = tones1[1];
            }else if(toneNum == 2){
                pin = tones2[1];
            }else if(toneNum == 3){
                pin = tones3[1];
            }else if(toneNum == 4){
                pin = tones4[1];
            }
        }

        if(toneNum != 0){
            str.remove(ind, 1);
            str.insert(ind, pin);
            oldText.remove(olderAnchor, str.size());
            oldText.insert(olderAnchor, str);
        }
        pinyinText->setText(oldText);

    //ou takes next precedence after a and e
    }else if(str.contains("ou")){
        pin = "ōu";
        int ind = str.indexOf("ou");

        if(toneNum != 0){
            str.remove(ind, 2);
            str.insert(ind, pin);
            oldText.remove(olderAnchor, str.size());
            oldText.insert(olderAnchor, str);
        }
        pinyinText->setText(oldText);

    }else if(str.contains("i")|| str.contains("o")|| str.contains("u")){
        //work backwards from selection and find first vowel
        for(int i = str.size() - 1; i > 0; i--){
            if(vowels.contains(str[i])){
                ind = i;
                break;
            }
        }
        if(str[ind] == 'i'){
            if(toneNum == 1){
                pin = tones1[2];
            }else if(toneNum == 2){
                pin = tones2[2];
            }else if(toneNum == 3){
                pin = tones3[2];
            }else if(toneNum == 4){
                pin = tones4[2];
            }
        }else if(str[ind] == 'o'){
            if(toneNum == 1){
                pin = tones1[3];
            }else if(toneNum == 2){
                pin = tones2[3];
            }else if(toneNum == 3){
                pin = tones3[3];
            }else if(toneNum == 4){
                pin = tones4[3];
            }
        }else if(str[ind] == 'u'){
            if(toneNum == 1){
                pin = tones1[4];
            }else if(toneNum == 2){
                pin = tones2[4];
            }else if(toneNum == 3){
                pin = tones3[4];
            }else if(toneNum == 4){
                pin = tones4[4];
            }
        }

        if(toneNum != 0){
            str.remove(ind, 1);
            str.insert(ind, pin);
            oldText.remove(olderAnchor, str.size());
            oldText.insert(olderAnchor, str);
        }
        pinyinText->setText(oldText);
    }

    if(toneNum != 0){
        if(olderAnchor + str.size() >= oldText.size()){
            cursor.clearSelection();
            pinyinText->setTextCursor(cursor);
            moveRight = false;
        }
    }

    if(moveRight){
        cursor.setPosition(olderAnchor + oldLen + 1);
        cursor.setPosition(oldPos + oldLen + 1, QTextCursor::KeepAnchor);
        pinyinText->setTextCursor(cursor);
    }
}

void MainWindow::on_tone0Button_clicked(){
   applyTone(0);
}

void MainWindow::on_tone1Button_clicked(){
   applyTone(1);
}

void MainWindow::on_tone2Button_clicked(){
   applyTone(2);
}

void MainWindow::on_tone3Button_clicked(){
   applyTone(3);
}

void MainWindow::on_tone4Button_clicked(){
   applyTone(4);
}

void MainWindow::on_acceptNewCardButton_clicked(){
    //Check to make sure no fields contain their default values
    //if they do, bring up a dialogue
    bool notDefaultEng = englishText->toPlainText() == englishText->getDefaultText();
    bool notDefaultPin = pinyinText->toPlainText() == pinyinText->getDefaultText();
    bool notDefaultChn = chineseText->toPlainText() == chineseText->getDefaultText();
    bool cardMade = false;
    if(!(notDefaultEng && notDefaultPin && notDefaultChn)){
        cardMade = true;
    }else{
        QMessageBox::StandardButton question = QMessageBox::question(this, "Adding Card...","Warning, one of the fields are still incomplete, are you sure you would like to make the card?");
        QMessageBox::StandardButton userAnswer = question;
        if (userAnswer == QMessageBox::Yes){
            cardMade = true;
        }
    }

    if(cardMade){
        Card newCard(englishText->toPlainText(), pinyinText->toPlainText(), chineseText->toPlainText());
        cardList.push_back(newCard);

        //Fade in label
        QGraphicsOpacityEffect *fadeInEff = new QGraphicsOpacityEffect(this);
        cardMadeLabel->setGraphicsEffect(fadeInEff);
        cardMadeLabel->show();
        QPropertyAnimation *fadeIn = new QPropertyAnimation(fadeInEff,"opacity");
        fadeIn->setDuration(5000);
        fadeIn->setStartValue(0);
        fadeIn->setEndValue(1);
        fadeIn->setEasingCurve(QEasingCurve::InBack);
        fadeIn->start(QPropertyAnimation::DeleteWhenStopped);

        for(auto text: newCardList){
            text->setText(text->getDefaultText());
        }

        //Fade out label
        QGraphicsOpacityEffect *fadeOutEff = new QGraphicsOpacityEffect(this);
        cardMadeLabel->setGraphicsEffect(fadeOutEff);
        QPropertyAnimation *fadeOut = new QPropertyAnimation(fadeOutEff,"opacity");
        fadeOut->setDuration(5000);
        fadeOut->setStartValue(1);
        fadeOut->setEndValue(0);
        fadeOut->setEasingCurve(QEasingCurve::OutBack);
        fadeOut->start(QPropertyAnimation::DeleteWhenStopped);
        connect(fadeOut,SIGNAL(finished()),this,SLOT(on_hideNewCardMadeLabel()));
    }
}

void MainWindow::on_hideNewCardMadeLabel(){
    cardMadeLabel->hide();
}


void MainWindow::on_quizSelectButton_clicked(){

}

void MainWindow::on_randomAllButton_clicked(){

}

void MainWindow::on_lightningQuizButton_clicked(){

}

void MainWindow::on_statisticsButton_clicked(){

}
/*
void MainWindow::on_QuizEdit_backButton_clicked(){
    hideQuizMenu();
    showMenu();
}
*/
void MainWindow::on_backButton_clicked(){
    hideNewCard();
    hideQuizMenu();
    showMenu();
}


void MainWindow::initializeNewQuiz(){
    qInfo() << "Here 1";
    backGround->setPixmap(*new QPixmap());
    verticalLayoutWidget = new QWidget(this->centralWidget());
    verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
    verticalLayoutWidget->setGeometry(QRect(10, 0, 951, 1021));
    verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_5);

    textEdit = new QTextEdit(verticalLayoutWidget);
    textEdit->setObjectName(QStringLiteral("textEdit"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
    textEdit->setSizePolicy(sizePolicy);
    textEdit->setMinimumSize(QSize(0, 50));
    textEdit->setMaximumSize(QSize(16777215, 50));

    verticalLayout->addWidget(textEdit);

    verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_6);

    verticalSpacer = new QSpacerItem(10, 1, QSizePolicy::Minimum, QSizePolicy::Fixed);

    verticalLayout->addItem(verticalSpacer);

    pushButton = new QPushButton(verticalLayoutWidget);
    pushButton->setObjectName(QStringLiteral("pushButton"));
    pushButton->setMinimumSize(QSize(0, 50));

    verticalLayout->addWidget(pushButton);

    verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_2);

    pushButton_4 = new QPushButton(verticalLayoutWidget);
    pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
    pushButton_4->setMinimumSize(QSize(0, 50));

    verticalLayout->addWidget(pushButton_4);

    verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_4);

    pushButton_2 = new QPushButton(verticalLayoutWidget);
    pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
    pushButton_2->setMinimumSize(QSize(0, 50));

    verticalLayout->addWidget(pushButton_2);

    verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_7);

    pushButton_3 = new QPushButton(verticalLayoutWidget);
    pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
    pushButton_3->setMinimumSize(QSize(0, 50));

    verticalLayout->addWidget(pushButton_3);

    verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_3);

    gridLayoutWidget = new QWidget(this->centralWidget());
    gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(970, 10, 941, 1011));
    gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);

    qInfo() << "Here 2";

    inner = new QGridLayout;

    /*testing populating scroll area*/
    for(int i = 0; i < 50; i++){
        QPushButton *loop = new QPushButton();
        loop->setMinimumHeight(250);
        loop->setMinimumWidth(425);
        loop->setMaximumHeight(250);
        loop->setMaximumWidth(425);
        inner->addWidget(loop, i/2, i%2, Qt::AlignRight);
    }

    qInfo() << "Here 3";

    //Create a widget and set its layout as your new layout created above
    viewport = new QWidget;
    viewport->setLayout(inner);

    //Add the viewport to the scroll area
    scrollArea = new QScrollArea;
    scrollArea->setWidget(viewport);

    gridLayout->addWidget(scrollArea);
    qInfo() << "Here 4";
}

void MainWindow::on_newQuizButton_clicked(){
    hideMenu();
    backButton->show();
    initializeNewQuiz();
    showMakeQuizMenu();
}

void MainWindow::initializeNewCard(){
    englishText = new MyTextEdit;
    pinyinText = new MyTextEdit;
    chineseText = new MyTextEdit;

    englishText->setDefaultText("Type English here");
    pinyinText->setDefaultText("Type Pinyin here");
    chineseText->setDefaultText("Type Chinese here");

    englishText->setText(englishText->getDefaultText());
    pinyinText->setText(pinyinText->getDefaultText());
    chineseText->setText(chineseText->getDefaultText());

    newCardList = {englishText, pinyinText, chineseText};
    int curY = 410;
    for(auto text: newCardList){
        text->setFixedHeight(buttonHeight);
        text->setFixedWidth(2 * buttonWidth);
        text->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
        text->setFont(*cardFont);
        text->move(210 + 450, curY);
        text->setParent(this);
        text->hide();
        curY += buttonHeight * 2 + 30;
    }

    acceptNewCardButton = new QPushButton;

    acceptNewCardButton->setFixedWidth(buttonWidth);
    acceptNewCardButton->setFixedHeight(buttonHeight);
    acceptNewCardButton->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
    acceptNewCardButton->setFont(*cardFont);
    acceptNewCardButton->move(210 + 750 + buttonWidth , 85);
    acceptNewCardButton->setParent(this);
    acceptNewCardButton->setText("Accept");
    acceptNewCardButton->hide();

    cardMadeLabel = new QLabel();
    cardMadeLabel->setText("Card was successfully created!");
    cardMadeLabel->setFont(*titleFont);
    cardMadeLabel->setMinimumWidth(this->width());
    cardMadeLabel->setMinimumHeight(buttonHeight);
    cardMadeLabel->setStyleSheet("background-color: rgba(255, 255, 255, 100);");
    cardMadeLabel->move(this->width()/2 - cardMadeLabel->width()/2 + 25, this->height()/2  - cardMadeLabel->height()/2 - 235);
    cardMadeLabel->setParent(this);
    cardMadeLabel->setAlignment(Qt::AlignCenter);
    cardMadeLabel->hide();

    tone0Button = new QPushButton;
    tone1Button = new QPushButton;
    tone2Button = new QPushButton;
    tone3Button = new QPushButton;
    tone4Button = new QPushButton;

    pinButtonList = {tone0Button, tone1Button, tone2Button, tone3Button, tone4Button};

    tone0Button->setText("0");
    tone1Button->setText("1");
    tone2Button->setText("2");
    tone3Button->setText("3");
    tone4Button->setText("4");

    pinyinButtonFont->setPointSize(12);
    int curX = 210 + 800 + buttonWidth;
    for(auto button: pinButtonList){
        button->setFixedWidth(buttonWidth/9);
        button->setFixedHeight(buttonHeight);
        button->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
        button->setFont(*pinyinButtonFont);
        button->move(curX + 10, 410 + buttonHeight * 2 + 30);
        button->setParent(this);
        button->hide();
        curX += buttonWidth/9;
    }

    connect(acceptNewCardButton, SIGNAL (released()), this, SLOT (on_acceptNewCardButton_clicked()));
    connect(tone0Button, SIGNAL (released()), this, SLOT (on_tone0Button_clicked()));
    connect(tone1Button, SIGNAL (released()), this, SLOT (on_tone1Button_clicked()));
    connect(tone2Button, SIGNAL (released()), this, SLOT (on_tone2Button_clicked()));
    connect(tone3Button, SIGNAL (released()), this, SLOT (on_tone3Button_clicked()));
    connect(tone4Button, SIGNAL (released()), this, SLOT (on_tone4Button_clicked()));
}

void MainWindow::initializeBackButton(){
    backButton = new QPushButton();
    backButton->setFixedWidth(buttonWidth);
    backButton->setFixedHeight(buttonHeight);
    backButton->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
    backButton->setFont(*cardFont);
    backButton->move(350 , 85);
    backButton->setParent(this);
    backButton->setText("Back");
    backButton->hide();
    connect(backButton, SIGNAL (released()), this, SLOT (on_backButton_clicked()));
}

void MainWindow::initializeQuizCreatorBackButton(){
    backButton->hide();
    connect(backButton, SIGNAL (released()), this, SLOT (on_backButton_clicked()));
}

void MainWindow::initializeMenuButtons(){
    titleLabel = new QLabel();
    newCardButton = new QPushButton();
    newQuizButton = new QPushButton();
    quizSelectButton = new QPushButton();
    randomAllButton = new QPushButton();
    lightningQuizButton = new QPushButton();
    statisticsButton = new QPushButton();

    buttonList = {newCardButton, newQuizButton, quizSelectButton, randomAllButton, lightningQuizButton, statisticsButton};

    if(languageEnglish == true){
        titleLabel->setText("Flash Quiz");
        newCardButton->setText("New Card");
        newQuizButton->setText("New / Edit Quiz");
        quizSelectButton->setText("Quiz Select");
        randomAllButton->setText("Random All Test");
        lightningQuizButton->setText("Lightning Quiz");
        statisticsButton->setText("Statistics");
    }

    int curY = 215;

    titleFont->setPointSize(50);
    cardFont->setPointSize(25);

    titleLabel->setFixedWidth(buttonWidth * 2);
    titleLabel->setFixedHeight(buttonHeight * 2);
    titleLabel->setFont(*titleFont);
    titleLabel->move(960 - 250/2, 0);
    titleLabel->setParent(this);

    for(auto button: buttonList){
        button->setFixedWidth(buttonWidth);
        button->setFixedHeight(buttonHeight);
        button->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
        button->setFont(*cardFont);
        button->move(960 - 350/2 , curY);
        button->setParent(this);
        curY += buttonHeight * 2 + 30;
    }

    connect(newCardButton, SIGNAL (released()), this, SLOT (on_newCardButton_clicked()));
    connect(newQuizButton, SIGNAL (released()), this, SLOT (on_newQuizButton_clicked()));
    connect(quizSelectButton, SIGNAL (released()), this, SLOT (on_quizSelectButton_clicked()));
    connect(randomAllButton, SIGNAL (released()), this, SLOT (on_randomAllButton_clicked()));
    connect(lightningQuizButton, SIGNAL (released()), this, SLOT (on_lightningQuizButton_clicked()));
    connect(statisticsButton, SIGNAL (released()), this, SLOT (on_statisticsButton_clicked()));
}

void MainWindow::hideNewCard(){
    backButton->hide();
    acceptNewCardButton->hide();

    englishText->setText("Type English here");
    pinyinText->setText("Type Pinyin here");
    chineseText->setText("Type Chinese here");

    for(auto text : newCardList){
        text->hide();
    }

    for(auto pinButton : pinButtonList){
        pinButton->hide();
    }
    cardMadeLabel->hide();
}

void MainWindow::showMakeQuizMenu(){
    //Hide main menu
    hideMenu();
    //Display the quiz editor menu
    verticalLayoutWidget->show();
    textEdit->show();
    pushButton->show();
    pushButton_2->show();
    pushButton_3->show();
    pushButton_4->show();
    viewport->show();
    gridLayoutWidget->show();

}

void MainWindow::hideQuizMenu(){
    //Hide quiz menu widgets
    //quizWidget->hide();
    //verticalLayoutWidget->hide();
    textEdit->hide();
    pushButton->hide();
    pushButton_2->hide();
    pushButton_3->hide();
    pushButton_4->hide();
    gridLayoutWidget->hide();
}

void MainWindow::showNewCard(){
    acceptNewCardButton->show();
    backButton->show();
    for(auto text: newCardList){
        text->show();
    }
    for(auto button: pinButtonList){
        button->show();
    }
    cardMadeLabel->setStyleSheet("background-color: rgba(0,0,0,0%)");
    //cardMadeLabel->show();
}

void MainWindow::hideMenu(){
    titleLabel->hide();
    for(auto card : buttonList){
        card->hide();
    }
    backButton->show();
}

void MainWindow::showMenu(){
    backButton->hide();
    backGround->setPixmap(*pix1);
    titleLabel->show();
    newCardButton->show();
    newQuizButton->show();
    quizSelectButton->show();
    randomAllButton->show();
    lightningQuizButton->show();
    statisticsButton->show();
}
