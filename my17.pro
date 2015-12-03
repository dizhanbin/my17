#-------------------------------------------------
#
# Project created by QtCreator 2015-07-15T09:54:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my17
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    my17.cpp \
    messagecenter.cpp \
    nlog.cpp \
    viewdoc.cpp \
    view.cpp \
    docbusinesseditor.cpp \
    docmodeleditor.cpp \
    mbusinessdelegate.cpp \
    mmodelfielddelegate.cpp \
    mmodeldelegate.cpp \
    doceventeditor.cpp \
    meventdelegate.cpp


HEADERS  += mainwindow.h \
    my17.h \
    messagecenter.h \
    nlog.h \
    view.h \
    viewdoc.h \
    docbusinesseditor.h \
    docmodeleditor.h \
    mbusinessdelegate.h \
    mmodelfielddelegate.h \
    mmodeldelegate.h \
    doceventeditor.h \
    meventdelegate.h


FORMS    += mainwindow.ui \
    docbusinesseditor.ui \
    docmodeleditor.ui \
    doceventeditor.ui

OTHER_FILES +=

RESOURCES += \
    image.qrc
