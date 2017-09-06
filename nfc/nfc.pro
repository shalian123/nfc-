#-------------------------------------------------
#
# Project created by QtCreator 2011-12-28T09:23:16
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT       += core gui widgets
QT       += sql
QT += widgets
TARGET = manager
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    clickedlabel.cpp \
    dialog_set.cpp \
    dialog_mea.cpp \
    paintline.cpp

HEADERS  += widget.h \
    clickedlabel.h \
    dialog_set.h \
    connection.h \
    dialog_mea.h \
    paintline.h

FORMS    += widget.ui \
    dialog_set.ui \
    dialog_mea.ui

RC_FILE = \
  my.rc

RESOURCES += \
    images.qrc

