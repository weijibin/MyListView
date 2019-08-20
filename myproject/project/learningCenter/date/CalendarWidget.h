#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QPainterPath>

class CCalendarWidget;

class CalendarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarWidget(QWidget *parent = nullptr);

    void initUI();

    void setCalendarDate(const QDate& date);
    bool requestDataBeforeShow();
    const QDate& getCalendarDate();
    void setCourseDate(const QList<QDate>& info);
signals:
    void sigSelectedDate(const QDate& date);
public slots:
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    void initOutLineWithShadow();
private:
    CCalendarWidget * m_calendar;

    //shadow
    QRect m_realRect;
    QPainterPath m_outLine;
    QPainterPath m_shadowPath1;
    QPainterPath m_shadowPath2;
    QPainterPath m_shadowPath3;
    QPainterPath m_shadowPath4;
};

#endif // CALENDARWIDGET_H
