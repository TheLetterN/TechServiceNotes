#-------------------------------------------------
#
# Project created by QtCreator 2013-07-29T13:30:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TechServiceNotes
TEMPLATE = app


SOURCES += main.cpp\
        technotes.cpp \
    notedata.cpp \
    popouttext.cpp \
    licensedialog.cpp \
    configdata.cpp

HEADERS  += technotes.h \
    notedata.h \
    popouttext.h \
    licensedialog.h \
    configdata.h

FORMS    += technotes.ui \
    popouttext.ui \
    licensedialog.ui

OTHER_FILES += \
    license.txt

RESOURCES += \
    textfiles.qrc
