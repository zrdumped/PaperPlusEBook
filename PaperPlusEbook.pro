#-------------------------------------------------
#
# Project created by QtCreator 2018-05-04T18:43:03
#
#-------------------------------------------------
#DEFINES += CWTWINDOWS
DEFINES += ZRWINDOWS
#DEFINES += TZYMACOSX

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
        touchtracker.cpp \
        mycv.cpp \
    writedetection.cpp



HEADERS += \
        mainwindow.h    \
        txtparser.h \
        bookmetadata.h \
        bookpagedata.h \
        book.h \
        note.h \
        imageconfig.h \
        qrcode.h \
        touchtracker.h \
        mycv.h \
    writedetection.h

FORMS += \
        mainwindow.ui \
        imageconfig.ui
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
             /usr/local/include/opencv2

LIBS +=         \
            -L/usr/local/lib -lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_imgcodecs \
            -L /usr/local/Cellar/little-cms2/2.9/lib -llcms2.2  \
            -L/usr/local/lib -lpoppler -lpoppler-cpp -lpoppler-glib  \
            -L/System/Library/Frameworks/ImageIO.framework/Versions/A/Resources -lJPEG \



}

}
}

RESOURCES += \
    icons.qrc \
    confighelper.qrc






