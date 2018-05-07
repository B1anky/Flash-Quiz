#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    setWindowFlags(this->windowFlags() |= Qt::FramelessWindowHint);
    ui->setupUi(this);

    delete findChild<QToolBar *>(); // NULL return value is ok for delete
    delete findChild<QMenuBar *>(); // NULL return value is ok for delete


    /*this->resize(1920, 1040);
    heightRatio = 1;
    widthRatio = 1;
    this->setFixedSize(1920, 1040);
*/

    this->resize(1366, 740);
    heightRatio = .71145833;
    widthRatio = .71111111;
    this->setFixedSize(1366, 740);

    languageEnglish = true;

    //All layouts for every page will be stored here for easy separation of show and hide
    masterLayout = new QStackedLayout();

    //Every single page's initializer primes their widgets
    initializeDragBar();
    initializeFonts();
    initializeExitAndMinimize();
    initializeImageFiles();
    initializeMenuButtons();
    initializeBackButton();
    initializeNotificationLabel();
    initializeNewCard();
    initializeNewQuiz();
    initializeOptions();
    initializeQuizSelect();
    initializeLightningQuiz();
    resetFlashCardPalette();

    this->centralWidget()->setLayout(masterLayout);
    masterLayout->setCurrentWidget(mainMenuWidget);
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
    exit = new ExitButton();
    exit->setMinimumSize(QSize(this->height() * .04, this->height() * .032));
    exit->setMaximumSize(QSize(this->height() * .04, this->height() * .032));
    exit->move((int)(this->width() * .979), 0);
    qDebug()<< "exit is as x: " << exit->x() << ", y: " << exit->y();
    exit->setText("X");
    exit->setFont(*exitAndMinimizeFont);
    //exit->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    exit->raise();
    exit->setParent(this);


    minimize = new MinimizeButton();
    minimize->setMinimumSize(QSize(this->height() * .04, this->height() * .032));
    minimize->setMaximumSize(QSize(this->height() * .04, this->height() * .032));
    minimize->move((int)(this->width() * .959), 0);
    minimize->setText("-");
    minimize->setFont(*exitAndMinimizeFont);
    minimize->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
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

void MainWindow::initializeImageFiles(){
    //Flashcard set up
    backGround = new DynamicFontSizeLabel();
    backGround->setGeometry(QRect(0, 0, this->width(), this->height()));
    backGround->setMaximumHeight(this->width());
    backGround->setMaximumHeight(this->height());
    backGround->setMinimumHeight(this->width());
    backGround->setMinimumHeight(this->height());

    flashCardImageBase = new QPixmap(":/pictures/flash-card.png");
    flashCardImageScaled = new QPixmap(flashCardImageBase->scaled(this->height(), this->width(), Qt::IgnoreAspectRatio , Qt::SmoothTransformation));

    penImageBase = new QPixmap(":/pictures/penImage.png");
    penImageScaled = new QPixmap(penImageBase->scaled(this->height(), this->width(), Qt::IgnoreAspectRatio , Qt::SmoothTransformation));

    deskImageBase = new QPixmap(":/pictures/desk.png");
    deskImageScaled = new QPixmap(deskImageBase->scaled(this->height(), this->width(), Qt::IgnoreAspectRatio , Qt::SmoothTransformation));

    QPalette palette;
    palette.setBrush(QPalette::Background, *flashCardImageScaled);
    this->setPalette(palette);
}

void MainWindow::initializeFonts(){
    //Font info
    cardFont->setPointSize(100 * heightRatio);
    textEditFont->setPointSize(35 * heightRatio);
    titleFont->setPointSize(50 * heightRatio);
    buttonFont->setPointSize(25 * heightRatio);
    pinyinButtonFont->setPointSize(16 * heightRatio);
    exitAndMinimizeFont->setPointSize(20 * heightRatio);
    standardQuizFont->setPointSize(50 * heightRatio);
    exitAndMinimizeFont->setFamily("Verdana");
}

