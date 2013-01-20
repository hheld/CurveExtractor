#-------------------------------------------------
#
# Project created by QtCreator 2013-01-19T16:22:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CurveExtractor
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    CEGraphicsView.cpp \
    CEGraphicsScene.cpp \
    PointGraphicsItem.cpp \
    MeasurementAreaLineItem.cpp \
    SelectedPointsTableModel.cpp

HEADERS  += MainWindow.h \
    CEGraphicsView.h \
    CEGraphicsScene.h \
    PointGraphicsItem.h \
    MeasurementAreaLineItem.h \
    SelectedPointsTableModel.h

FORMS    += MainWindow.ui
