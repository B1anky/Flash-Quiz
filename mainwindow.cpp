#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    setWindowFlags(this->windowFlags() |= Qt::FramelessWindowHint);
    ui->setupUi(this);

    delete findChild<QToolBar *>(); // NULL return value is ok for delete
    delete findChild<QMenuBar *>(); // NULL return value is ok for delete

    /*
    this->resize(1920, 1040);
    heightRatio = 1;
    widthRatio = 1;
*/

    this->resize(1366, 740);
    heightRatio = .7114583333;
    widthRatio = .71111111;

    this->setFixedSize(1366, 740);

    languageEnglish = true;

    //All layouts for every page will be stored here for easy separation of show and hide
    masterLayout = new QStackedLayout();

    //Every single page's initializer primes their widgets
    initializeDragBar();
    initializeFonts();
    initializeExitAndMinimize();
    initializeFlashCard();
    initializeMenuButtons();
    initializeBackButton();
    initializeNotificationLabel();
    initializeNewCard();
    initializeNewQuiz();
    initializeOptions();
    initializeQuizSelect();
    resetFlashCardPalette();
    qDebug() << "desktop: " << QDesktopWidget().availableGeometry();

    this->centralWidget()->setLayout(masterLayout);
    masterLayout->setCurrentWidget(mainMenuWidget);
    //this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::initializeDragBar(){
    dragBarLabel = new DragBarLabel();
    dragBarLabel->setStyleSheet("background-color: rgba(0, 0, 0, 15);");
    dragBarLabel->setGeometry(QRect(0,0, this->width(), this->height() * .032));
    dragBarLabel->setParent(this);
}

void MainWindow::initializeExitAndMinimize(){
    //Need to add a simple Exit and minimize button
    exit = new HoverButton();
    exit->setMinimumSize(QSize(25 * heightRatio, 25 * widthRatio));
    exit->setMaximumSize(QSize(25 * heightRatio, 25 * widthRatio));
    exit->move((int)(this->width() * .985), (int)(this->height() * (.005 * heightRatio)));
    qDebug()<< "exit is as x: " << exit->x() << ", y: " << exit->y();
    exit->setText("X");
    exit->setFont(*exitAndMinimizeFont);
    exit->setStyleSheet("background-color: rgba(255, 255, 255, 25); font-weight: bold;");
    exit->raise();
    exit->setParent(this);


    minimize = new HoverButton();
    minimize->setMinimumSize(QSize(25 * heightRatio, 25 * widthRatio));
    minimize->setMaximumSize(QSize(25 * heightRatio, 25 * widthRatio));
    minimize->move((int)(this->width() * .97), (int)(this->height() * .005));
    minimize->setText("-");
    minimize->setFont(*exitAndMinimizeFont);
    minimize->setStyleSheet("background-color: rgba(255, 255, 255, 25); font-weight: bold;");
    minimize->raise();
    minimize->setParent(this);


    connect(exit, SIGNAL (released()), this, SLOT (exitClicked()));
    connect(minimize, SIGNAL (released()), this, SLOT (minimizeClicked()));
}

void MainWindow::exitClicked(){
    QApplication::quit();
}

void MainWindow::minimizeClicked(){
    this->showMinimized();
}

void MainWindow::initializeFlashCard(){
    //Flashcard set up
    backGround = new QLabel();
    backGround->setGeometry(QRect(0, 0, this->width(), this->height()));
    backGround->setMaximumHeight(this->width());
    backGround->setMaximumHeight(this->height());
    backGround->setMinimumHeight(this->width());
    backGround->setMinimumHeight(this->height());

    QPalette palette;
    pix1 = new QPixmap(":/new/pictures/flash-card.png");
    auto newPix = pix1->scaled(this->height(), this->width(), Qt::IgnoreAspectRatio , Qt::SmoothTransformation);
    palette.setBrush(QPalette::Background, newPix);
    this->setPalette(palette);
}

void MainWindow::initializeFonts(){
    //Font info
    cardFont->setPointSize(100 * heightRatio);
    textEditFont->setPointSize(25 * heightRatio);
    titleFont->setPointSize(50 * heightRatio);
    buttonFont->setPointSize(25 * heightRatio);
    pinyinButtonFont->setPointSize(12 * heightRatio);
    exitAndMinimizeFont->setPointSize(20 * heightRatio);
    exitAndMinimizeFont->setFamily("Arial Black");
}

