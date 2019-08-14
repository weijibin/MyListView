#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H
//数据提供者

#include <QObject>
#include <QList>
#include <QDate>
#include <QThread>

#include "common/common.h"
#include "common/LoadingDlg.h"

class DataProviderImp;

class DataProvider : public QObject
{
    Q_OBJECT

    DataProvider(QObject *parent = nullptr);
    ~DataProvider();

    DataProvider(const DataProvider &)=delete;
    DataProvider& operator=(const DataProvider &)=delete;
public:
    static DataProvider & GetInstance()
    {
        static DataProvider instance;
        return instance;
    }

    void setParentWidget(QWidget * parent);

    ///
    /// \brief requestClassCard
    /// \param start
    /// \param end
    /// \param cards
    /// \return
    /// return errCode  1: success, other : error;
    int requestClassCard(const QDate &start ,const QDate &end,QList<ClassCardInfo>& cards);

    ///
    /// \brief requestCourseCard
    /// \param type
    /// \param cards
    /// \return
    ///
    int requestCourseCard(const FilterType & type,QList<CourseCardInfo>& cards);

    ///
    /// \brief requestCourseDateForMonth
    /// \param date          input  the date be queried
    /// \param courseDates   output
    /// \return
    /// return errCode  1: success, other : error;
    int requestCourseDateForMonth(const QDate & date,QList<QString> & courseDates);

    ///
    /// \brief requestChapterList
    /// \param par
    /// \param chapters
    /// \return
    /// query charpter list
    int requestChapterList(const CourseToChapterPar & par ,QList<ChapterInfo> & chapters);

    ///
    /// \brief requestMaterialList
    /// \param url
    /// \param materials
    /// \return
    ///
    int requestMaterialList(const QString &url, QList<MaterialUnit> & materials);

signals:
    void sigRequestClassCard(const QDate &start ,const QDate &end);

    void sigRequestCourseCard(const FilterType& type);

    void sigRequestCourseDateForMonth(const QDate& cur);

    void sigRequestChapterList(const CourseToChapterPar & par);

    void sigRequestMaterialList(const QString& url);
private slots:
    void sltFinish();

private:

    DataProviderImp * m_imp = nullptr;
    LoadingDlg * m_loadingDlg = nullptr;
    QThread * m_dataThread = nullptr;

    bool m_isDlgHasPrnt = false;
};

#endif // DATAPROVIDER_H
