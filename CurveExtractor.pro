#-------------------------------------------------
#
# Project created by QtCreator 2013-01-19T16:22:31
#
#-------------------------------------------------

CERESINCLUDEPATH = /home/harry/local/include
CERESLIBPATH = /home/harry/local/lib
GOOGLELOGLIBPATH = /usr/lib

##################################################
QMAKE_CXXFLAGS += -fopenmp

INCLUDEPATH += $${CERESINCLUDEPATH} /usr/include/eigen3

LIBS += -L$${GOOGLELOGLIBPATH} -lglog
LIBS += -L$${CERESLIBPATH} -lceres
LIBS += -lgomp -llapack -lblas -lcholmod -lcxsparse -lcolamd -lamd -lspqr -lcamd -lsuitesparseconfig

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
    CurveFitting/LeastSquaresSolver.cpp \
    FittedCurveGraphicsItem.cpp \
    CurveFitting/QuadraticPolynomial.cpp \
    CurveFitting/LeastSquareSolverFactory.cpp \
    CurveFitting/CubicPolynomial.cpp \
    CurveFitting/CubicPolynomialResidual.cpp \
    CurveFitting/ExponentialResidual.cpp \
    CurveFitting/Exponential.cpp

HEADERS  += MainWindow.h \
    CEGraphicsView.h \
    CEGraphicsScene.h \
    PointGraphicsItem.h \
    MeasurementAreaLineItem.h \
    SelectedPointsTableModel.h \
    CurveFitting/QuadraticPolynomialResidual.h \
    CurveFitting/LeastSquaresSolver.h \
    FittedCurveGraphicsItem.h \
    CurveFitting/QuadraticPolynomial.h \
    CurveFitting/LeastSquareSolverFactory.h \
    CurveFitting/CubicPolynomial.h \
    CurveFitting/CubicPolynomialResidual.h \
    CurveFitting/ExponentialResidual.h \
    CurveFitting/Exponential.h

FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc
