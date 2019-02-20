#-------------------------------------------------
#
# Project created by QtCreator 2018-08-10T16:04:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FFMPEGTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    h265viedoplayer.cpp

HEADERS += \
        mainwindow.h \
    h265viedoplayer.h

FORMS += \
        mainwindow.ui


#win32: LIBS += -L$$PWD/../../../FFMPEG/ffmpeg-20180809-e0539f0-win64-dev/ffmpeg-20180809-e0539f0-win64-dev/lib/ -llibavcodec.dll
#win32: LIBS += -L$$PWD/../../../FFMPEG/ffmpeg-20180809-e0539f0-win64-dev/ffmpeg-20180809-e0539f0-win64-dev/lib/ -llibavdevice.dll.dll
#win32: LIBS += -L$$PWD/../../../FFMPEG/ffmpeg-20180809-e0539f0-win64-dev/ffmpeg-20180809-e0539f0-win64-dev/lib/ -llibavfilter.dll
#win32: LIBS += -L$$PWD/../../../FFMPEG/ffmpeg-20180809-e0539f0-win64-dev/ffmpeg-20180809-e0539f0-win64-dev/lib/ -llibavfilter.dll
#win32: LIBS += -L$$PWD/../../../FFMPEG/ffmpeg-20180809-e0539f0-win64-dev/ffmpeg-20180809-e0539f0-win64-dev/lib/ -llibavformat.dll
#win32: LIBS += -L$$PWD/../../../FFMPEG/ffmpeg-20180809-e0539f0-win64-dev/ffmpeg-20180809-e0539f0-win64-dev/lib/ -llibavutil.dll
#win32: LIBS += -L$$PWD/../../../FFMPEG/ffmpeg-20180809-e0539f0-win64-dev/ffmpeg-20180809-e0539f0-win64-dev/lib/ -llibpostproc.dll
#win32: LIBS += -L$$PWD/../../../FFMPEG/ffmpeg-20180809-e0539f0-win64-dev/ffmpeg-20180809-e0539f0-win64-dev/lib/ -llibswresample.dll
#win32: LIBS += -L$$PWD/../../../FFMPEG/ffmpeg-20180809-e0539f0-win64-dev/ffmpeg-20180809-e0539f0-win64-dev/lib/ -llibswscale.dll

#INCLUDEPATH += $$PWD/../../../FFMPEG/ffmpeg-20180809-e0539f0-win64-dev/ffmpeg-20180809-e0539f0-win64-dev/include


#DEPENDPATH += $$PWD/../../../FFMPEG/ffmpeg-20180809-e0539f0-win64-dev/ffmpeg-20180809-e0539f0-win64-dev/lib




win32: LIBS += -L$$PWD/../../FFMPEG/ffmpeg-4.0.2-win64-dev/ffmpeg-4.0.2-win64-dev/lib/ -lavcodec
win32: LIBS += -L$$PWD/../../FFMPEG/ffmpeg-4.0.2-win64-dev/ffmpeg-4.0.2-win64-dev/lib/ -lavdevice
win32: LIBS += -L$$PWD/../../FFMPEG/ffmpeg-4.0.2-win64-dev/ffmpeg-4.0.2-win64-dev/lib/ -lavfilter
win32: LIBS += -L$$PWD/../../FFMPEG/ffmpeg-4.0.2-win64-dev/ffmpeg-4.0.2-win64-dev/lib/ -lavformat
win32: LIBS += -L$$PWD/../../FFMPEG/ffmpeg-4.0.2-win64-dev/ffmpeg-4.0.2-win64-dev/lib/ -lavutil
win32: LIBS += -L$$PWD/../../FFMPEG/ffmpeg-4.0.2-win64-dev/ffmpeg-4.0.2-win64-dev/lib/ -lpostproc
win32: LIBS += -L$$PWD/../../FFMPEG/ffmpeg-4.0.2-win64-dev/ffmpeg-4.0.2-win64-dev/lib/ -lswresample
win32: LIBS += -L$$PWD/../../FFMPEG/ffmpeg-4.0.2-win64-dev/ffmpeg-4.0.2-win64-dev/lib/ -lswscale

INCLUDEPATH += $$PWD/../../FFMPEG/ffmpeg-4.0.2-win64-dev/ffmpeg-4.0.2-win64-dev/include
DEPENDPATH += $$PWD/../../FFMPEG/ffmpeg-4.0.2-win64-shared/ffmpeg-4.0.2-win64-shared/bin



win32: LIBS += -L$$PWD/../../FFMPEG/SDL2/lib/x64/ -lSDL2

INCLUDEPATH += $$PWD/../../FFMPEG/SDL2/include
DEPENDPATH += $$PWD/../../FFMPEG/SDL2/lib/x64
