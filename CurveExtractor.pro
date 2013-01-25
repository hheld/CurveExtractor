#-------------------------------------------------
#
# Project created by QtCreator 2013-01-19T16:22:31
#
#-------------------------------------------------

CERESINCLUDEPATH = /home/harry/local/include
CERESLIBPATH = /home/harry/local/lib
GOOGLELOGLIBPATH = /home/harry/local/lib

##################################################

INCLUDEPATH += $${CERESINCLUDEPATH} /usr/include/eigen3
LIBS += -L$${CERESLIBPATH} -lceres_shared -L$${GOOGLELOGLIBPATH} -lglog

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
    SelectedPointsTableModel.cpp \
    CurveFitting/QuadraticPolynomialResidual.cpp \
    CurveFitting/LeastSquaresSolver.cpp

HEADERS  += MainWindow.h \
    CEGraphicsView.h \
    CEGraphicsScene.h \
    PointGraphicsItem.h \
    MeasurementAreaLineItem.h \
    SelectedPointsTableModel.h \
    CurveFitting/QuadraticPolynomialResidual.h \
    CurveFitting/LeastSquaresSolver.h

FORMS    += MainWindow.ui
