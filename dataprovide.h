#ifndef DATAPROVIDE_H
#define DATAPROVIDE_H

#include <QObject>
#include "LoadingDlg.h"
class QThread;
class DataProvideImp;
class DataProvide : public QObject
{
    Q_OBJECT
public:
    explicit DataProvide(QWidget *parent = 0);

    ~DataProvide();

    void setParentWidget(QWidget * parent);

    void requestData();
signals:
    void sigRequest(const QString &par);
private slots:
    void sltFinish();
private:
    QThread * m_thread = nullptr;
    LoadingDlg * m_loadingDlg = nullptr;
    DataProvideImp * m_imp = nullptr;
};

#endif // DATAPROVIDE_H
