#include "dataprovide.h"
#include <QThread>
#include <QTime>
#include <QTimer>
#include "dataprovideimp.h"

DataProvide::DataProvide(QWidget *parent) :QObject(parent)
{

    m_loadingDlg = new LoadingDlg(parent);

    m_thread = new QThread(this);
    m_imp = new DataProvideImp;

    connect(m_imp,&DataProvideImp::sigFinish,
            this,&DataProvide::sltFinish);
    connect(this,&DataProvide::sigRequest,m_imp,&DataProvideImp::sltRequestData);

    m_imp->moveToThread(m_thread);
    m_thread->start();
}

DataProvide::~DataProvide()
{
    m_thread->terminate();
    delete m_imp;
//    delete m_loadingDlg;
}

void DataProvide::setParentWidget(QWidget *parent)
{
    m_loadingDlg->setParent(parent,m_loadingDlg->windowFlags());
}

void DataProvide::sltFinish()
{
    m_loadingDlg->close();
}

void DataProvide::requestData()
{
    QString str = "requestData";
    emit this->sigRequest(str);

    m_loadingDlg->exec();
}
