#include "dataprovideimp.h"
#include <QTime>
#include <QDebug>

DataProvideImp::DataProvideImp(QObject *parent) : QObject(parent)
{

}

void DataProvideImp::sltRequestData(QString par)
{
    QTime t;
    t.start();
    while(t.elapsed() < 3000)
    {

    }
    qDebug()<<par;
    emit sigFinish();
}
