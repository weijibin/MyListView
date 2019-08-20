#ifndef DATAPROVIDERIMP_H
#define DATAPROVIDERIMP_H

#include <QObject>
#include "common/common.h"

class DataProviderImp : public QObject
{
    Q_OBJECT
public:
    explicit DataProviderImp(QObject *parent = 0);

    QList<ClassCardInfo> getClassCardResult(){return m_classInfo;}
    ClassCardsPar getClassCardPar(){return m_classPar;}
    int getClassCardResultCode(){return m_classErrorCode;}

    QList<DateInfo> getClassDateResult() {return m_classDateInfo;}
    int getClassDateResultCode() {return m_classDateErroCode;}

    QList<CourseCardInfo> getCourseCardResult(){return m_courseInfo;}
    int getCourseCardResultCode(){return m_courseErrorCode;}
    int getCourseCardNextZone(){return m_courseNextZone;}

    CourseConfigInfo getCourseConfigResult(){return m_courseConfig;}
    int getCourseConfigResultCode(){return m_courseConfigErrorCode;}

    QList<QDate> getCourseDateResult(){return m_courseDates;}
    int getCourseDateResultCode(){return m_courseDateErrorCode;}

    QList<ChapterInfo> getChapterListResult(){return m_chapterList;}
    int getChapterListResultCode(){return m_chapterListErrorCode;}

    QList<MaterialUnit> getMaterialListResult(){return m_materialList;}
    int getMaterialListResultCode(){return m_materialListErrorCode;}
signals:
    void sigFinish();
public slots:
    void sltRequestClassCard(const QDate &start ,int direction);
    void sltRequestClassNumInPeriod(const QDate &start ,const QDate &end);
    void sltRequestCourseCard(const FilterType & filter);
    void sltRequestCourseConfig();
    void sltRequestCourseDates(const QDate & cur);
    void sltRequestChapterList(const CourseToChapterPar& par);
    void sltRequestMaterialList(const QString&par);
private:
    QList<ClassCardInfo> m_classInfo;
    ClassCardsPar m_classPar;
    int     m_classErrorCode = 0;

    QList<DateInfo> m_classDateInfo;
    int             m_classDateErroCode = 0;

    QList<CourseCardInfo> m_courseInfo;
    int     m_courseErrorCode = 0;
    int     m_courseNextZone = 1;

    CourseConfigInfo m_courseConfig;
    int     m_courseConfigErrorCode = 0;

    QList<QDate> m_courseDates;
    int m_courseDateErrorCode = 0;

    QList<ChapterInfo> m_chapterList;
    int m_chapterListErrorCode = 0;

    QList<MaterialUnit> m_materialList;
    int m_materialListErrorCode = 0;
};

#endif // DATAPROVIDERIMP_H