void MainWindow::initializeNotificationLabel(){
    //Notification label will now be a global widget
    notificationLabel = new DynamicFontSizeLabel();
    notificationLabel->setText("Card was successfully created!");
    notificationLabel->setFont(*titleFont);
    notificationLabel->setMinimumWidth(this->width());
    notificationLabel->setMinimumHeight(buttonHeight + 25);
    notificationLabel->setMaximumWidth(this->width());
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
    standardQuizOptions = {false, false, false};

    QRect quizSelectQRect(QRect(this->width() * .1, this->height() * .05, this->width() * .95, this->height() * .95));
    QRect quizSelectScrollQRect(QRect(this->width() * .125, this->height() * .2, this->width() * .75, this->height() * .65));
    QRect quizSelectScrollQRect2(QRect(this->width() * .125, this->height() * .2, this->width() * .75, 50 * buttonHeight));


    quizSelectWidget = new QWidget();
    quizSelectWidget->setGeometry(quizSelectQRect);
    quizSelectWidget->setStyleSheet("border: transparent;");

    quizSelectLayout = new QVBoxLayout(quizSelectWidget);
    quizSelectLayout->setGeometry(quizSelectScrollQRect);

    quizSelectGridWidget = new QWidget();
    quizSelectGridWidget->setGeometry(quizSelectScrollQRect);
    quizGridLayout = new QVBoxLayout(quizSelectGridWidget);

    quizInner = new QVBoxLayout();

    quizViewport = new QWidget();
    quizViewport->setGeometry(quizSelectScrollQRect2);
    quizViewport->setLayout(quizInner);
    quizViewport->setParent(quizSelectGridWidget);

    qscrollArea = new QScrollArea();
    qscrollArea->setWidget(quizViewport);

    quizGridLayout->addWidget(qscrollArea);
    quizSelectGridWidget->setParent(quizSelectWidget);
    setScrollAreaStyleSheet(qscrollArea);

    //Add buttons for accept, and selection
    startQuizButton = new HoverButton();
    startQuizButton->setText("Begin Quiz");
    startQuizButton->setFont(*buttonFont);
    startQuizButton->setMaximumSize(QSize(buttonWidth, buttonHeight));
    startQuizButton->setMinimumSize(QSize(buttonWidth, buttonHeight));
    startQuizButton->move((this->width() * .95) - buttonWidth, this->height() * .1);
    startQuizButton->setParent(quizSelectWidget);

    //Add button for studying
    studyQuizButton = new HoverButton();
    studyQuizButton->setText("Study Chapters");
    studyQuizButton->setFont(*buttonFont);
    studyQuizButton->setMaximumSize(QSize(buttonWidth, buttonHeight));
    studyQuizButton->setMinimumSize(QSize(buttonWidth, buttonHeight));
    studyQuizButton->move(this->width() * .05 + 2 * buttonWidth, this->height() * .1);
    studyQuizButton->setParent(quizSelectWidget);

    englishSelectedButton = new QuizButton(nullptr, &standardQuizOptions);
    pinyinSelectedButton = new QuizButton(nullptr, &standardQuizOptions);
    chineseSelectedButton = new QuizButton(nullptr, &standardQuizOptions);

    QVector<QuizButton*> userQuizOptionsButtons = {englishSelectedButton, pinyinSelectedButton, chineseSelectedButton};
    englishSelectedButton->setText("English Mode");
    pinyinSelectedButton->setText("Pinyin Mode");
    chineseSelectedButton->setText("Chinese Mode");

    int offset = 0;
    for(auto button: userQuizOptionsButtons){
        button->setMaximumSize(QSize(buttonWidth, buttonHeight));
        button->setMinimumSize(QSize(buttonWidth, buttonHeight));
        button->setFont(*buttonFont);
        button->move(this->width() * .05 + offset * buttonWidth, this->height() * .875);
        button->setParent(quizSelectWidget);
        offset+=2;
    }
    masterLayout->addWidget(quizSelectWidget);

    connect(startQuizButton, SIGNAL (released()), this, SLOT (beginStandardQuiz()));
    connect(englishSelectedButton, SIGNAL (released()), this, SLOT (checkValidation()));
    connect(pinyinSelectedButton, SIGNAL (released()), this, SLOT (checkValidation()));
    connect(chineseSelectedButton, SIGNAL (released()), this, SLOT (checkValidation()));
}

void MainWindow::checkValidation(){
    //Check if we need to hide a third button so it cannot be clicked
    if(standardQuizOptions[0] == true && standardQuizOptions[1] == true){
        chineseSelectedButton->setEnabled(false);
    }else if(standardQuizOptions[0] == true && standardQuizOptions[2] == true){
        pinyinSelectedButton->setEnabled(false);
    }else if(standardQuizOptions[1] == true && standardQuizOptions[2] == true){
        englishSelectedButton->setEnabled(false);
    }else{
        englishSelectedButton->setEnabled(true);
        pinyinSelectedButton->setEnabled(true);
        chineseSelectedButton->setEnabled(true);
    }

}

