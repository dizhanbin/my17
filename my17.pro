#-------------------------------------------------
#
# Project created by QtCreator 2015-07-15T09:54:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += widgets

TARGET = my17
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    my17.cpp \
    messagecenter.cpp \
    view.cpp \
    nlog.cpp \
    viewdoc.cpp \
    docbusinesseditor.cpp \
    docmodeleditor.cpp \
    mbusinessdelegate.cpp \
    mmodelfielddelegate.cpp \
    mmodeldelegate.cpp \
    doceventeditor.cpp \
    meventdelegate.cpp \
    lineview.cpp \
    iconview.cpp \
    viewgroup.cpp \
    murldelegate.cpp \
    docurleditor.cpp \
    mpropertydelegate.cpp \
    mproperty.cpp \
    doccommoneditor.cpp \
    mbooleandelegate.cpp \
    formview.cpp \
    docformeditor.cpp \
    viewforms.cpp \
    formlineview.cpp \
    tablemodel.cpp \
    projectadapter.cpp \
    commoneditdelegate.cpp

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
    meventdelegate.h \
    lineview.h \
    iconview.h \
    viewgroup.h \
    murldelegate.h \
    docurleditor.h \
    mpropertydelegate.h \
    mproperty.h \
    doccommoneditor.h \
    mbooleandelegate.h \
    formview.h \
    docformeditor.h \
    viewforms.h \
    viewforms.h \
    formlineview.h \
    tablemodel.h \
    projectadapter.h \
    editoradapter.h \
    commoneditdelegate.h

FORMS    += mainwindow.ui \
    docbusinesseditor.ui \
    docmodeleditor.ui \
    doceventeditor.ui \
    docurleditor.ui \
    doccommoneditor.ui \
    docformeditor.ui

OTHER_FILES +=

RESOURCES += \
    image.qrc
