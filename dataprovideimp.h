#ifndef DATAPROVIDEIMP_H
#define DATAPROVIDEIMP_H

#include <QObject>

class DataProvideImp : public QObject
{
    Q_OBJECT
public:
    explicit DataProvideImp(QObject *parent = nullptr);

signals:
    void sigFinish();
public slots:
    void sltRequestData(QString par);
};

#endif // DATAPROVIDEIMP_H
