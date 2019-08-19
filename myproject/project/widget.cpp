#include "widget.h"
#include "ui_widget.h"
#include "chapterlist/ChapterListWidget.h"
#include "classlist/ClassListWidget.h"
#include "classList/classcard/ClassCardWidget.h"
#include "date/DateListWidget.h"
#include "courselist/CourseListWidget.h"

#include "title/TitleWidget.h"

#include "LearningCenterWidget.h"
#include "InterMediaCtrl.h"
#include "dataCenter/DataProvider.h"
#include "common/common.h"
#include "ChapterWidget.h"
#include "courseList/CourseCardWidget.h"

#include "date/customcalendar/CCalendarWidget.h"

#include <QFile>
#include <QDebug>
#include <QDate>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_dateBtn_clicked()
{

    CCalendarWidget * w = new CCalendarWidget;

    QFile f(":/qss/style.qss");
    if (f.open(QFile::ReadOnly)) {
        QByteArray a_qss(std::move(f.readAll()));
        f.close();
        w->setStyleSheet(a_qss);
    }

    w->setSelectedDate(QDate::currentDate());

    QList<QDate> lst;
    lst.append(QDate::currentDate().addDays(10));
    w->setCourseDate(lst);

    w->show();
}

void Widget::on_classBtn_clicked()
{
//    DataProvider::GetInstance().setParentWidget(this);
//    QDate dataStart;
//    QDate dataend;
//    QList<ClassCardInfo> cards;
//    int ret = DataProvider::GetInstance().requestClassCard(dataStart,dataend,cards);

//    qDebug()<<"Widget::on_classBtn_clicked()"<<ret;

    ClassCardWidget *w = new ClassCardWidget(0);
    w->setFixedSize(772,512);

    QFile f(":/qss/style.qss");
    if (f.open(QFile::ReadOnly)) {
        QByteArray a_qss(std::move(f.readAll()));
        f.close();
        w->setStyleSheet(a_qss);
    }

    ClassTime time;
    time.day = QString::fromLocal8Bit("今日");
    time.startTime = "8:30";
    time.endTime = "18:30";
    time.index = 2;

    ClassCardInfo info;
    info.time = time;
    info.classStatusType = 1;
    info.classStatus = QString::fromLocal8Bit("直播进行中...");
    info.classTip = QString::fromLocal8Bit("记得去APP完成课清哦~");
    info.btnText = QString::fromLocal8Bit("去上课");
    info.chapterName = QString::fromLocal8Bit("第一讲 函数奇偶性与对称性");
    info.subjectName = QString::fromLocal8Bit("数学");
    info.courseName = QString::fromLocal8Bit("【2019-暑】六年级初一数学直播菁英班（北京人教）");

    w->setClassInfo(info);
    w->show();
}

void Widget::on_courseBtn_clicked()
{
//    for(int i = 0 ; i<2; i++)
//    {
//        DataProvider::GetInstance().setParentWidget(this);
//        FilterType filter;
//        QList<CourseCardInfo> cards;
//        int ret = DataProvider::GetInstance().requestCourseCard(filter,cards);

//        qDebug()<<"Widget::on_courseBtn_clicked()"<<ret;
//    }

    CourseCardWidget *w = new CourseCardWidget(this);

    QFile f(":/qss/style.qss");
    if (f.open(QFile::ReadOnly)) {
        QByteArray a_qss(std::move(f.readAll()));
        f.close();
        w->setStyleSheet(a_qss);
    }

    CourseCardInfo info;
    info.subjectName = QString::fromLocal8Bit("数学");
    info.courseName = QString::fromLocal8Bit("【2019-暑】六年级初一数学直播菁英班（北京人教）");

    TeacherInfo info_t1;
    info_t1.name = QString::fromLocal8Bit("郭德纲");
    info_t1.type = 1;
    info_t1.imgUrl = ":/res/default_boy_img.png";

    TeacherInfo info_t2;
    info_t2.name = QString::fromLocal8Bit("于谦");
    info_t2.type = 4;
    info_t2.imgUrl = ":/res/default_boy_img.png";

    info.teachers.clear();
    info.teachers.append(info_t1);
    info.teachers.append(info_t2);

    info.isRefund = true;
    w->setCourseInfo(info);
    w->show();

    w->move(100,100);
}

void Widget::on_chapterBtn_clicked()
{
////    m_center = new LearningCenterWidget(this);
//    CourseToChapterPar par;
//    par.deadLine = "2022";
//    par.stuCouID = 123456;
//    par.courseName = "小学语数英课程";
//    par.courseType = 0;

////    m_center = new LearningCenterWidget;
////    m_center->changeToChapterMode(par);
////    qDebug() << "enter---->chapterListWidget";

//    ChapterWidget * m_charpter = new ChapterWidget();
//    m_charpter->setCourseInfo(par);
//    m_charpter->changeToChapter();
//    m_charpter->show();
}

void Widget::on_pushButton_clicked()
{
//    if(m_center == nullptr)
    {
        m_center = new LearningCenterWidget;
        m_center->resize(900,600);
        InterMediaCtrl::GetInstance().setCenterWidget(m_center);
        InterMediaCtrl::GetInstance().initState();

        QFile f(":/qss/style.qss");
        if (f.open(QFile::ReadOnly)) {
            QByteArray a_qss(std::move(f.readAll()));
            f.close();
            m_center->setStyleSheet(a_qss);
        }
    }
    m_center->showNormal();

}