void MainWindow::initializeNotificationLabel(){
    //Notification label will now be a global widget
    notificationLabel = new QLabel();
    notificationLabel->setText("Card was successfully created!");
    notificationLabel->setFont(*titleFont);
    notificationLabel->setMinimumWidth(this->width());
    notificationLabel->setMaximumHeight(buttonHeight + 25);
    notificationLabel->setStyleSheet("background-color: rgba(255, 255, 255, 100);");
    notificationLabel->setAttribute(Qt::WA_TranslucentBackground);
    notificationLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    notificationLabel->move(this->width()/2 - notificationLabel->width()/2 + (25 * widthRatio), this->height()/2  - notificationLabel->height()/2 - (300 * heightRatio));
    notificationLabel->setParent(this);
    notificationLabel->setAlignment(Qt::AlignCenter);
    notificationLabel->hide();
}

void MainWindow::newCardButtonClicked(){
    //Show the new card menu
    showNewCard();
}

void MainWindow::initializeQuizSelect(){
    quizSelectWidget = new QWidget();
    quizSelectLayout = new QGridLayout(quizSelectWidget);
    quizSelectLayout->setAlignment(Qt::AlignCenter);
    qDebug() << "a";
    quizGridLayoutWidget = new QWidget();
    quizGridLayout = new QGridLayout(quizGridLayoutWidget);
    quizInner = new QGridLayout();
    quizViewport = new QWidget();
    quizViewport->setGeometry(QRect(this->width()/2,this->height() * .05,this->width()/2,(950 * widthRatio)));
    quizViewport->setLayout(quizInner);
    qscrollArea = new QScrollArea;
    qscrollArea->setWidget(quizViewport);
    quizGridLayout->addWidget(qscrollArea);
    quizSelectLayout->addWidget(qscrollArea);
    quizGridLayout->setGeometry(QRect(this->width()/2,this->height() * .05,this->width()/2,(950 * widthRatio)));
    qDebug() << "B";
    verticalQuizSelectLayoutWidget = new QWidget();
    verticalQuizSelectLayout = new QVBoxLayout(verticalQuizSelectLayoutWidget);
    verticalQuizSelectLayoutWidget->setGeometry(QRect(this->width()/2,this->height() * .05,this->width()/2,(950 * widthRatio)));
    verticalQuizSelectLayoutWidget->setParent(quizSelectWidget);
    quizGridLayout->setParent(quizSelectWidget);
    qDebug() << "C";

        //Add the viewport to the scroll area
    //quizSelectLayout->addWidget(verticalQuizSelectLayoutWidget);
    //quizSelectLayout->addWidget(quizSelectWidget);
qDebug() <<"D";
    masterLayout->addWidget(quizSelectWidget);
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
    int ind = 0;

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

void MainWindow::tone0ButtonClicked(){
   applyTone(0);
}

void MainWindow::tone1ButtonClicked(){
   applyTone(1);
}

void MainWindow::tone2ButtonClicked(){
   applyTone(2);
}

void MainWindow::tone3ButtonClicked(){
   applyTone(3);
}

void MainWindow::tone4ButtonClicked(){
   applyTone(4);
}

void MainWindow::acceptNewCardButtonClicked(){
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
    //qDebug() << "moshi moshi!";
    if(cardMade){
        Card* newCard = new Card(englishText->toPlainText(), pinyinText->toPlainText(), chineseText->toPlainText());
        cardUpdater(*newCard);

        //notificationLabel->setText("New card Added!");
        //Fade in label
        //qDebug() << "I want to make a label!";
        fireAnimation();
        //qDebug() << "I made a label!";
        for(auto text: newCardTextEditList){
            text->setText(text->getDefaultText());
        }

    }
}

void MainWindow::hideNotificationLabel(){
    notificationLabel->hide();
}


void MainWindow::quizSelectButtonClicked(){
    showQuizSelect();
}

void MainWindow::showQuizSelect(){
    quizSelectLayout->addWidget(backButton, 0, 0);
    masterLayout->setCurrentWidget(quizSelectWidget);
}

void MainWindow::randomAllButtonClicked(){

}

void MainWindow::lightningQuizButtonClicked(){

}

void MainWindow::statisticsButtonClicked(){

}

void MainWindow::resetFlashCardPalette(){
    auto size = this->size();
    auto pixNew = pix1->scaled(size.width(), size.height(), Qt::KeepAspectRatioByExpanding , Qt::FastTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, pixNew);
    this->setPalette(palette);
}

void MainWindow::backButtonClicked(){
    showMenu();
    resetFlashCardPalette();
    backButton->hide();
}


void MainWindow::initializeNewQuiz(){
    //Quiz creation widget
    quizCreateWidget = new QWidget();
    quizCreateLayout = new QHBoxLayout(quizCreateWidget);

    verticalLayoutWidget = new QWidget();
    verticalLayout = new QVBoxLayout(verticalLayoutWidget);

    //QLabel* spacer = new QLabel();
    //spacer->setMinimumWidth(this->width()/2);
    //verticalLayout->addWidget(spacer);

    int offset = 2;
    //Text field for quiz names and selection
    quizTextEdit = new DropDownTextEdit(quizList);
    quizTextEdit->setMinimumSize(QSize(this->width()/2.2, buttonHeight));
    quizTextEdit->setMaximumSize(QSize(this->width()/2.2, buttonHeight));
    quizTextEdit->setDefaultText("Insert quiz name here");
    quizTextEdit->setText(quizTextEdit->getDefaultText());
    quizTextEdit->setFont(*textEditFont);
    quizTextEdit->move((this->width() * .255) - quizTextEdit->width()/2, (this->height() * .085) * offset + buttonHeight * 2);
    quizTextEdit->setParent(verticalLayoutWidget);

    //Quiz Creation buttons
    createEditQuizButton = new HoverButton();
    saveQuizButton = new HoverButton();
    loadQuizButton = new HoverButton();
    deleteQuizButton = new HoverButton();
    deleteSelectedCardsButton = new HoverButton();

    createEditQuizButton->setText("Create/Edit Quiz");
    saveQuizButton->setText("Save Quiz");
    loadQuizButton->setText("Load Quiz");
    deleteQuizButton->setText("Delete Quiz");
    deleteSelectedCardsButton->setText("Delete selected cards");

    quizCreateMenuButtonList = {createEditQuizButton, saveQuizButton, loadQuizButton, deleteQuizButton, deleteSelectedCardsButton};

    offset++;
    for(auto button: quizCreateMenuButtonList){
        button->setMaximumSize(QSize(buttonWidth, buttonHeight));
        button->setMinimumSize(QSize(buttonWidth, buttonHeight));
        button->setFont(*buttonFont);
        button->move((this->width() * .25) - button->width()/2, (this->height() * .085) * offset + buttonHeight * 2);
        button->setParent(verticalLayoutWidget);
        offset++;
    }

    gridLayoutWidget = new QWidget();
    gridLayout = new QGridLayout(gridLayoutWidget);
    inner = new QGridLayout();

    //Create a widget and set its layout as your new layout created above
    viewport = new QWidget();
    viewport->setGeometry(QRect(this->width()/2,this->height() * .05,this->width()/2,(950 * widthRatio)));
    viewport->setLayout(inner);

    //Add the viewport to the scroll area
    scrollArea = new QScrollArea;
    scrollArea->setWidget(viewport);
    gridLayout->addWidget(scrollArea);

    //Add the lest hand and right hand side to the main layout
    gridLayoutWidget->setGeometry(QRect(this->width()/2,this->height() * .05,this->width()/2,(950 * widthRatio)));
    verticalLayoutWidget->setGeometry(QRect(0,this->height() * .05,this->width()/2,(950 * widthRatio)));
    verticalLayoutWidget->setParent(quizCreateWidget);
    gridLayoutWidget->setParent(quizCreateWidget);

    //Add the quiz creation menu to the master layout
    masterLayout->addWidget(quizCreateWidget);

    //Connect signals and slots for buttons
    connect(createEditQuizButton, SIGNAL (released()), this, SLOT (createEditQuizButton_clicked()));
    connect(saveQuizButton, SIGNAL (released()), this, SLOT (saveQuizButton_clicked()));
    connect(loadQuizButton, SIGNAL (released()), this, SLOT (loadQuizButton_clicked()));
    connect(deleteQuizButton, SIGNAL (released()), this, SLOT (deleteQuizButton_clicked()));
    connect(deleteSelectedCardsButton, SIGNAL (released()), this, SLOT (deleteSelectedCardsButton_clicked()));
}

void MainWindow::cardUpdater(Card newCard){
    QuizCard *quizCard = new QuizCard(newCard, selectedCards);
    quizCard->setMinimumHeight(150);
    quizCard->setMinimumWidth(300);
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


void MainWindow::cardDisplayer(){
    for(int i = 0; i < physicalCardButtonList.size(); i++){
        inner->addWidget(physicalCardButtonList[i], i/2, i%2, Qt::AlignTop);
    }
}

void MainWindow::newQuizButtonClicked(){
    showMakeQuizMenu();
}

void MainWindow::optionsButtonClicked(){
    backButton->show();
    masterLayout->setCurrentWidget(optionsWidget);
}

void MainWindow::initializeOptions(){
    optionsWidget = new QWidget();

    //Need to add a scale factor for different resolutions
    //Current base scale is 1920 x 1040 (16:19)

    x1920x1040 = new HoverButton();
    x1366x740 = new HoverButton();

    QVector<int> resolutionCompareList = {1366 * 740, 1920 * 1040};
    resolutionButtonList = {x1366x740, x1920x1040};

    //Eliminate resolutions greater than current desktop's available geometry
    QRect usersDesktopRect = QDesktopWidget().availableGeometry();
    int usersWidth = usersDesktopRect.width();
    int usersHeight = usersDesktopRect.height();

    for(int i = resolutionCompareList.size() - 1; i >= 0; i--){
        if(usersWidth * usersHeight < resolutionCompareList[i]){
            resolutionCompareList.remove(i);
            resolutionButtonList.remove(i);
        }
    }

    int offset = 2;
    for(auto button: resolutionButtonList){
        button->setMinimumSize(buttonWidth, buttonHeight);
        button->setMaximumSize(buttonWidth, buttonHeight);
        button->setFont(*buttonFont);
        button->move((this->width() * .5) - button->width()/2, (this->height() * .088) * offset + buttonHeight * 2);
        button->setParent(optionsWidget);
        offset++;
    }

    x1366x740->setText("1366 x 766");
    x1920x1040->setText("1920 x 1080");

    masterLayout->addWidget(optionsWidget);

    connect(x1366x740, SIGNAL (released()), this, SLOT (resolutionChangedx1366x740()));
    connect(x1920x1040, SIGNAL (released()), this, SLOT (resolutionChangedx1920x1040()));


}

void MainWindow::resolutionChangedx1366x740(){
    //Mark their current resolution as used
    int currentHeight = this->height();
    int currentWidth = this->width();

    if(currentWidth != 1366 && currentHeight != 740){
        //Find the ratio of height and width for resizing all widgets
        heightRatio = .7114583333;
        widthRatio = .7115384615;
        //Reinitialize all windows to fix scale of widgets and then resize this
        this->setFixedSize(1366, 740);
        this->setGeometry(this->x() + 100, this->y() + 100, 1366, 740);
        reinitializeAll();
        //Prompt user to check if they like the change
    }

}

void MainWindow::resolutionChangedx1920x1040(){
    //Mark their current resolution as used
    int currentHeight = this->height();
    int currentWidth = this->width();

    if(currentWidth != 1920 && currentHeight != 1040){
        //Find the ratio of height and width for resizing all widgets
        heightRatio = 1;
        widthRatio = 1;
        //Reinitialize all windows to fix scale of widgets and then resize this
        this->setFixedSize(1920, 1040);
        this->setGeometry(0, 0, 1920, 1040);
        reinitializeAll();
        //Prompt user to check if they like the change
    }

}

/*
void MainWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}
*/

void MainWindow::reinitializeAll(){
    for(int i = 0; i < masterLayout->count(); i++){
        QWidget *widget = masterLayout->itemAt(i)->widget();
        if(widget){
            widget->deleteLater();
        }
    }


    backButton->deleteLater();
    titleLabel->deleteLater();
    notificationLabel->deleteLater();
    exit->deleteLater();
    minimize->deleteLater();
    dragBarLabel->deleteLater();

    buttonHeight = 50 * heightRatio;
    buttonWidth = 350 * widthRatio;

    initializeFonts();
    initializeFlashCard();
    resetFlashCardPalette();
    initializeMenuButtons();
    initializeBackButton();
    initializeNotificationLabel();
    initializeNewCard();
    initializeNewQuiz();
    initializeOptions();
    initializeDragBar();
    initializeExitAndMinimize();
    masterLayout->setCurrentWidget(optionsWidget);

    backButton->show();
    dragBarLabel->show();
    exit->show();
    minimize->show();

}

void MainWindow::initializeNewCard(){
    //Create widget and layout to add the masterLayout
    newCardWidget = new QWidget();

    //Add accept button to top left of grid layout
    acceptNewCardButton = new HoverButton;
    acceptNewCardButton->setMinimumWidth(buttonWidth);
    acceptNewCardButton->setMinimumHeight(buttonHeight);
    acceptNewCardButton->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
    acceptNewCardButton->setFont(*buttonFont);
    acceptNewCardButton->setText("Accept");
    acceptNewCardButton->setParent(newCardWidget);
    acceptNewCardButton->move((this->width() * .95) - buttonWidth, this->height() * .1);

    englishText = new MyTextEdit;
    pinyinText = new MyTextEdit;
    chineseText = new MyTextEdit;

    englishText->setDefaultText("Type English here");
    pinyinText->setDefaultText("Type Pinyin here");
    chineseText->setDefaultText("Type Chinese here");

    englishText->setText(englishText->getDefaultText());
    pinyinText->setText(pinyinText->getDefaultText());
    chineseText->setText(chineseText->getDefaultText());


    //Add the text edits to the grid layout
    newCardTextEditList = {englishText, pinyinText, chineseText};
    int offset = 1;
    for(auto text: newCardTextEditList){
        text->setMinimumHeight(buttonHeight);
        text->setMinimumWidth(2 * buttonWidth);
        text->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
        text->setFont(*buttonFont);
        text->setGeometry((int)((this->width() * .5) - text->width()/2), (int)(this->height() * .175) * offset + buttonHeight/4 + (95 * heightRatio), buttonWidth*2, buttonHeight);
        text->setParent(newCardWidget);
        offset++;
    }


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


    offset = 0;
    for(auto button: pinButtonList){
        button->setMinimumWidth(buttonWidth/9);
        button->setMinimumHeight(buttonHeight);
        button->setMaximumWidth(buttonWidth/9);
        button->setMaximumHeight(buttonHeight);
        button->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
        button->setFont(*pinyinButtonFont);
        button->move((int)((this->width() * .7) - button->width()/9) + offset * buttonWidth/9, (int)(this->height() * .175) * 2 + (buttonHeight/4 + (95 * heightRatio)));
        button->setParent(newCardWidget);
        offset+=2;
    }

    masterLayout->addWidget(newCardWidget);

    connect(acceptNewCardButton, SIGNAL (released()), this, SLOT (acceptNewCardButtonClicked()));

    connect(tone0Button, SIGNAL (released()), this, SLOT (tone0ButtonClicked()));
    connect(tone1Button, SIGNAL (released()), this, SLOT (tone1ButtonClicked()));
    connect(tone2Button, SIGNAL (released()), this, SLOT (tone2ButtonClicked()));
    connect(tone3Button, SIGNAL (released()), this, SLOT (tone3ButtonClicked()));
    connect(tone4Button, SIGNAL (released()), this, SLOT (tone4ButtonClicked()));

}

void MainWindow::initializeBackButton(){
    backButton = new HoverButton();
    backButton->setMaximumWidth(buttonWidth);
    backButton->setMaximumHeight(buttonHeight);
    backButton->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
    backButton->setFont(*buttonFont);
    backButton->move((this->width() * .05), this->height() * .1);
    backButton->setParent(this);
    backButton->setText("Back");
    backButton->hide();
    connect(backButton, SIGNAL (released()), this, SLOT (backButtonClicked()));
}

void MainWindow::initializeMenuButtons(){
    mainMenuWidget = new QWidget();
    mainMenuLayout = new QVBoxLayout(mainMenuWidget);

    titleLabel = new QLabel();
    newCardButton = new HoverButton();
    newQuizButton = new HoverButton();
    loadProfileButton = new HoverButton();
    quizSelectButton = new HoverButton();
    randomAllButton = new HoverButton();
    lightningQuizButton = new HoverButton();
    statisticsButton = new HoverButton();
    optionsButton = new HoverButton();

    buttonList = {newCardButton, newQuizButton, loadProfileButton, quizSelectButton, randomAllButton, lightningQuizButton, statisticsButton, optionsButton};

    if(languageEnglish == true){
        titleLabel->setText("Flash Quiz");
        newCardButton->setText("New Card");
        newQuizButton->setText("New / Edit Quiz");
        loadProfileButton->setText("Load Profile");
        quizSelectButton->setText("Quiz Select");
        randomAllButton->setText("Random All Test");
        lightningQuizButton->setText("Lightning Quiz");
        statisticsButton->setText("Statistics");
        optionsButton->setText("Options");
    }

    titleLabel->setMaximumWidth(buttonWidth * 2);
    titleLabel->setMaximumHeight(buttonHeight * 2);
    titleLabel->setMinimumWidth(buttonWidth * 2);
    titleLabel->setMinimumHeight(buttonHeight * 2);
    titleLabel->setFont(*titleFont);
    titleLabel->move((int)(this->width() * .5  - titleLabel->width()/4.5), (int)(this->height() * .1  - titleLabel->height()/2));
    titleLabel->setParent(mainMenuWidget);

    int offset = 2;
    for(auto button: buttonList){
        button->setMaximumWidth(buttonWidth);
        button->setMaximumHeight(buttonHeight);
        button->setStyleSheet("background-color: rgba(255, 255, 255, 25);");
        button->setFont(*buttonFont);
        button->move((this->width() * .5) - button->width()/2, (this->height() * .088) * offset + buttonHeight * 2);
        button->setParent(mainMenuWidget);
        offset++;
    }

    //add main menu layout to masterLayout
    masterLayout->addWidget(mainMenuWidget);

    connect(newCardButton, SIGNAL (released()), this, SLOT (newCardButtonClicked()));
    connect(newQuizButton, SIGNAL (released()), this, SLOT (newQuizButtonClicked()));
    connect(loadProfileButton, SIGNAL (released()), this, SLOT (loadProfileButtonClicked()));
    connect(quizSelectButton, SIGNAL (released()), this, SLOT (quizSelectButtonClicked()));
    connect(randomAllButton, SIGNAL (released()), this, SLOT (randomAllButtonClicked()));
    connect(lightningQuizButton, SIGNAL (released()), this, SLOT (lightningQuizButtonClicked()));
    connect(statisticsButton, SIGNAL (released()), this, SLOT (statisticsButtonClicked()));
    connect(optionsButton, SIGNAL (released()), this, SLOT(optionsButtonClicked()));
}

void MainWindow::loadProfileButtonClicked(){
    loadProfile(); //bool loaded =
    /*
    if(loaded){
        for(auto quiz : quizList){
            //qDebug() << quiz.first;
            for(auto card : *quiz.second){
                //qDebug() << *card;
            }
        }
    }
    */
}

bool MainWindow::loadProfile(){
    //qDebug() << "Loading profile";
    QString toParse;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Flash Quiz Profile"), "", tr("Flash Quiz File (*.fqf);;All Files (*)"));
    if(fileName.isEmpty()){
        return false;
    }else{
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return false;
        }

        QTextStream inStream(&file);
        inStream.setCodec("UTF-8");
        // clear existing profile
        quizList.clear();
        userCards.clear();
        selectedCards.clear();
        physicalCardButtonList.clear();

        QString line = inStream.readAll();
        int lineCnt = 0;

        QStringList fields = line.split("╫");
        for(int i = 0; i < fields.size() - 1; i++){
            if(i == 0){
                profileName = fields[0].remove("\n");
                lineCnt++;
            }else if(i == 1){
                QStringList curCard = fields[1].split("\n");

                for(int j = 1; j < curCard.size() - 3; j+=3){
                    QString english = curCard[j];
                    QString pinyin = curCard[j+1];
                    QString chinese = curCard[j+2];
                    Card* newCard = new Card(english, pinyin, chinese);
                    cardUpdater(*newCard);
                    //qDebug() << *newCard;
                }
            }else{
                //qDebug() <<"Quiz" << (i - 1);
                //Has to be a quiz
                QStringList curQuiz = fields[i].split("\n");
                QString* quizName = new QString(curQuiz[1]);
                QVector<Card*>* newQuizList = new QVector<Card*>();
                for(int j = 2; j < curQuiz.size() - 3; j += 3){
                    QString english = curQuiz[j];
                    QString pinyin = curQuiz[j+1];
                    QString chinese = curQuiz[j+2];
                    Card* newCard = new Card(english, pinyin, chinese);
                    newQuizList->push_back(newCard);
                    //qDebug() << "loop:" << *newCard;
                }

                quizList.push_back(QPair<QString, QVector<Card*>*>(*quizName, newQuizList));
            }
        }
    }


    quizTextEdit->updateCompleter(quizList);

    gridLayout->removeWidget(scrollArea);

    viewport = new QWidget;
    viewport->setLayout(inner);

    //Add the viewport to the scroll area
    scrollArea = new QScrollArea;
    scrollArea->setWidget(viewport);

    gridLayout->addWidget(scrollArea);

    //Revisualize the cards
    cardDisplayer();

    //qDebug() << "Done loading";
    notificationLabel->setText("Welcome back, " + profileName);
    fireAnimation();
    return true;
}

void MainWindow::showMakeQuizMenu(){
    backButton->show();
    this->setPalette(QPalette());
    masterLayout->setCurrentWidget(quizCreateWidget);
    quizTextEdit->clearFocus();
}

void MainWindow::showNewCard(){
    backButton->show();
    masterLayout->setCurrentWidget(newCardWidget);
}

void MainWindow::showMenu(){
    masterLayout->setCurrentWidget(mainMenuWidget);
}

void MainWindow::fireAnimation(){
    //Fade in label
    //qDebug() << "Animate!";
    //notificationLabel->raise();
    QGraphicsOpacityEffect *fadeInEff = new QGraphicsOpacityEffect(this);
    notificationLabel->setGraphicsEffect(fadeInEff);
    notificationLabel->show();
    QPropertyAnimation *fadeIn = new QPropertyAnimation(fadeInEff,"opacity");
    fadeIn->setDuration(5000);
    fadeIn->setStartValue(0);
    fadeIn->setEndValue(1);
    fadeIn->setEasingCurve(QEasingCurve::InBack);
    fadeIn->start(QPropertyAnimation::DeleteWhenStopped);

    //Fade out label
    QGraphicsOpacityEffect *fadeOutEff = new QGraphicsOpacityEffect(this);
    notificationLabel->setGraphicsEffect(fadeOutEff);
    QPropertyAnimation *fadeOut = new QPropertyAnimation(fadeOutEff,"opacity");
    //notificationLabel->lower();
    fadeOut->setDuration(5000);
    fadeOut->setStartValue(1);
    fadeOut->setEndValue(0);
    fadeOut->setEasingCurve(QEasingCurve::OutBack);
    fadeOut->start(QPropertyAnimation::DeleteWhenStopped);
    connect(fadeOut,SIGNAL(finished()),this,SLOT(hideNotificationLabel()));
}

//create a new quiz based on quizTextEdit's content
void MainWindow::createEditQuizButton_clicked(){
    //Search the quizList for the string pair name that corresponds to quizTextEdit's text
    //If there's a match, then we're updating/adding to a current quiz, otherwise we're appending a new quiz
    for(auto quiz = quizList.begin(); quiz != quizList.end(); ++quiz){
        if(quiz->first == quizTextEdit->text()){
            qInfo() << "Reassigning quiz->second";
            //Set up label text
            notificationLabel->setText(quiz->first + " has been updated!");
            for(auto card = selectedCards.begin(); card != selectedCards.end(); ++card){
                //qDebug() << **card;
            }
            quiz->second = new QVector<Card*>(selectedCards);
            fireAnimation();
            return;
        }
    }

    //otherwise need to append a new list to quizList
    quizList.push_back(QPair<QString, QVector<Card*>*>(quizTextEdit->text(), new QVector<Card*>(selectedCards)));

    //update the completer
    quizTextEdit->updateCompleter(quizList);
    notificationLabel->setText(quizTextEdit->text() + " has been created!");

    //setAnimation
    fireAnimation();
}

//This writes to the text file the quiz cards and quizzes
void MainWindow::saveQuizButton_clicked(){
    //First prompt the user for their profile name if it isn't currently set
    bool getNameOkay = false;

    MyInputDialog* getUserName = new MyInputDialog(nullptr, 750 * widthRatio, 200 * heightRatio, heightRatio);

    if(profileName == "Guest"){
        profileName = getUserName->getText(profileName, &getNameOkay);
    }else{
        profileName = getUserName->updateText(profileName, &getNameOkay);
    }

    if(profileName != "Guest" && getNameOkay){
        QString dialogPromptText = profileName + " would you like to save your Flash Quiz profile?";
        QString fileName = QFileDialog::getSaveFileName(this, tr(dialogPromptText.toStdString().c_str()), "", tr("Flash Quiz File(*.fqf);;All Files (*)"));

        if (fileName.isEmpty()){
            return;
        }else{
            QFile file(fileName);
            if(!file.open(QIODevice::WriteOnly)){
                QMessageBox::information(this, tr("Unable to open file"), file.errorString());
                return;
            }

            QTextStream out(&file);
            out.setCodec("UTF-8");

            //Construct the string to write to the file
            QString output =constructSaveFile();

            //Pushes the stream to the file and saves it
            out << output;
            out.flush();

            file.close();

            notificationLabel->setText(profileName + ", your profile has been saved!");
            fireAnimation();
        }
    }
}

QString MainWindow::constructSaveFile(){
    //This text file will consist of a name
    QString output = profileName + "\n";

    //alt 215
    output += "╫\n";

    for(auto card : userCards){
        output += card->getEnglish() + "\n";
        output += card->getPinyin() + "\n";
        output += card->getChinese() + "\n";
    }


    output += "╫\n";

    for(auto quiz : quizList){
        output += quiz.first + "\n";
        for(auto card : *quiz.second){
            output += card->getEnglish() + "\n";
            output += card->getPinyin() + "\n";
            output += card->getChinese() + "\n";
        }
        output += "╫\n";
    }

    return output;
}

//This reads a save file and loads into quizList and userCards
void MainWindow::loadQuizButton_clicked(){
    quizLoader(quizTextEdit->text());
    notificationLabel->setText(quizTextEdit->text() + " has been loaded!");
    fireAnimation();
}

void MainWindow::quizLoader(QString quizName){
    //Search through quiz and set physicalButtonList cards as selected
    //First find correct quiz in quizList
    for(auto quiz : quizList){
        if(quiz.first == quizName){
            //Reset selected Cards
            for(int i = 0; i < physicalCardButtonList.size(); i++){
                physicalCardButtonList[i]->setClicked(false);
                physicalCardButtonList[i]->setStyleSheet("");
            }

            selectedCards.clear();

            qInfo() << "Starting load loop";
            for(int i = 0; i < physicalCardButtonList.size(); i++){
                for(int j = 0; j < quiz.second->size(); j++){
                    if(physicalCardButtonList[i]->getCard() == *(quiz.second->operator[](j))){
                        //qInfo() << "Selecting card at index: " << i;
                        //qDebug() << "physicalCardButtonList[" << i << "]->getCard() = " << physicalCardButtonList[i]->getCard();
                        selectedCards.push_back(new Card(physicalCardButtonList[i]->getCard()));
                        physicalCardButtonList[i]->setClicked(true);
                        physicalCardButtonList[i]->setStyleSheet("background-color: rgb(255, 0, 0);");
                        break;
                    }
                }
            }
            // break because we found the quiz and there will only be one occurrance of it
            break;
        }
    }
}


//Clears quizList
void MainWindow::deleteQuizButton_clicked(){
    bool found = false;
    //Remove corresponding quizTextEdit's match from quizList
    for(int i = 0; i < quizList.size(); i++){
        if(quizList[i].first == quizTextEdit->text()){
            quizList.remove(i);
            qInfo() << "deleting quiz";
            found = true;
            //Reset selected Cards
            for(int i = 0; i < physicalCardButtonList.size(); i++){
                physicalCardButtonList[i]->setClicked(false);
                physicalCardButtonList[i]->setStyleSheet("");
            }
            selectedCards.clear();
            break;
        }
    }

    //update the completer
    quizTextEdit->updateCompleter(quizList);

    if(found){
        notificationLabel->setText(quizTextEdit->text() + " has been deleted!");
    }else{
        notificationLabel->setText(quizTextEdit->text() + " not found!");
    }

    fireAnimation();
}

void MainWindow::deleteSelectedCardsButton_clicked(){
    //O(n^2) solution maybe make better in the future
    //for every card in selectedCards, remove from userCards
    qInfo() << "Calling delete";

    //Loop through every quiz and remove the card from it first
    for(auto quiz : quizList){
        for(auto selectedCard : selectedCards){
            for(auto qCard : *quiz.second){
                if(*selectedCard == *qCard){
                    quiz.second->removeOne(qCard);
                }
            }
        }
    }

    for(int i = selectedCards.size() - 1; i >= 0; i--){
        for(int j = userCards.size() - 1; j >= 0; j--){
            if(userCards[j] && selectedCards[i] && !physicalCardButtonList.empty()){
                if(*userCards[j] == *selectedCards[i]){
                    userCards.remove(j);
                    selectedCards.remove(i);
                    inner->removeWidget(physicalCardButtonList[j]);
                    physicalCardButtonList.remove(j);
                }
                while(i > selectedCards.size()) i--;
                while(j > userCards.size()) j--;
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
    //masterLayout->setCurrentWidget(mainMenuWidget);
    //masterLayout->setCurrentWidget(quizWidget);

    notificationLabel->setText("Selected Card have been deleted!");
    fireAnimation();
}
