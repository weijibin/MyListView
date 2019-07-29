#-------------------------------------------------
#
# Project created by QtCreator 2019-07-23T16:14:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyListView
TEMPLATE = app

INCLUDEPATH += $$PWD\learningCenter

SOURCES += main.cpp\
        widget.cpp \
    learningCenter/chapterList/ChapterListWidget.cpp \
    learningCenter/courseList/CourseListWidget.cpp \
    learningCenter/date/DateWidget.cpp \
    learningCenter/date/CalendarWidget.cpp \
    learningCenter/date/DateListWidget.cpp \
    learningCenter/classList/ClassListWidget.cpp

HEADERS  += widget.h \
    learningCenter/chapterList/ChapterListWidget.h \
    learningCenter/courseList/CourseListWidget.h \
    learningCenter/date/CalendarWidget.h \
    learningCenter/date/DateListWidget.h \
    learningCenter/date/DateWidget.h \
    learningCenter/classList/ClassListWidget.h

FORMS    += widget.ui

RESOURCES += \
    res.qrc
