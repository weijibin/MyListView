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
    int getClassCardResultCode(){return m_classErrorCode;}

    QList<CourseCardInfo> getCourseCardResult(){return m_courseInfo;}
    int getCourseCardResultCode(){return m_courseErrorCode;}

    QList<QString> getCourseDateResult(){return m_courseDates;}
    int getCourseDateResultCode(){return m_courseDateErrorCode;}

    QList<ChapterInfo> getChapterListResult(){return m_chapterList;}
    int getChapterListResultCode(){return m_chapterListErrorCode;}

    QList<MaterialUnit> getMaterialListResult(){return m_materialList;}
    int getMaterialListResultCode(){return m_materialListErrorCode;}
signals:
    void sigFinish();
public slots:
    void sltRequestClassCard(const QDate &start ,const QDate &end);
    void sltRequestCourseCard(const FilterType & filter);
    void sltRequestCourseDates(const QDate & cur);
    void sltRequestChapterList(const CourseToChapterPar& par);
    void sltRequestMaterialList(const QString&par);
private:
    QList<ClassCardInfo> m_classInfo;
    int     m_classErrorCode = 0;
    QList<CourseCardInfo> m_courseInfo;
    int     m_courseErrorCode = 0;

    QList<QString> m_courseDates;
    int m_courseDateErrorCode = 0;

    QList<ChapterInfo> m_chapterList;
    int m_chapterListErrorCode = 0;

    QList<MaterialUnit> m_materialList;
    int m_materialListErrorCode = 0;
};

#endif // DATAPROVIDERIMP_H
