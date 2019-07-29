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
    chapterList/ChapterListWidget.cpp \
    date/CalendarWidget.cpp \
    date/DateWidget.cpp \
    date/DateListWidget.cpp \
    classList/ClassListWidget.cpp \
    courseList/CourseListWidget.cpp

HEADERS  += widget.h \
    chapterList/ChapterListWidget.h \
    date/CalendarWidget.h \
    date/DateListWidget.h \
    date/DateWidget.h \
    classList/ClassListWidget.h \
    courseList/CourseListWidget.h

FORMS    += widget.ui

RESOURCES += \
    res.qrc
