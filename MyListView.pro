#-------------------------------------------------
#
# Project created by QtCreator 2019-07-23T16:14:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyListView
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    classlistwidget.cpp \
    courselistwidget.cpp \
    chapterlistwidget.cpp \
    datelistwidget.cpp \
    dateList/datelistmodel.cpp \
    dateList/datedelegate.cpp \
    dateList/datelistview.cpp \
    dateList/datewidget.cpp

HEADERS  += widget.h \
    classlistwidget.h \
    courselistwidget.h \
    chapterlistwidget.h \
    datelistwidget.h \
    dateList/datelistmodel.h \
    dateList/datedelegate.h \
    dateList/datelistview.h \
    dateList/datewidget.h

FORMS    += widget.ui \
    dateList/datewidget.ui
