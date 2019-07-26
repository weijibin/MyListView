#ifndef DATELISTMODEL_H
#define DATELISTMODEL_H

#include <QAbstractListModel>
#include <QStandardItemModel>

class DateListModel : public QAbstractListModel
{
     Q_OBJECT

public:
    DateListModel(const QStringList &strings, QObject *parent = 0)
        : QAbstractListModel(parent), stringList(strings) {}

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

private:
    QStringList stringList;
};

#endif // DATELISTMODEL_H
