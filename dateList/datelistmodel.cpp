#include "datelistmodel.h"


int DateListModel::rowCount(const QModelIndex &parent) const
{
    return stringList.count();
}

QVariant DateListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= stringList.size())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return "";
//        return stringList.at(index.row());
    }
    else if(role == Qt::UserRole)
    {
        return stringList.at(index.row());
    }
    else
        return QVariant();
}
