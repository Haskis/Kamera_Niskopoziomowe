#-------------------------------------------------
#
# Project created by QtCreator 2014-07-18T20:35:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kamera_Niskopoziomowe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cameradriver.cpp \
    imageprocessing.cpp \
    ledindicator.cpp \
    trainingset.cpp \
    stylesheets.cpp

HEADERS  += mainwindow.h \
    cameradriver.h \
    imageprocessing.h \
    ledindicator.h \
    trainingset.h \
    stylesheets.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib

LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
LIBS += -lopencv_nonfree

RESOURCES +=  Resources.qrc
