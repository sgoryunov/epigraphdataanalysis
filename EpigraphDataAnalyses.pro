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


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-QEpigDataFourierAnalysisLib-Desktop-Debug/release/ -lQEpigDataFourierAnalysisLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-QEpigDataFourierAnalysisLib-Desktop-Debug/debug/ -lQEpigDataFourierAnalysisLib
else:unix: LIBS += -L$$PWD/../build-QEpigDataFourierAnalysisLib-Desktop-Debug/ -lQEpigDataFourierAnalysisLib

INCLUDEPATH += $$PWD/../QEpigDataFourierAnalysisLib
DEPENDPATH += $$PWD/../QEpigDataFourierAnalysisLib
