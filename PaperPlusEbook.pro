#-------------------------------------------------
#
# Project created by QtCreator 2018-05-04T18:43:03
#
#-------------------------------------------------
#DEFINES += CWTWINDOWS
#DEFINES += ZRWINDOWS
DEFINES += TZYMACOSX

DEFINES += DLL_EXPORT

include(qzxing/QZXing.pri)

QT       += core gui xml
QT       += core gui multimedia
QT       += quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaperPlusEBook
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
    txtparser.cpp \
    bookmetadata.cpp \
    bookpagedata.cpp \
    book.cpp \
    note.cpp \
    imageconfig.cpp \
    myifstream.cpp \
    notemanager.cpp \
    notemetadata.cpp \
    menu.cpp \
    singlepage.cpp \
    choosebookpage.cpp \
    choosenotepage.cpp \
    arrowwidget.cpp \
    emptynote.cpp \
    emptybook.cpp \
        touchtracker.cpp \
        mycv.cpp \
    writedetection.cpp \
    bookmanager.cpp \
    bookentrymodal.cpp \
    noteentrymodal.cpp \
    noteentryedit.cpp \
    bookentryuppermodal.cpp \
    noteentryuppermodal.cpp \
    noteentryeditupper.cpp

HEADERS += \
        mainwindow.h    \
    txtparser.h \
    bookmetadata.h \
    bookpagedata.h \
    book.h \
    note.h \
    imageconfig.h   \
    myifstream.h \
    notemanager.h \
    notemetadata.h \
    menu.h \
    singlepage.h \
    choosebookpage.h \
    choosenotepage.h \
    arrowwidget.h \
    emptynote.h \
    emptybook.h \
    qrcode.h \
        touchtracker.h \
        mycv.h \
    writedetection.h \
    bookmanager.h \
    bookentrymodal.h \
    noteentrymodal.h \
    noteentryedit.h \
    bookentryuppermodal.h \
    noteentryuppermodal.h \
    noteentryeditupper.h

FORMS += \
        mainwindow.ui \
    imageconfig.ui \
    menu.ui \
    singlepage.ui \
    choosebookpage.ui \
    choosenotepage.ui \
    emptynote.ui \
    emptybook.ui \
    bookentrymodal.ui \
    noteentrymodal.ui \
    noteentryedit.ui \
    bookentryuppermodal.ui \
    noteentryuppermodal.ui \
    noteentryeditupper.ui

if(contains(DEFINES, CWTWINDOWS)){
INCLUDEPATH += \
        E:\develop\opencv_build\include

LIBS += \
        #-LE:/develop/opencv/build/x64/vc15/lib/ \
        #-lopencv_world341 \
        #-lopencv_world341d \
        -LE:\develop\opencv_build\lib\
        -lopencv_highgui341 \
        -lopencv_core341 \
        -lopencv_videoio341 \
        -lopencv_imgproc341  \
        -lopencv_imgcodecs341 \
        -lopencv_tracking341 \
}
else{
if(contains(DEFINES, ZRWINDOWS)){
INCLUDEPATH += \
        C:\OpenCV\opencv\build\include \
        C:\OpenCV\opencv\build\include\opencv  \
        C:\OpenCV\opencv\build\include\opencv2

LIBS += C:\OpenCV\opencv\build\x64\vc14\lib\opencv_world330.lib \
        C:\OpenCV\opencv\build\x64\vc14\lib\opencv_world330d.lib

#INCLUDEPATH += $$PWD/poppler
#LIBS += -L$$PWD/poppler -llibpoppler
#LIBS += -L$$PWD/poppler -llibpoppler-qt5

}
else{
if(contains(DEFINES, TZYMACOSX)){


INCLUDEPATH += \
            /usr/local/include \
            /usr/local/include/opencv \
             /usr/local/include/opencv2

LIBS +=         \
            -L/usr/local/lib -lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lopencv_tracking\
            -L/System/Library/Frameworks/ImageIO.framework/Versions/A/Resources -lJPEG \

}

}
}

RESOURCES += \
    icons.qrc \
    confighelper.qrc






