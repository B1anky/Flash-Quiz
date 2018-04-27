#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    delete findChild<QToolBar *>(); // NULL return value is ok for delete
    delete findChild<QMenuBar *>(); // NULL return value is ok for delete

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
    cardFont->setPointSize(100);
    textEditFont->setPointSize(25);
    initializeNewQuiz();
    hideQuizMenu();
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
    if(!(notDefaultEng || notDefaultPin || notDefaultChn)){
        cardMade = true;
    }else{
        QMessageBox::StandardButton question = QMessageBox::question(this, "Adding Card...","Warning, one of the fields are still incomplete, are you sure you would like to make the card?");
        QMessageBox::StandardButton userAnswer = question;
        if (userAnswer == QMessageBox::Yes){
            cardMade = true;
        }
    }

    if(cardMade){
        Card* newCard = new Card(englishText->toPlainText(), pinyinText->toPlainText(), chineseText->toPlainText());
        cardUpdater(*newCard);
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

void MainWindow::on_backButton_clicked(){
    hideNewCard();
    hideQuizMenu();
    showMenu();
}


void MainWindow::initializeNewQuiz(){
    backGround->setPixmap(*new QPixmap());
    verticalLayoutWidget = new QWidget(this->centralWidget());
    verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
    verticalLayoutWidget->setGeometry(QRect(10, 0, 951, 1021));
    verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalLayout->addItem(verticalSpacer_9);

    verticalLayout->addItem(verticalSpacer_5);

    quizTextEdit = new DropDownTextEdit(quizList);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(quizTextEdit->sizePolicy().hasHeightForWidth());
    quizTextEdit->setSizePolicy(sizePolicy);
    quizTextEdit->setMinimumSize(QSize(0, 50));
    quizTextEdit->setMaximumSize(QSize(1920, 50));
    quizTextEdit->setDefaultText("Insert quiz name here");
    quizTextEdit->setText(quizTextEdit->getDefaultText());
    quizTextEdit->setFont(*textEditFont);

    verticalLayout->addWidget(quizTextEdit);

    verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_6);

    verticalSpacer = new QSpacerItem(10, 1, QSizePolicy::Minimum, QSizePolicy::Fixed);

    verticalLayout->addItem(verticalSpacer);

    createEditQuizButton = new HoverButton();
    createEditQuizButton->setMinimumSize(QSize(0, 50));
    createEditQuizButton->setText("Create/Edit Quiz");
    createEditQuizButton->setFont(*buttonFont);
    verticalLayout->addWidget(createEditQuizButton);

    verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_2);

    saveQuizButton = new HoverButton();
    saveQuizButton->setText("Save Quiz");
    saveQuizButton->setMinimumSize(QSize(0, 50));
    saveQuizButton->setFont(*buttonFont);
    verticalLayout->addWidget(saveQuizButton);

    verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_4);

    loadQuizButton = new HoverButton();
    loadQuizButton->setText("Load Quiz");
    loadQuizButton->setMinimumSize(QSize(0, 50));
    loadQuizButton->setFont(*buttonFont);
    verticalLayout->addWidget(loadQuizButton);

    verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_7);

    deleteQuizButton = new HoverButton();
    deleteQuizButton->setText("Delete Quiz");
    deleteQuizButton->setMinimumSize(QSize(0, 50));
    deleteQuizButton->setFont(*buttonFont);
    verticalLayout->addWidget(deleteQuizButton);

    verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_3);

    deleteSelectedCardsButton = new HoverButton();
    deleteSelectedCardsButton->setText("Delete selected cards");
    deleteSelectedCardsButton->setMinimumSize(QSize(0, 50));
    deleteSelectedCardsButton->setFont(*buttonFont);
    verticalLayout->addWidget(deleteSelectedCardsButton);

    verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_8);


    gridLayoutWidget = new QWidget(this->centralWidget());
    gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(970, 10, 941, 1011));
    gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);


    inner = new QGridLayout;

    //Create a widget and set its layout as your new layout created above
    viewport = new QWidget;
    viewport->setLayout(inner);

    //Add the viewport to the scroll area
    scrollArea = new QScrollArea;
    scrollArea->setWidget(viewport);

    gridLayout->addWidget(scrollArea);

    //Connect signals and slots for buttons
    connect(createEditQuizButton, SIGNAL (released()), this, SLOT (createEditQuizButton_clicked()));
    connect(saveQuizButton, SIGNAL (released()), this, SLOT (saveQuizButton_clicked()));
    connect(loadQuizButton, SIGNAL (released()), this, SLOT (loadQuizButton_clicked()));
    connect(deleteQuizButton, SIGNAL (released()), this, SLOT (deleteQuizButton_clicked()));
    connect(deleteSelectedCardsButton, SIGNAL (released()), this, SLOT (deleteSelectedCardsButton_clicked()));
}

