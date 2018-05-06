#-------------------------------------------------
#
# Project created by QtCreator 2017-10-30T10:44:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quiz
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    Card.cpp \
    MyTextEdit.cpp \
    QuizCard.cpp \
    DropDownTextEdit.cpp \
    HoverButton.cpp \
    MyInputDialog.cpp \
    DragBarLabel.cpp \
    QuizButton.cpp \
    ExitButton.cpp \
    MinimizeButton.cpp

HEADERS  += mainwindow.h \
    Card.h \
    MyTextEdit.h \
    QuizCard.h \
    DropDownTextEdit.h \
    HoverButton.h \
    MyInputDialog.h \
    DragBarLabel.h \
    QuizButton.h \
    ExitButton.h \
    MinimizeButton.h

FORMS    += mainwindow.ui \
    QuizEditor.ui \
    QuizEditor_copy.ui

RESOURCES += \
    resources.qrc

CONFIG += c++11
