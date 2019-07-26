#ifndef DATELISTVIEW_H
#define DATELISTVIEW_H

#include <QListView>
class DateListView : public QListView
{
    Q_OBJECT
public:
    DateListView(QWidget *parent = Q_NULLPTR);
};

#endif // DATELISTVIEW_H
