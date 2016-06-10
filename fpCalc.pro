#-------------------------------------------------
#
# Project created by QtCreator 2016-06-08T10:41:53
#
#-------------------------------------------------

QT       += core gui

#QT += testlib
#CONFIG += testcase

CONFIG += static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fpCalc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        calculator.cpp \
        #testof_calculator.cpp
        medianinputdialog.cpp

HEADERS  += mainwindow.h \
        calculator.h \
        medianinputdialog.h
        #testof_calculator.h

FORMS    += mainwindow.ui \
        medianinputdialog.ui
