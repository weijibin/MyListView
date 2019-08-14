#include "DataProvider.h"
#include "DataProviderImp.h"


DataProvider::DataProvider(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<FilterType>("FilterType");
    qRegisterMetaType<CourseToChapterPar>("CourseToChapterPar");

    m_dataThread = new QThread(this);

    m_imp  = new DataProviderImp;

    connect(m_imp,&DataProviderImp::sigFinish,this,&DataProvider::sltFinish);

    connect(this,&DataProvider::sigRequestCourseDateForMonth,m_imp,&DataProviderImp::sltRequestCourseDates); //请求当月 有课日期

    connect(this,&DataProvider::sigRequestClassCard,m_imp,&DataProviderImp::sltRequestClassCard); //请求直播数据

    connect(this,&DataProvider::sigRequestCourseCard,m_imp,&DataProviderImp::sltRequestCourseCard); //请求课程数据

    connect(this,&DataProvider::sigRequestChapterList,m_imp,&DataProviderImp::sltRequestChapterList); //请求场次列表

    connect(this,&DataProvider::sigRequestMaterialList,m_imp,&DataProviderImp::sltRequestMaterialList); //请求学习资料

    m_imp->moveToThread(m_dataThread);
    m_dataThread->start();

    m_loadingDlg = new LoadingDlg;
}

DataProvider::~DataProvider()
{
    m_dataThread->terminate();
    delete m_imp;

    if(!m_isDlgHasPrnt)
        delete m_loadingDlg;
}

void DataProvider::setParentWidget(QWidget *parent)
{
    m_loadingDlg->setParent(parent,m_loadingDlg->windowFlags());
    m_isDlgHasPrnt = true;
}

void DataProvider::sltFinish()
{
    m_loadingDlg->close();
}

int DataProvider::requestClassCard(const QDate &start ,const QDate &end,QList<ClassCardInfo>& cards)
{
    emit this->sigRequestClassCard(start,end);
    m_loadingDlg->exec();

    cards = m_imp->getClassCardResult();

    return m_imp->getClassCardResultCode();
}

int DataProvider::requestCourseCard(const FilterType &type,QList<CourseCardInfo>& cards)
{
    emit this->sigRequestCourseCard(type);
    m_loadingDlg->exec();

    cards = m_imp->getCourseCardResult();
    return m_imp->getCourseCardResultCode();
}

int DataProvider::requestCourseDateForMonth(const QDate &date, QList<QString> &courseDates)
{
    emit this->sigRequestCourseDateForMonth(date);
    m_loadingDlg->exec();

    courseDates = m_imp->getCourseDateResult();
    return m_imp->getCourseDateResultCode();
}

int DataProvider::requestChapterList(const CourseToChapterPar& par,QList<ChapterInfo> & chapters)
{
    emit this->sigRequestChapterList(par);
    m_loadingDlg->exec();

    chapters = m_imp->getChapterListResult();
    return m_imp->getChapterListResultCode();
}

int DataProvider::requestMaterialList(const QString& par,QList<MaterialUnit> & materials)
{
    emit this->sigRequestMaterialList(par);
    m_loadingDlg->exec();

    materials = m_imp->getMaterialListResult();
    return m_imp->getMaterialListResultCode();
}
