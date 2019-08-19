#ifndef DATALISTWIDGET_H
#define DATALISTWIDGET_H

#include <QWidget>
#include "common/common.h"

class QPushButton;
class QScrollArea;
class QHBoxLayout;
class DateWidget;
class QButtonGroup;
class QLabel;
class CalendarWidget;
class CalendarButton;
class QPropertyAnimation;

class DateListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DateListWidget(QWidget *parent = 0);

    void initUi();
    void initConnections();

    void updateScrollArea();

    void refreshByDate(const QDate& date);

signals:
    void sigSelectedDate(const QDate& date);

public slots:
protected:
    void setCalendarDate(const QDate& date);
    void updateWeekListByDate(const QDate& date);

    void updateWeekSelected(const QDate& date);

    virtual void paintEvent(QPaintEvent *event) override;

private slots:
    void onLeftClick();
    void onRightClick();

    void updateWidget_pre();
    void updateWidget_back();

private:
    void printLayoutWidgetsInfo();

private:
    CalendarWidget * m_popupWidget;

    QString m_dateFormat;

    CalendarButton * m_dateBtn;

    QPushButton * m_left;
    QPushButton * m_right;
    QPushButton * m_today;

    QScrollArea * m_area;

    QWidget * m_scrolWidget;
    QHBoxLayout * m_scrolLayout;

    QList<DateWidget*> m_dateWidgets;

    QList<DateInfo> m_curDateInfos;

    QButtonGroup * m_btnGroup;

    int m_dateCount;   // total DateWidget count

    int m_dateVisibleNum; // the visible DateWidget count

    int m_dateWidgetWidth;
    int m_dateWidgetHeight;

    int m_aniDuration; // animation duration
    QPropertyAnimation *m_animation = nullptr;

};


#endif // DATALISTWIDGET_H
