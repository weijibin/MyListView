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
