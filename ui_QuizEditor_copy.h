/********************************************************************************
** Form generated from reading UI file 'QuizEditor_copy.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIZEDITOR_COPY_H
#define UI_QUIZEDITOR_COPY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuizEditor
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
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

    void setupUi(QMainWindow *QuizEditor)
    {
        if (QuizEditor->objectName().isEmpty())
            QuizEditor->setObjectName(QStringLiteral("QuizEditor"));
        QuizEditor->resize(1920, 1080);
        centralWidget = new QWidget(QuizEditor);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
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

        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(970, 10, 941, 1011));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        QuizEditor->setCentralWidget(centralWidget);
        menubar = new QMenuBar(QuizEditor);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1920, 21));
        QuizEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(QuizEditor);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        QuizEditor->setStatusBar(statusbar);

        retranslateUi(QuizEditor);

        QMetaObject::connectSlotsByName(QuizEditor);
    } // setupUi

    void retranslateUi(QMainWindow *QuizEditor)
    {
        QuizEditor->setWindowTitle(QApplication::translate("QuizEditor", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("QuizEditor", "Create/Update Quiz", nullptr));
        pushButton_4->setText(QApplication::translate("QuizEditor", "Load/Select Quiz", nullptr));
        pushButton_2->setText(QApplication::translate("QuizEditor", "Lock Quiz", nullptr));
        pushButton_3->setText(QApplication::translate("QuizEditor", "Delete Quiz", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuizEditor: public Ui_QuizEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZEDITOR_COPY_H