void MainWindow::cardUpdater(Card newCard){
    QuizCard *quizCard = new QuizCard(newCard, selectedCards);
    quizCard->setMinimumHeight(250);
    quizCard->setMinimumWidth(425);
    quizCard->setMaximumHeight(250);
    quizCard->setMaximumWidth(425);
    QPixmap *cardImg = new QPixmap(*pix1);
    QPainter painter(cardImg);
    painter.setFont(*cardFont);
    painter.drawText(QPoint(200, 285), quizCard->getCard().getEnglish());
    painter.drawText(QPoint(200, 540), quizCard->getCard().getPinyin());
    painter.drawText(QPoint(200, 800), quizCard->getCard().getChinese());
    QIcon ButtonIcon(*cardImg);
    quizCard->setIcon(ButtonIcon);
    quizCard->setIconSize(QSize(380, 315));
    userCards.push_back(quizCard->getCardRef());
    physicalCardButtonList.push_back(quizCard);
    inner->addWidget(quizCard, (userCards.size() - 1) / 2, (userCards.size() - 1) % 2, Qt::AlignTop);
}

void MainWindow::quizLoader(QString quizName){
    //Search through quiz and set physicalButtonList cards as selected
    //First find correct quiz in quizList
    for(auto quiz : quizList){
        if(quiz.first == quizName){
            //Reset selected Cards
            int i = 0;
            for(auto selection : selectedCards){
                if(*physicalCardButtonList[i]->getCardRef() == *selection){
                    physicalCardButtonList[i]->setClicked(false);
                    physicalCardButtonList[i]->setStyleSheet("");
                }
                i++;
            }
            selectedCards.clear();
            i = 0;
            for(auto card : quiz.second){
                if(*physicalCardButtonList[i]->getCardRef() == *card){
                    selectedCards.push_back(card);
                    physicalCardButtonList[i]->setClicked(true);
                    physicalCardButtonList[i]->setStyleSheet("background-color: rgb(255, 0, 0);");
                }
                i++;
            }

            break;
        }
    }
}

void MainWindow::cardDisplayer(){
    for(int i = 0; i < physicalCardButtonList.size(); i++){
        inner->addWidget(physicalCardButtonList[i], i/2, i%2, Qt::AlignTop);
    }
}

void MainWindow::on_newQuizButton_clicked(){
    backButton->show();
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
        text->setFont(*buttonFont);
        text->move(210 + 450, curY);
        text->setParent(this);
        text->hide();
        curY += buttonHeight * 2 + 30;
    }

    acceptNewCardButton = new HoverButton;

    acceptNewCardButton->setFixedWidth(buttonWidth);
    acceptNewCardButton->setFixedHeight(buttonHeight);
    acceptNewCardButton->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
    acceptNewCardButton->setFont(*buttonFont);
    acceptNewCardButton->move(210 + 750 + buttonWidth , 85);
    acceptNewCardButton->setParent(this);
    acceptNewCardButton->setText("Accept");
    acceptNewCardButton->hide();

    cardMadeLabel = new QLabel();
    cardMadeLabel->setText("Card was successfully created!");
    cardMadeLabel->setFont(*titleFont);
    cardMadeLabel->setMinimumWidth(this->width());
    cardMadeLabel->setMaximumHeight(buttonHeight + 25);
    cardMadeLabel->setStyleSheet("background-color: rgba(255, 255, 255, 100);");
    cardMadeLabel->move(this->width()/2 - cardMadeLabel->width()/2 + 25, this->height()/2  - cardMadeLabel->height()/2 - 235);
    cardMadeLabel->setParent(this);
    cardMadeLabel->setAlignment(Qt::AlignCenter);
    cardMadeLabel->hide();

    tone0Button = new HoverButton;
    tone1Button = new HoverButton;
    tone2Button = new HoverButton;
    tone3Button = new HoverButton;
    tone4Button = new HoverButton;

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
    backButton = new HoverButton();
    backButton->setFixedWidth(buttonWidth);
    backButton->setFixedHeight(buttonHeight);
    backButton->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
    backButton->setFont(*buttonFont);
    backButton->move(350 , 85);
    backButton->setParent(this);
    backButton->setText("Back");
    backButton->hide();
    connect(backButton, SIGNAL (released()), this, SLOT (on_backButton_clicked()));
}

