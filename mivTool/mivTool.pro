#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T12:26:13
#
#-------------------------------------------------

QT     += core gui xml multimedia
CONFIG += app_bundle
CONFIG +=  c++11
TARGET = mivTool
TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#unix:macx{
#INCLUDEPATH += /usr/local/include/ \
#              ../../codespace/mivClass/ \
#              ../../codespace/extLib/
#LIBS += "/usr/local/lib/*.dylib"
#include(../exLib/bgslib.pri)
#DEFINES += RESULTDIR=\\\"/Users/iDev/Documents/xResults\\\"
#DEFINES += CONFIGDIR=\\\"/Users/iDev/codespace/mivClass\\\"
#DEFINES += INPUTDIR=\\\"/Users/iDev/Documents/dataset2014/dataset/dynamicBackground/\\\"
#}

win32{
INCLUDEPATH += C:/opencv/build3conrib/install/include \
               E:/QTWS/pix2qim/exLib/ \
               E:/QTWS/pix2qim/mivClass/ \
               E:/QTWS/pix2qim/GroundPlane/ \

LIBS += C:/opencv/build3conrib/bin/*.dll \

include(E:/QTWS/pix2qim/exLib/bgslib.pri)
DEFINES += RESULTDIR=\\\"E:/QTWS/pix2qim/result\\\"
DEFINES += CONFIGDIR=\\\"E:/QTWS/pix2qim/config\\\"
DEFINES += INPUTDIR=\\\"E:/QTWS/dataset/\\\"
}

SOURCES += main.cpp\
        mainwindow.cpp \
    E:/QTWS/pix2qim/mivClass/dynamicwidget.cpp \
    E:/QTWS/pix2qim/mivClass/vidprocessor.cpp \
    task_runalgo.cpp \
    task_extractframe.cpp \
    task_evaluate.cpp \
    calibrater.cpp \
    dialogrange.cpp \
    groundplane.cpp \
    qlabelclick.cpp \
    settings.cpp \
    tools.cpp \

HEADERS  += mainwindow.h \
    E:/QTWS/pix2qim/mivClass/dynamicwidget.h \
    E:/QTWS/pix2qim/mivClass/vidprocessor.h \
    task_runalgo.h \
    task_extractframe.h \
    task_evaluate.h \
    calibrater.h \
    dialogrange.h \
    groundplane.h \
    qlabelclick.h \
    settings.h \
    tools.h \


FORMS    += mainwindow.ui \
    task_runalgo.ui \
    task_extractframe.ui \
    task_evaluate.ui \
    E:/QTWS/pix2qim/GroundPlane/dialogrange.ui \

