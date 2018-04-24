#include "QuizEditor.h"
#include "ui_QuizEditor.h"

QuizEditor::QuizEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuizEditor)
{
    ui->setupUi(this);

    //Create and populate your layout
    QGridLayout *inner = new QGridLayout;

    for(int i = 0; i < 50; i++){
        QPushButton *loop = new QPushButton();
        loop->setMinimumHeight(250);
        loop->setMinimumWidth(425);
        loop->setMaximumHeight(250);
        loop->setMaximumWidth(425);
        inner->addWidget(loop, i/2, i%2, Qt::AlignRight);
    }

    //Create a widget and set its layout as your new layout created above
    QWidget *viewport = new QWidget;
    viewport->setLayout(inner);

    //Add the viewport to the scroll area
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(viewport);

    ui->gridLayout->addWidget(scrollArea);
}

QuizEditor::~QuizEditor()
{
    delete ui;
}
