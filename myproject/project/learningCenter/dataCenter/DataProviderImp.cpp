#include "DataProviderImp.h"
#include <QTime>
#include <QDebug>

ClassCardInfo getCardInfo(int type)
{
    ClassTime time;
    time.day = QString::fromLocal8Bit("test");
    time.startTime = "8:30";
    time.endTime = "18:30";
    time.index = 2;
    time.date = QDate::currentDate();

    ClassCardInfo info;
    info.time = time;

    info.classStatusType = type%3;

    info.classStatus = QString::fromLocal8Bit("直播进行中...");
    info.classTip = QString::fromLocal8Bit("记得去APP完成课清哦~");
    if(info.classStatusType == 1)
        info.btnText = QString::fromLocal8Bit("去上课");
    else
        info.btnText = QString::fromLocal8Bit("看回放");

    info.chapterName = QString::fromLocal8Bit("第一讲 函数奇偶性与对称性");
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


    return info;

}

DataProviderImp::DataProviderImp(QObject *parent) : QObject(parent)
{

}

void DataProviderImp::sltRequestClassCard(const QDate &start,int direction)
{
    m_classErrorCode = 0;

    QTime t;
    t.start();
    m_classInfo.clear();
    while(t.elapsed() < 3000)
    {

    }

    m_classPar.curIndex = 3;

    for(int i = 0 ; i< 8; i++)
    {
        ClassCardInfo info = getCardInfo(i+1);
        info.type = 1;
        m_classInfo.append(info);
    }

    m_classErrorCode = 1;

    emit sigFinish();
}

void DataProviderImp::sltRequestClassNumInPeriod(const QDate &start, const QDate &end)
{
    m_classDateErroCode = 0;
    QTime t;
    t.start();
    m_classDateInfo.clear();
    while(t.elapsed() < 3000)
    {

    }
    m_classDateErroCode = 1;

    for(int i =0; i<7; i++)
    {
        QDate date = start;
        DateInfo Info;
        Info.date = date.addDays(i);
        Info.num = 9;
        m_classDateInfo.append(Info);
    }

    emit sigFinish();
}

void DataProviderImp::sltRequestCourseConfig()
{
    m_courseConfigErrorCode = 0;
    QTime t;
    t.start();
    while(t.elapsed() < 1000)
    {

    }
    m_courseConfigErrorCode = 1;

    //=========================================
    m_courseConfig.courseStatus.insert(0,QString::fromLocal8Bit("全部"));
    m_courseConfig.courseStatus.insert(1,QString::fromLocal8Bit("未开课"));
    m_courseConfig.courseStatus.insert(2,QString::fromLocal8Bit("正在学"));
    m_courseConfig.courseStatus.insert(3,QString::fromLocal8Bit("已结课"));

    m_courseConfig.subjects.insert(0,QString::fromLocal8Bit("全部"));
    m_courseConfig.subjects.insert(2,QString::fromLocal8Bit("数学"));
    m_courseConfig.subjects.insert(5,QString::fromLocal8Bit("化学"));
    m_courseConfig.subjects.insert(3,QString::fromLocal8Bit("英语"));
    m_courseConfig.subjects.insert(10000,QString::fromLocal8Bit("素养课"));
    //=========================================

    emit sigFinish();
}

void DataProviderImp::sltRequestCourseCard(const FilterType & filter)
{
    m_courseErrorCode = 0;
    QTime t;
    t.start();
    m_courseInfo.clear();
    while(t.elapsed() < 3000)
    {

    }

    m_courseErrorCode = 1;
    m_courseNextZone = 1;

    //===================================
    //test data
    CourseCardInfo info;
    info.subjectName = QString::fromLocal8Bit("语文");
    info.courseName = QString::fromLocal8Bit("【2019-暑】六年级初一数学直播菁英班（北京人教）");

    TeacherInfo info_t1;
    info_t1.name = QString::fromLocal8Bit("test");
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

    for(int i = 0; i<10; i++)
    {
        m_courseInfo.append(info);
    }
    //===================================

    emit sigFinish();
}

void DataProviderImp::sltRequestCourseDates(const QDate & cur)
{
    m_courseDateErrorCode = 0;
    QTime t;
    t.start();
    m_courseDates.clear();
    while(t.elapsed() < 3000)
    {

    }
    m_courseDateErrorCode = 1;

    //==========
    m_courseDates.append(cur);
    m_courseDates.append(cur.addDays(2));
    m_courseDates.append(cur.addDays(5));
    //===========

    emit sigFinish();
}

void DataProviderImp::sltRequestChapterList(const CourseToChapterPar & par)
{
    m_chapterListErrorCode = 0;
    QTime t;
    t.start();
    m_chapterList.clear();
    while(t.elapsed() < 3000)
    {

    }
    m_chapterListErrorCode = 1;
    // 测试数据
    for (int  i = 0; i < 20; i++) {
        ChapterInfo info;
        info.time.day = QString::fromLocal8Bit("8月20日");
        info.time.index = 1;
        info.time.startTime = "19:00";
        info.time.endTime = "21:00";
        info.isEngTitle = false;
        info.chapterName = QString("%1 ").arg(QString::number(i+1)) + QString::fromLocal8Bit("讲次内容 语文数学英语等等");
        info.classStatus = QString::fromLocal8Bit("直播进行中");
        info.isExchanged = false;
        if (i == 3) {
            info.isExchanged = true;
        }
        ButtonInfo btnInfo;
        btnInfo.text = QString::fromLocal8Bit("去上课");
        btnInfo.status = 0;
        btnInfo.btnType = 0;

        ButtonInfo btnInfo2;
        btnInfo2.text = QString::fromLocal8Bit("课堂巩固");
        btnInfo2.status = 0;
        btnInfo2.btnType = 1;

        ButtonInfo btnInfo3;
        btnInfo3.text = QString::fromLocal8Bit("学习报告");
        btnInfo3.status = 0;
        btnInfo3.btnType = 2;

        info.buttons << btnInfo << btnInfo2 << btnInfo3;
        TeacherInfo tInfo;
        tInfo.name =QString::fromLocal8Bit("武亚敏");
        tInfo.type = 0;
        tInfo.imgUrl = ":/res/default_boy_img.png";
        info.teachers.append(tInfo);
        TeacherInfo tInfo2;
        tInfo2.name =QString::fromLocal8Bit("武亚敏");
        tInfo2.type = 4;
        tInfo2.imgUrl = ":/res/default_boy_img.png";
        info.teachers.append(tInfo2);

        m_chapterList.append(info);
    }

    emit sigFinish();
}
void DataProviderImp::sltRequestMaterialList(const QString& par)
{
    m_materialListErrorCode = 0;
    QTime t;
    t.start();
    m_materialList.clear();
    while(t.elapsed() < 3000)
    {

    }
    m_materialListErrorCode = 1;

    emit sigFinish();
}
