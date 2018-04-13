#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T13:16:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EpigraphDataAnalyses
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qepigraphdataprocessor.cpp

HEADERS  += mainwindow.h \
    qepigraphdataprocessor.h



FORMS    += mainwindow.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-QEpigDataFourierAnalysisLib-Desktop_Qt_5_5_1_MinGW_32bit-Debug/release/ -lQEpigDataFourierAnalysisLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-QEpigDataFourierAnalysisLib-Desktop_Qt_5_5_1_MinGW_32bit-Debug/debug/ -lQEpigDataFourierAnalysisLib
else:unix: LIBS += -L$$PWD/../build-QEpigDataFourierAnalysisLib-Desktop_Qt_5_5_1_MinGW_32bit-Debug/ -lQEpigDataFourierAnalysisLib

INCLUDEPATH += $$PWD/../QEpigDataFourierAnalysisLib
DEPENDPATH += $$PWD/../QEpigDataFourierAnalysisLib