void MainWindow::beginStandardQuiz(){
    int selectedOptions = 0;
    for(auto option: standardQuizOptions){
        if(option) selectedOptions++;
    }

    if(selectedOptions){
        //Add every card from a selected quiz
        for(auto quizButton: selectedQuizzes){
            if(quizButton->selected == true){
                //pull every card from the quizList with the same name
                auto curQuizName = quizButton->text();
                for(auto quiz : quizList){
                    if(quiz.first == curQuizName){
                        for(auto card: *(quiz.second)){
                            standardQuizCards.push_back(*card);
                        }
                    }
                }
            }
        }

        //Check if the user added at least 1 card
        if(!standardQuizCards.empty()){
            //Sort cards with lambda
            std::sort(std::begin(standardQuizCards), std::end(standardQuizCards),
                      [] (const auto& lhs, const auto& rhs) {
                return lhs.getEnglish() < rhs.getEnglish();
            });

            //Remove cards by using unique iterator
            auto it = std::unique(standardQuizCards.begin(), standardQuizCards.end());
            standardQuizCards.resize(std::distance(standardQuizCards.begin(), it));

            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(standardQuizCards.begin(), standardQuizCards.end(), std::default_random_engine(seed));

            //Shuffle the cards in no particular order so it's random every time with the same quizzes
            for(auto card: standardQuizCards){
                qDebug() << card;
            }


            //Create widget and layout to add the masterLayout
            standardQuizWidget = new QWidget();

            nextCardButton = new HoverButton();
            nextCardButton->setMinimumWidth(buttonWidth);
            nextCardButton->setMinimumHeight(buttonHeight);
            nextCardButton->setStyleSheet("background-color: rgba(255, 255, 255);");
            nextCardButton->setFont(*buttonFont);
            nextCardButton->setText("Next Card");
            nextCardButton->setParent(standardQuizWidget);
            nextCardButton->move((this->width() * .95) - buttonWidth, this->height() * .1);

            cardCount = standardQuizCards.size() - 1;
            remainingCardsLabel = new DynamicFontSizeLabel();
            remainingCardsLabel->setMinimumWidth(buttonWidth);
            remainingCardsLabel->setMinimumHeight(buttonHeight);
            remainingCardsLabel->setMaximumWidth(buttonWidth);
            remainingCardsLabel->setMaximumHeight(buttonHeight);
            remainingCardsLabel->setText("Remaining cards: " + QString::number(cardCount));
            remainingCardsLabel->setParent(standardQuizWidget);
            remainingCardsLabel->setAlignment(Qt::AlignCenter);
            remainingCardsLabel->move((this->width() * .6) - buttonWidth, this->height() * .1);

            //User input on previous page influences what is added to the page

            //Add accept button to top left of grid layout
            englishQuizText = new MyTextEdit();
            pinyinQuizText = new MyTextEdit();
            chineseQuizText = new MyTextEdit();

            englishQuizLabel = new DynamicFontSizeLabel();
            pinyinQuizLabel = new DynamicFontSizeLabel();
            chineseQuizLabel = new DynamicFontSizeLabel();

            englishQuizText->setDefaultText("Type English here");
            pinyinQuizText->setDefaultText("Type Pinyin here");
            chineseQuizText->setDefaultText("Type Chinese here");

            englishQuizText->setText(englishQuizText->getDefaultText());
            pinyinQuizText->setText(pinyinQuizText->getDefaultText());
            chineseQuizText->setText(chineseQuizText->getDefaultText());

            //Add the text edits to the grid layout
            standardQuizTextEditList = {englishQuizText, pinyinQuizText, chineseQuizText};
            int offset = 1;
            for(auto text: standardQuizTextEditList){
                text->setMinimumHeight(buttonHeight * 1.5);
                text->setMinimumWidth(2 * buttonWidth);
                text->setMaximumHeight(buttonHeight * 1.5);
                text->setMaximumWidth(2 * buttonWidth);
                text->setStyleSheet("background-color: rgba(255, 255, 255);");
                text->setFont(*textEditFont);
                text->setGeometry((int)((this->width() * .5) - text->width()/2), (int)(this->height() * .175) * offset + (95 * heightRatio), buttonWidth*2, buttonHeight * 1.5);
                text->setParent(standardQuizWidget);
                offset++;
            }

            standardQuizTextLabel = {englishQuizLabel, pinyinQuizLabel, chineseQuizLabel};
            offset = 1;
            for(auto text: standardQuizTextLabel){
                text->setMinimumHeight(2 * buttonHeight);
                text->setMinimumWidth(this->width() * .9);
                text->setMaximumHeight(2 * buttonHeight);
                text->setMaximumWidth(this->width() * .9);
                text->setStyleSheet("background-color: rgba(255, 255, 255,0); color: black;");
                text->setFont(*standardQuizFont);
                text->move((int)((this->width() * .5) - text->width()/2), (int)(this->height() * .175) * offset + buttonHeight/4 + (85 * heightRatio));
                text->setParent(standardQuizWidget);
                text->setAlignment(Qt::AlignCenter);
                offset++;
            }

            tone0ButtonSQ = new HoverButton();
            tone1ButtonSQ = new HoverButton();
            tone2ButtonSQ = new HoverButton();
            tone3ButtonSQ = new HoverButton();
            tone4ButtonSQ = new HoverButton();

            pinButtonListSQ = {tone0ButtonSQ, tone1ButtonSQ, tone2ButtonSQ, tone3ButtonSQ, tone4ButtonSQ};

            tone0ButtonSQ->setText("0");
            tone1ButtonSQ->setText("1");
            tone2ButtonSQ->setText("2");
            tone3ButtonSQ->setText("3");
            tone4ButtonSQ->setText("4");


            offset = 0;
            for(auto button: pinButtonListSQ){
                button->setMinimumWidth(buttonWidth/9);
                button->setMinimumHeight(buttonHeight);
                button->setMaximumWidth(buttonWidth/9);
                button->setMaximumHeight(buttonHeight);
                button->setStyleSheet("background-color: rgba(255, 255, 255);");
                button->setFont(*pinyinButtonFont);
                button->move((int)((this->width() * .7) - button->width()/9) + offset * buttonWidth/9, (int)(this->height() * .175) * 2 + (buttonHeight/4 + (95 * heightRatio)));
                button->setParent(standardQuizWidget);
                offset+=2;
            }

            QPalette palette;
            palette.setBrush(QPalette::Background, *flashCardImageScaled);
            this->setPalette(palette);

            masterLayout->addWidget(standardQuizWidget);

            connect(tone0ButtonSQ, SIGNAL (released()), this, SLOT (tone0ButtonClickedSQ()));
            connect(tone1ButtonSQ, SIGNAL (released()), this, SLOT (tone1ButtonClickedSQ()));
            connect(tone2ButtonSQ, SIGNAL (released()), this, SLOT (tone2ButtonClickedSQ()));
            connect(tone3ButtonSQ, SIGNAL (released()), this, SLOT (tone3ButtonClickedSQ()));
            connect(tone4ButtonSQ, SIGNAL (released()), this, SLOT (tone4ButtonClickedSQ()));
            connect(nextCardButton, SIGNAL(released()), this, SLOT(nextCardSQ()));

            //Set up page to have what is necessary for user's options
            if(standardQuizOptions[0]){
                englishQuizText->setParent(nullptr);
            }else{
                 englishQuizLabel->setParent(nullptr);
            }

            if(standardQuizOptions[1]){
                pinyinQuizText->setParent(nullptr);
                for(auto button: pinButtonListSQ){
                    button->setParent(nullptr);
                }
            }else{
                pinyinQuizLabel->setParent(nullptr);
            }

            if(standardQuizOptions[2]){
                chineseQuizText->setParent(nullptr);
            }else{
                chineseQuizLabel->setParent(nullptr);
            }

            masterLayout->setCurrentWidget(standardQuizWidget);

            //Begin the quiz since all conditions have been met
            iteratorSQ = standardQuizCards.begin();
            startStandardQuiz();

        }else{
            //Display the notification label with message
            notificationLabel->setText("A quiz with at least one card must be added");
            notificationLabel->setStyleSheet("color:white;");
            fireAnimation();
        }
    }else{
        //Display the notification label with message
        notificationLabel->setText("You must select at least one mode");
        notificationLabel->setStyleSheet("color:white;");
        fireAnimation();
    }
}

void MainWindow::startStandardQuiz(){
    //Do different things based on the user's options
    //Have an iterator point to the first index of the quiz cards
    //The next card button will cause the iterator to move forward
    //and update the necessary widgets

    if(standardQuizOptions[0]){
        englishQuizLabel->setText(iteratorSQ->getEnglish());
    }

    if(standardQuizOptions[1]){
        pinyinQuizLabel->setText(iteratorSQ->getPinyin());
    }

    if(standardQuizOptions[2]){
        chineseQuizLabel->setText(iteratorSQ->getChinese());
    }


}

void MainWindow::nextCardSQ(){
    //Check if the user input the correct value and display the notification accordingly
    bool correct = true;

    //Users options will determine which we check
    if(!standardQuizOptions[0]){
        correct = englishQuizText->toPlainText() == iteratorSQ->getEnglish();
    }

    if(!standardQuizOptions[1]){
        correct = pinyinQuizText->toPlainText() == iteratorSQ->getPinyin();
    }

    if(!standardQuizOptions[2]){
        correct = chineseQuizText->toPlainText() == iteratorSQ->getChinese();
    }

    englishQuizText->setText(englishQuizText->getDefaultText());
    pinyinQuizText->setText(pinyinQuizText->getDefaultText());
    chineseQuizText->setText(chineseQuizText->getDefaultText());

    if(correct){
        notificationLabel->setText("Good job!");
        fireAnimation();
    }else{
        notificationLabel->setText("Incorrect");
        fireAnimation();
    }

    auto itCheck = iteratorSQ;
    if(++itCheck == standardQuizCards.end() - 1){
        nextCardButton->setText("Finish Quiz");
    }

    if(iteratorSQ != standardQuizCards.end() - 1){
        cardCount--;
        remainingCardsLabel->setText("Remaining cards: " + QString::number(cardCount));
        ++iteratorSQ;
        startStandardQuiz();
    }else{
        QPalette palette;
        palette.setBrush(QPalette::Background, *deskImageScaled);
        this->setPalette(palette);
        masterLayout->setCurrentWidget(quizSelectWidget);
    }
}

void MainWindow::applyTone(int toneNum, MyTextEdit* pinyinT){
    QString vowels = "aeiou";
    QString tones1 = "āēīōū";
    QString tones2 = "áéíóú";
    QString tones3 = "ǎěǐǒǔ";
    QString tones4 = "àèìòù";
    QVector<QString> toneCheck = {tones1, tones2, tones3, tones4};
    QTextCursor cursor = pinyinT->textCursor();
    QString oldText = pinyinT->toPlainText();
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
       pinyinT->setTextCursor(cursor);
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
        pinyinT->setTextCursor(cursor);
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
            pinyinT->setTextCursor(cursor);
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
        pinyinT->setText(oldText);

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
        pinyinT->setText(oldText);

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
        pinyinT->setText(oldText);
    }

    if(toneNum != 0){
        if(olderAnchor + str.size() >= oldText.size()){
            cursor.clearSelection();
            pinyinT->setTextCursor(cursor);
            moveRight = false;
        }
    }

    if(moveRight){
        cursor.setPosition(olderAnchor + oldLen + 1);
        cursor.setPosition(oldPos + oldLen + 1, QTextCursor::KeepAnchor);
        pinyinT->setTextCursor(cursor);
    }
}

