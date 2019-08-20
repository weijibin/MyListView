#-------------------------------------------------
#
# Project created by QtCreator 2019-07-23T16:14:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyListView
TEMPLATE = app

INCLUDEPATH += $$PWD/learningCenter

SOURCES += main.cpp\
        widget.cpp \
    learningCenter/chapterList/ChapterListWidget.cpp \
    learningCenter/courseList/CourseListWidget.cpp \
    learningCenter/date/DateWidget.cpp \
    learningCenter/date/CalendarWidget.cpp \
    learningCenter/date/DateListWidget.cpp \
    learningCenter/classList/ClassListWidget.cpp \
    learningCenter/title/MainTitle.cpp \
    learningCenter/MainWidget.cpp \
    learningCenter/ChapterWidget.cpp \
    learningCenter/InterMediaCtrl.cpp \
    learningCenter/LearningCenterWidget.cpp \
    learningCenter/title/ChapterTitle.cpp \
    learningCenter/title/HeadImg.cpp \
    learningCenter/classList/CardListWidget.cpp \
    learningCenter/classList/CardWidget.cpp \
    learningCenter/date/CalendarButton.cpp \
    learningCenter/common/common.cpp \
    learningCenter/chapterList/CefViewWidget.cpp \
    learningCenter/dataCenter/DataProvider.cpp \
    learningCenter/dataCenter/DataProviderImp.cpp \
    learningCenter/common/LoadingDlg.cpp \
    learningCenter/title/ToolButton.cpp \
    learningCenter/classList/classcard/ClassCardWidget.cpp \
    learningCenter/common/RoundMovieWidget.cpp \
    learningCenter/common/HeadItem.cpp \
    learningCenter/common/TeacherHeadWidget.cpp \
    learningCenter/chapterList/ChapterNameWidget.cpp \
    learningCenter/chapterList/ChapterItem.cpp \
    learningCenter/courseList/CourseCardWidget.cpp \
    learningCenter/date/customcalendar/CCalendarWidget.cpp \
    learningCenter/date/customcalendar/DayLabel.cpp \
    learningCenter/title/TitleBaseWidget.cpp

HEADERS  += widget.h \
    learningCenter/chapterList/ChapterListWidget.h \
    learningCenter/courseList/CourseListWidget.h \
    learningCenter/date/CalendarWidget.h \
    learningCenter/date/DateListWidget.h \
    learningCenter/date/DateWidget.h \
    learningCenter/classList/ClassListWidget.h \
    learningCenter/title/MainTitle.h \
    learningCenter/MainWidget.h \
    learningCenter/ChapterWidget.h \
    learningCenter/InterMediaCtrl.h \
    learningCenter/LearningCenterWidget.h \
    learningCenter/title/ChapterTitle.h \
    learningCenter/title/HeadImg.h \
    learningCenter/classList/CardListWidget.h \
    learningCenter/classList/CardWidget.h \
    learningCenter/date/CalendarButton.h \
    learningCenter/common/common.h \
    learningCenter/chapterList/CefViewWidget.h \
    learningCenter/dataCenter/DataProvider.h \
    learningCenter/dataCenter/DataProviderImp.h \
    learningCenter/common/LoadingDlg.h \
    learningCenter/title/ToolButton.h \
    learningCenter/classList/classcard/ClassCardWidget.h \
    learningCenter/common/RoundMovieWidget.h \
    learningCenter/common/HeadItem.h \
    learningCenter/common/TeacherHeadWidget.h \
    learningCenter/chapterList/ChapterNameWidget.h \
    learningCenter/chapterList/ChapterItem.h \
    learningCenter/courseList/CourseCardWidget.h \
    learningCenter/date/customcalendar/CCalendarWidget.h \
    learningCenter/date/customcalendar/DayLabel.h \
    learningCenter/title/TitleBaseWidget.h

FORMS    += widget.ui

RESOURCES += \
    res.qrc
