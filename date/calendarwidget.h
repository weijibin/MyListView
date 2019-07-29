#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QCalendarWidget>

class CalendarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarWidget(QWidget *parent = nullptr);

    void initUI();

    void setCalendarDate(const QDate& date);
signals:
    void sigSelectedDate(const QDate& date);
public slots:
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    QCalendarWidget * m_calendar;
};

#endif // CALENDARWIDGET_H