void MainWindow::tone0ButtonClicked(){
   applyTone(0, pinyinText);
}

void MainWindow::tone1ButtonClicked(){
   applyTone(1, pinyinText);
}

void MainWindow::tone2ButtonClicked(){
   applyTone(2, pinyinText);
}

void MainWindow::tone3ButtonClicked(){
   applyTone(3, pinyinText);
}

void MainWindow::tone4ButtonClicked(){
   applyTone(4, pinyinText);
}

//This is for standard quiz pinyin text editor
void MainWindow::tone0ButtonClickedSQ(){
   applyTone(0, pinyinQuizText);
}

void MainWindow::tone1ButtonClickedSQ(){
   applyTone(1, pinyinQuizText);
}

void MainWindow::tone2ButtonClickedSQ(){
   applyTone(2, pinyinQuizText);
}

void MainWindow::tone3ButtonClickedSQ(){
   applyTone(3, pinyinQuizText);
}

void MainWindow::tone4ButtonClickedSQ(){
   applyTone(4, pinyinQuizText);
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
    if(cardMade){
        Card* newCard = new Card(englishText->toPlainText(), pinyinText->toPlainText(), chineseText->toPlainText());
        cardAdder(*newCard);

        //Create a widget and set its layout as your new layout created above
        gridLayout->removeWidget(scrollArea);
        scrollArea->deleteLater();
        viewport->deleteLater();

        viewport = new QWidget();
        viewport->setLayout(inner);

        //Add the viewport to the scroll area
        scrollArea = new QScrollArea;
        scrollArea->setWidget(viewport);
        setScrollAreaStyleSheet(scrollArea);
        gridLayout->addWidget(scrollArea);

        //Revisualize the cards
        cardDisplayer();

        notificationLabel->setText("New card Added!");
        //Fade in label
        fireAnimation();

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
    backButton->show();
    deskImageScaled = new QPixmap(deskImageBase->scaled(this->width(), this->height(), Qt::IgnoreAspectRatio , Qt::SmoothTransformation));
    QPalette palette;
    palette.setBrush(QPalette::Background, *deskImageScaled);
    this->setPalette(palette);
    masterLayout->setCurrentWidget(quizSelectWidget);
}

void MainWindow::randomAllButtonClicked(){

}

void MainWindow::lightningQuizButtonClicked(){
    showLightningQuiz();
}

void MainWindow::initializeLightningQuiz(){
    QRect lightningQuizQRect(QRect(this->width() * .1, this->height() * .05, this->width() * .95, this->height() * .95));
    lightningQuizWidget = new QWidget();
    lightningQuizWidget->setGeometry(lightingQuizQRect);
    lightningQuizWidget->setStyleSheet("border: transparent;");

    lightningQuizLayout = new QVBoxLayout(lightningQuizWidget);
    lightningQuizLayout->setGeometry(lightingQuizQRect);

    lightningQuizInner = new QVBoxLayout();

    lightningQuizViewport = new QWidget();
    lightningQuizViewport->setGeometry(lightingQuizQRect);
    lightningQuizViewport->setLayout(lightningQuizInner);
    lightningQuizViewport->setParent(lightningQuizWidget);

<<<<<<< HEAD
    HoverButton* lightningQuizButton = new HoverButton();
    lightningQuizButton->setText("Button Quiz");
    lightningQuizButton->setFont(*buttonFont);
    lightningQuizButton->setMaximumSize(QSize(buttonWidth, buttonHeight));
    lightningQuizButton->setMinimumSize(QSize(buttonWidth, buttonHeight));
    lightningQuizButton->move((this->width() * .60) - buttonWidth, this->height() * .50);
    lightningQuizButton->setParent(lightningQuizWidget);
=======
    lightningQuizCountdown = new QLabel(this);
    lightningQuizCountdown->setVisible(true);
    lightningQuizCountdown->move((this->width() * .60) - buttonWidth, this->height() * .45);

    QFont f( "Arial", 30, QFont::Bold);
    lightningQuizCountdown->setFont( f);
    lightningQuizCountdown->setParent(lightningQuizWidget);
>>>>>>> 85345a5ee25935e78317811fb6565ff1c8e502b6

    masterLayout->addWidget(lightningQuizWidget);
}

void MainWindow::showLightningQuiz(){
    backButton->show();
    masterLayout->setCurrentWidget((lightningQuizWidget));
    lightningQuizTimer = new QTimer();
    connect(lightningQuizTimer,SIGNAL(timeout()), this, SLOT(lightningQuizStart()));
    qint32 timeLeft = 0;
    QTimer::singleShot(3000, [&](){
        lightningQuizCountdown->setText(QString( "%1" ).arg(timeLeft++));
    });
}

void MainWindow::lightningQuizStart(){
<<<<<<< HEAD
   qDebug() << "Quiz has started";
=======

   qDebug() << "hello";
>>>>>>> 85345a5ee25935e78317811fb6565ff1c8e502b6
}


void MainWindow::statisticsButtonClicked(){

}

void MainWindow::resetFlashCardPalette(){
    flashCardImageScaled = new QPixmap(flashCardImageBase->scaled(this->width(), this->height(), Qt::KeepAspectRatioByExpanding, Qt::FastTransformation));

    penImageScaled = new QPixmap(penImageBase->scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    deskImageScaled = new QPixmap(deskImageBase->scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    QPalette palette;
    palette.setBrush(QPalette::Background, *flashCardImageScaled);
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

    quizCreateVerticalWidget = new QWidget();
    verticalLayout = new QVBoxLayout(quizCreateVerticalWidget);

    int offset = 2;
    //Text field for quiz names and selection
    quizTextEdit = new DropDownTextEdit(quizList);
    quizTextEdit->setMinimumSize(QSize(this->width()/2.2, buttonHeight * 1.5));
    quizTextEdit->setMaximumSize(QSize(this->width()/2.2, buttonHeight * 1.5));
    quizTextEdit->setDefaultText("Insert quiz name here");
    quizTextEdit->setText(quizTextEdit->getDefaultText());
    quizTextEdit->setFont(*textEditFont);
    quizTextEdit->move((this->width() * .255) - quizTextEdit->width()/2, (this->height() * .085) * offset + buttonHeight * 1.5);
    quizTextEdit->setParent(quizCreateVerticalWidget);

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
        button->setParent(quizCreateVerticalWidget);
        offset++;
    }

    gridLayoutWidget = new QWidget();
    gridLayout = new QGridLayout(gridLayoutWidget);
    inner = new QGridLayout();
    gridLayoutWidget->setStyleSheet("border: transparent;");


    //Create a widget and set its layout as your new layout created above
    viewport = new QWidget();
    viewport->setGeometry(QRect(this->width()/2,this->height() * .05,this->width()/2,(950 * widthRatio)));
    viewport->setLayout(inner);

    //Add the viewport to the scroll area
    scrollArea = new QScrollArea;
    scrollArea->setWidget(viewport);
    setScrollAreaStyleSheet(scrollArea);
    gridLayout->addWidget(scrollArea);

    //Add the lest hand and right hand side to the main layout
    gridLayoutWidget->setGeometry(QRect(this->width()/2,this->height() * .05,this->width()/2,(950 * widthRatio)));
    quizCreateVerticalWidget->setGeometry(QRect(0,this->height() * .05,this->width()/2,(950 * widthRatio)));
    quizCreateVerticalWidget->setParent(quizCreateWidget);
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

void MainWindow::allCardUpdater(){
    selectedCards.clear();
    physicalCardButtonList.clear();

    int i = 0;
    for(auto card: userCards){
        QuizCard *quizCard = new QuizCard(*card, selectedCards);
        quizCard->setMinimumHeight(265 * heightRatio);
        quizCard->setMinimumWidth(440 * widthRatio);
        quizCard->setMaximumHeight(265 * heightRatio);
        quizCard->setMaximumWidth(440 * widthRatio);
        QPixmap *cardImg = new QPixmap(*flashCardImageScaled);
        QPainter painter(cardImg);
        painter.setFont(*cardFont);
        painter.drawText(QPoint(200 * widthRatio, 355 * heightRatio), quizCard->getCard().getEnglish());
        painter.drawText(QPoint(200 * widthRatio, 625 * heightRatio), quizCard->getCard().getPinyin());
        painter.drawText(QPoint(200 * widthRatio, 900 * heightRatio), quizCard->getCard().getChinese());
        QIcon ButtonIcon(*cardImg);
        quizCard->setIcon(ButtonIcon);
        quizCard->setIconSize(QSize(400 * widthRatio, 225 * heightRatio));
        physicalCardButtonList.push_back(quizCard);
        inner->addWidget(physicalCardButtonList[i], i/2, i%2, Qt::AlignTop);
        i++;
    }

    //Create a widget and set its layout as your new layout created above
    gridLayout->removeWidget(scrollArea);
    scrollArea->deleteLater();
    viewport->deleteLater();

    viewport = new QWidget();
    viewport->setLayout(inner);

    //Add the viewport to the scroll area
    scrollArea = new QScrollArea;
    scrollArea->setWidget(viewport);
    setScrollAreaStyleSheet(scrollArea);
    gridLayout->addWidget(scrollArea);

    //Revisualize the cards
    cardDisplayer();
}

void MainWindow::cardAdder(Card newCard){
    QuizCard *quizCard = new QuizCard(newCard, selectedCards);
    quizCard->setMinimumHeight(265 * heightRatio);
    quizCard->setMinimumWidth(440 * widthRatio);
    quizCard->setMaximumHeight(265 * heightRatio);
    quizCard->setMaximumWidth(440 * widthRatio);
    QPixmap *cardImg = new QPixmap(*flashCardImageScaled);
    QPainter painter(cardImg);
    painter.setFont(*cardFont);
    painter.drawText(QPoint(200 * widthRatio, 355 * heightRatio), quizCard->getCard().getEnglish());
    painter.drawText(QPoint(200 * widthRatio, 625 * heightRatio), quizCard->getCard().getPinyin());
    painter.drawText(QPoint(200 * widthRatio, 900 * heightRatio), quizCard->getCard().getChinese());
    QIcon ButtonIcon(*cardImg);
    quizCard->setIcon(ButtonIcon);
    quizCard->setIconSize(QSize(400 * widthRatio, 225 * heightRatio));
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
    initializeImageFiles();
    resetFlashCardPalette();
    initializeMenuButtons();
    initializeBackButton();
    initializeNotificationLabel();
    initializeNewCard();
    initializeNewQuiz();
    initializeQuizSelect();
    initializeOptions();
    initializeDragBar();
    initializeExitAndMinimize();
    allCardUpdater();
    allQuizButtonUpdater();

    masterLayout->setCurrentWidget(optionsWidget);

    backButton->show();
    dragBarLabel->show();
    exit->show();
    minimize->show();
}

void MainWindow::allQuizButtonUpdater(){
    for(auto button : selectedQuizzes){
        quizInner->removeWidget(button);
        button->deleteLater();
    }

    selectedQuizzes.clear();

    for(int i = 0; i < quizList.size(); i++){
        QuizButton* button = new QuizButton(nullptr, nullptr);
        button->setText(quizList[i].first);
        button->setFont(*buttonFont);
        button->setMinimumSize(buttonWidth, buttonHeight);
        button->setMaximumSize(buttonWidth, buttonHeight);
        button->setParent(quizViewport);
        button->move(quizSelectGridWidget->width()/2 - buttonWidth/2, (((i * buttonHeight) + ((i + 1) * 20)) * heightRatio) + (heightRatio * 75));
        selectedQuizzes[quizList[i].first] = button;
    }

}

void MainWindow::initializeNewCard(){
    //Create widget and layout to add the masterLayout
    newCardWidget = new QWidget();

    //Add accept button to top left of grid layout
    acceptNewCardButton = new HoverButton;
    acceptNewCardButton->setMinimumWidth(buttonWidth);
    acceptNewCardButton->setMinimumHeight(buttonHeight);
    acceptNewCardButton->setStyleSheet("background-color: rgba(255, 255, 255);");
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
        text->setStyleSheet("background-color: rgba(255, 255, 255);");
        text->setFont(*textEditFont);
        text->setGeometry((int)((this->width() * .5) - text->width()/2), (int)(this->height() * .175) * offset + (95 * heightRatio), buttonWidth*2, buttonHeight * 1.5);
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
        button->setStyleSheet("background-color: rgba(255, 255, 255);");
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
    backButton->setStyleSheet("background-color: rgba(255, 255, 255);");
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

    titleLabel = new DynamicFontSizeLabel();
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
    titleLabel->move((int)(this->width() * .405 ), (int)(this->height() * .1  - titleLabel->height()/2));
    titleLabel->setParent(mainMenuWidget);

    int offset = 2;
    for(auto button: buttonList){
        button->setMaximumWidth(buttonWidth);
        button->setMaximumHeight(buttonHeight);
        button->setStyleSheet("background-color: rgba(255, 255, 255);");
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
        for(auto card: physicalCardButtonList){
            card->deleteLater();
        }
        quizList.clear();
        userCards.clear();
        selectedCards.clear();
        physicalCardButtonList.clear();

        for(auto button: selectedQuizzes){
            button->deleteLater();
        }
        selectedQuizzes.clear();

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
                    cardAdder(*newCard);
                }
            }else{
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
    scrollArea->deleteLater();
    viewport->deleteLater();

    viewport = new QWidget();
    viewport->setLayout(inner);

    //Add the viewport to the scroll area
    scrollArea = new QScrollArea();
    scrollArea->setWidget(viewport);
    setScrollAreaStyleSheet(qscrollArea);

    gridLayout->addWidget(scrollArea);

    //Revisualize the cards
    cardDisplayer();

    //qDebug() << "Done loading";
    notificationLabel->setText("Welcome back, " + profileName);
    notificationLabel->setStyleSheet("color:black");
    fireAnimation();

    //Add quiz buttons to quizViewport
    for(int i = 0; i < quizList.size(); i++){
        QuizButton* button = new QuizButton(nullptr, nullptr);
        button->setText(quizList[i].first);
        button->setFont(*buttonFont);
        button->setMinimumSize(buttonWidth, buttonHeight);
        button->setMaximumSize(buttonWidth, buttonHeight);
        button->setParent(quizViewport);
        button->move(quizSelectGridWidget->width()/2 - buttonWidth/2, (((i * buttonHeight) + ((i + 1) * 20)) * heightRatio) + (heightRatio * 75));
        selectedQuizzes[quizList[i].first] = button;
    }

    return true;
}

void MainWindow::setScrollAreaStyleSheet(QScrollArea* scrollA){
    scrollA->setStyleSheet(QString::fromUtf8("background: transparent; }"
        "QScrollBar:vertical {"
        "    border: 1px solid #999999;"
        "    background:white;"
        "    width:20px;    "
        "    margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar:horizontal {"
        "    border: 1px solid #999999;"
        "    background:white;"
        "    width:20px;    "
        "    margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "    stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130));"
        "    min-height: 0px;"
        "}"
        "QScrollBar::add-line:vertical {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "    stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
        "    height: 0px;"
        "    subcontrol-position: bottom;"
        "    subcontrol-origin: margin;"
        "}"
        "QScrollBar::sub-line:vertical {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "    stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
        "    height: 0 px;"
        "    subcontrol-position: top;"
        "    subcontrol-origin: margin;"
        "}"
        ));
}

void MainWindow::showMakeQuizMenu(){
    backButton->show();
    this->setPalette(QPalette());

    QPalette palette;
    palette.setBrush(QPalette::Background, *penImageScaled);
    this->setPalette(palette);

    setScrollAreaStyleSheet(scrollArea);

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
    fadeIn->setDuration(7000);
    fadeIn->setStartValue(0);
    fadeIn->setEndValue(1);
    fadeIn->setEasingCurve(QEasingCurve::InBack);
    fadeIn->start(QPropertyAnimation::DeleteWhenStopped);

    //Fade out label
    QGraphicsOpacityEffect *fadeOutEff = new QGraphicsOpacityEffect(this);
    notificationLabel->setGraphicsEffect(fadeOutEff);
    QPropertyAnimation *fadeOut = new QPropertyAnimation(fadeOutEff,"opacity");
    //notificationLabel->lower();
    fadeOut->setDuration(7000);
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
            notificationLabel->setStyleSheet("color:black");
            fireAnimation();
            return;
        }
    }

    //otherwise need to append a new list to quizList
    quizList.push_back(QPair<QString, QVector<Card*>*>(quizTextEdit->text(), new QVector<Card*>(selectedCards)));

    //update the completer
    quizTextEdit->updateCompleter(quizList);
    notificationLabel->setText(quizTextEdit->text() + " has been created!");

    //Append a button to the quiz select menu for the new chapter
    QuizButton* button = new QuizButton(nullptr, nullptr);
    button->setText(quizList[quizList.length() - 1].first);
    button->setFont(*buttonFont);
    button->setMinimumSize(buttonWidth, buttonHeight);
    button->setMaximumSize(buttonWidth, buttonHeight);

    if(selectedQuizzes.size() > 0){
        qDebug() << "here 2";
        button->move(quizSelectGridWidget->width()/2 - buttonWidth/2, (((quizList.size() - 1) * buttonHeight + (20 * quizList.size() - 1)) * heightRatio) + (75 * heightRatio));
    }else{
        qDebug() << "here 1";
        button->move(quizSelectGridWidget->width()/2 - buttonWidth/2, 95 * heightRatio);
    }
    button->setParent(quizViewport);
    selectedQuizzes[quizList[quizList.length() - 1].first] = button;

    //setAnimation
    notificationLabel->setStyleSheet("color:black");
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
            notificationLabel->setStyleSheet("color:black");
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
    notificationLabel->setStyleSheet("color:black");
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

            //qInfo() << "Starting load loop";
            for(int i = 0; i < physicalCardButtonList.size(); i++){
                for(int j = 0; j < quiz.second->size(); j++){
                    if(physicalCardButtonList[i]->getCard() == *(quiz.second->operator[](j))){
                        //qInfo() << "Selecting card at index: " << i;
                        //qDebug() << "physicalCardButtonList[" << i << "]->getCard() = " << physicalCardButtonList[i]->getCard();
                        selectedCards.push_back(new Card(physicalCardButtonList[i]->getCard()));
                        physicalCardButtonList[i]->setClicked(true);
                        physicalCardButtonList[i]->setStyleSheet("background-color: rgb(60,120,200);");
                        break;
                    }
                }
            }
            // break because we found the quiz and there will only be one occurrance of it
            break;
        }
    }
}


