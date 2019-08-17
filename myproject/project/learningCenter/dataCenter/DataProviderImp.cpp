#include "DataProviderImp.h"
#include <QTime>
#include <QDebug>

DataProviderImp::DataProviderImp(QObject *parent) : QObject(parent)
{

}

void DataProviderImp::sltRequestClassCard(const QDate &start ,const QDate &end)
{
    m_classErrorCode = 0;
    QTime t;
    t.start();
    m_classInfo.clear();
    while(t.elapsed() < 3000)
    {

    }
    m_classErrorCode = 1;

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
