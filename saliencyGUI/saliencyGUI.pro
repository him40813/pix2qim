#-------------------------------------------------
#
# Project created by QtCreator 2015-12-09T10:52:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = saliencyGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp

HEADERS  += mainwindow.h \
    player.h

FORMS    += mainwindow.ui
unix:macx{
INCLUDEPATH += /usr/local/include/
LIBS += "/usr/local/lib/*.dylib"
}
win32{
INCLUDEPATH += C:/opencv/build/install/include
LIBS += "C:/opencv/build/install/x86/mingw/bin/*.dll"
}
