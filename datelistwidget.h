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
class QButtonGroup;
class QLabel;
class CalendarWidget;

class DateListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DateListWidget(QWidget *parent = 0);

    void initUi();
    void initConnections();

    void updateScrollArea();
signals:

public slots:

private slots:
    void onLeftClick();
    void onRightClick();

    void updateWidget_pre();
    void updateWidget_back();

private:
    void printLayoutWidgetsInfo();

private:
    DateListView * m_view;
    DateListModel * m_model;
    DateDelegate * m_delegate;

private:
    CalendarWidget * m_popupWidget;
    QLabel * m_dateLabel;
    QPushButton * m_subCtrl;
    QPushButton * m_left;
    QPushButton * m_right;
    QScrollArea * m_area;

    QWidget * m_scrolWidget;
    QHBoxLayout * m_scrolLayout;

    QList<DateWidget*> m_dateWidgets;
    QButtonGroup * m_btnGroup;

    int m_dateCount;   // total DateWidget count

    int m_dateVisibleNum; // the visible DateWidget count

    int m_dateWidgetWidth;
    int m_dateWidgetHeight;

    int m_aniDuration; // animation duration

};


#endif // DATALISTWIDGET_H
