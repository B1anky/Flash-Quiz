#-------------------------------------------------
#
# Project created by QtCreator 2017-10-30T10:44:40
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
    QuizEditor.cpp \
    DropDownTextEdit.cpp

HEADERS  += mainwindow.h \
    Card.h \
    MyTextEdit.h \
    QuizCard.h \
    QuizEditor.h \
    DropDownTextEdit.h

FORMS    += mainwindow.ui \
    QuizEditor.ui \
    QuizEditor_copy.ui

RESOURCES += \
    resources.qrc

CONFIG += c++11