//Clears quizList and quiz select
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
        //Remove the corresponding button from the quiz select layout
        selectedQuizzes[quizTextEdit->text()]->deleteLater();
        selectedQuizzes.remove(quizTextEdit->text());
        for(auto button : selectedQuizzes){
            quizInner->removeWidget(button);
        }


        //qDebug() << "SelectedQuizzes.size() = " << selectedQuizzes.size();
        int i = 0;
        for(auto button : selectedQuizzes){
            button->setParent(quizViewport);
            button->move(quizSelectGridWidget->width()/2 - buttonWidth/2, (((i * buttonHeight) + (20 * (i + 1))) * heightRatio) + (75 * heightRatio));
            i++;
        }

    }else{
        notificationLabel->setText(quizTextEdit->text() + " not found!");
    }

    notificationLabel->setStyleSheet("color:black");
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
    scrollArea->deleteLater();
    viewport->deleteLater();

    viewport = new QWidget();
    viewport->setLayout(inner);

    //Add the viewport to the scroll area
    scrollArea = new QScrollArea;
    scrollArea->setWidget(viewport);
    setScrollAreaStyleSheet(scrollArea);
    gridLayout->addWidget(scrollArea);

    //Revisualize the cards
    cardDisplayer();

    notificationLabel->setText("Selected Card have been deleted!");
    notificationLabel->setStyleSheet("color:black");
    fireAnimation();
}
