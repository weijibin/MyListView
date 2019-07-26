#ifndef DATALISTWIDGET_H
#define DATALISTWIDGET_H

#include <QWidget>

#include "dateList/datelistview.h"
#include "dateList/datelistmodel.h"
#include "dateList/datedelegate.h"

class QPushButton;
class QScrollArea;
class QHBoxLayout;
class DateWidget;

class DateListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DateListWidget(QWidget *parent = 0);

    void initUi();

    void updateScrollArea();
signals:

public slots:

private slots:
    void onLeftClick();
    void onRightClick();

    void updateWidget_pre();
    void updateWidget_back();

private:
    void printLayoutWidgets();

private:
    DateListView * m_view;
    DateListModel * m_model;
    DateDelegate * m_delegate;

private:
    QPushButton * m_left;
    QPushButton * m_right;
    QScrollArea * m_area;

    QWidget * m_scrolWidget;
    QHBoxLayout * m_scrolLayout;

    QList<DateWidget*> m_dateWidgets;

    int m_dateCount;

    int m_dateVisibleNum;

    int m_dateWidgetWidth;
    int m_dateWidgetHeight;

    int m_aniDuration;

};


#endif // DATALISTWIDGET_H
