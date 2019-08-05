#-------------------------------------------------
#
# Project created by QtCreator 2019-07-23T16:14:51
#
#-------------------------------------------------

QT       += core gui
QT       += winextras

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
    learningCenter/classList/ClassListWidget.cpp \
    learningCenter/title/TitleWidget.cpp \
    learningCenter/title/MainTitle.cpp \
    learningCenter/MainWidget.cpp \
    learningCenter/ChapterWidget.cpp \
    learningCenter/InterMediaCtrl.cpp \
    learningCenter/LearningCenterWidget.cpp \
    learningCenter/title/ChapterTitle.cpp \
    learningCenter/title/HeadImg.cpp \
    learningCenter/classList/CardListWidget.cpp \
    learningCenter/classList/CardWidget.cpp \
    learningCenter/date/CCalendarWidget.cpp

HEADERS  += widget.h \
    learningCenter/chapterList/ChapterListWidget.h \
    learningCenter/courseList/CourseListWidget.h \
    learningCenter/date/CalendarWidget.h \
    learningCenter/date/DateListWidget.h \
    learningCenter/date/DateWidget.h \
    learningCenter/classList/ClassListWidget.h \
    learningCenter/title/TitleWidget.h \
    learningCenter/title/MainTitle.h \
    learningCenter/MainWidget.h \
    learningCenter/ChapterWidget.h \
    learningCenter/InterMediaCtrl.h \
    learningCenter/LearningCenterWidget.h \
    learningCenter/title/ChapterTitle.h \
    learningCenter/title/HeadImg.h \
    learningCenter/classList/CardListWidget.h \
    learningCenter/classList/CardWidget.h \
    learningCenter/date/CCalendarWidget.h

FORMS    += widget.ui

RESOURCES += \
    res.qrc