void MainWindow::initializeMenuButtons(){
    titleLabel = new QLabel();
    newCardButton = new HoverButton();
    newQuizButton = new HoverButton();
    quizSelectButton = new HoverButton();
    randomAllButton = new HoverButton();
    lightningQuizButton = new HoverButton();
    statisticsButton = new HoverButton();

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
    buttonFont->setPointSize(25);

    titleLabel->setFixedWidth(buttonWidth * 2);
    titleLabel->setFixedHeight(buttonHeight * 2);
    titleLabel->setFont(*titleFont);
    titleLabel->move(960 - 250/2, 0);
    titleLabel->setParent(this);

    for(auto button: buttonList){
        button->setAttribute(Qt::WA_Hover, true);
        button->setFixedWidth(buttonWidth);
        button->setFixedHeight(buttonHeight);
        button->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
        button->setFont(*buttonFont);
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

    //Reset default background
    backGround->setPixmap(*new QPixmap());

    //add back button
    verticalLayout->insertWidget(1, backButton);
    backButton->show();

    viewport = new QWidget;
    viewport->setLayout(inner);

    gridLayout->removeWidget(scrollArea);

    //Add the viewport to the scroll area
    scrollArea = new QScrollArea;
    scrollArea->setWidget(viewport);

    gridLayout->addWidget(scrollArea);

    //Display the quiz editor menu
    verticalLayoutWidget->show();
    quizTextEdit->show();
    createEditQuizButton->show();
    saveQuizButton->show();
    loadQuizButton->show();
    deleteQuizButton->show();
    deleteSelectedCardsButton->show();
    viewport->show();
    gridLayoutWidget->show();

}

void MainWindow::hideQuizMenu(){
    //Hide quiz menu widgets
    quizTextEdit->setDefaultText(quizTextEdit->getDefaultText());
    quizTextEdit->hide();
    createEditQuizButton->hide();
    saveQuizButton->hide();
    loadQuizButton->hide();
    deleteQuizButton->hide();
    deleteSelectedCardsButton->hide();
    gridLayoutWidget->hide();
    verticalLayout->removeWidget(backButton);

    verticalLayout->removeWidget(backButton);
    backButton->deleteLater();
    initializeBackButton();
    backButton->show();
}

void MainWindow::showNewCard(){
    acceptNewCardButton->show();
    for(auto text: newCardList){
        text->show();
    }
    for(auto button: pinButtonList){
        button->show();
    }
    cardMadeLabel->setStyleSheet("background-color: rgba(0,0,0,0%)");
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

//create a new quiz based on quizTextEdit's content
void MainWindow::createEditQuizButton_clicked(){
    //Search the quizList for the string pair name that corresponds to quizTextEdit's text
    //If there's a match, then we're updating/adding to a current quiz, otherwise we're appending a new quiz
    for(auto& quiz: quizList){
        if(quiz.first == quizTextEdit->text()){
            qInfo() << "Reassigning quiz.second";
            for(auto card: selectedCards){
                qDebug() << *card;
            }
            quiz.second = QVector<Card*>(selectedCards);

            for(auto card: quiz.second){
                qDebug() << *card;
            }
            return;
        }
    }

    //otherwise need to append a new list to quizList
    quizList.push_back(QPair<QString, QVector<Card*>>(quizTextEdit->text(), selectedCards));

    //update the completer
    quizTextEdit->updateCompleter(quizList);
}

//This writes to the text file the quiz cards and quizzes
void MainWindow::saveQuizButton_clicked(){
    for(auto quiz: quizList){
        qInfo() << quiz.first;
        for(auto card : quiz.second){
            qInfo() << *card;
        }
    }
}

//This reads a save file and loads into quizList and userCards
void MainWindow::loadQuizButton_clicked(){
    quizLoader(quizTextEdit->text());
}

//Clears quizList
void MainWindow::deleteQuizButton_clicked(){
    //Remove corresponding quizTextEdit's match from quizList
    for(int i = 0; i < quizList.size(); i++){
        if(quizList[i].first == quizTextEdit->text()){
            quizList.remove(i);
            qInfo() << "deleting quiz";
            break;
        }
    }

    //update the completer
    quizTextEdit->updateCompleter(quizList);
}

void MainWindow::deleteSelectedCardsButton_clicked(){
    //O(n^2) solution maybe make better in the future
    //for every card in selectedCards, remove from userCards
    qInfo() << "Calling delete";

    for(int i = selectedCards.size() - 1; i >= 0; i--){
        for(int j = userCards.size() - 1; j >= 0; j--){
            if(userCards[j] == selectedCards[i]){
                userCards.remove(j);
                selectedCards.remove(i);
                inner->removeWidget(physicalCardButtonList[j]);
                physicalCardButtonList.remove(j);
            }
        }
    }

    //Create a widget and set its layout as your new layout created above
    gridLayout->removeWidget(scrollArea);

    viewport = new QWidget;
    viewport->setLayout(inner);

    //Add the viewport to the scroll area
    scrollArea = new QScrollArea;
    scrollArea->setWidget(viewport);

    gridLayout->addWidget(scrollArea);

    //Revisualize the cards
    cardDisplayer();

    hideQuizMenu();
    showMakeQuizMenu();

}
