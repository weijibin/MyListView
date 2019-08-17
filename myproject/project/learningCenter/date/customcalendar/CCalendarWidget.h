#ifndef CCALENDARWIDGET_H
#define CCALENDARWIDGET_H

#include <QWidget>
#include <QLabel>
#include "DayLabel.h"
#include "common/common.h"

QT_BEGIN_NAMESPACE
class QPushButton;
class QComboBox;
class QGroupBox;
class QLineEdit;
class QDate;
class QGridLayout;
class QHBoxLayout;
class QVBoxLayout;
class QButtonGroup;

QT_END_NAMESPACE

typedef enum {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Week
} E_WEEK;

class CCalendarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CCalendarWidget(QWidget *parent = 0);
    ~CCalendarWidget();

    QDate getDate() const;
    void setDate(const QDate&date);

    QDate getSelectedDate() const;
    void setSelectedDate(const QDate& date);

    void setCourseDate(const QList<QDate>& m_coursesInfo);

signals:
    void sigDayClicked(const QDate& date);
public slots:
    void sltShowPrevMonth();
    void sltShowNextMonth();

private:
    void initWidget();

    void updateUiByDate();
    void updateUiBySelectedDate();
    void updateUiByCourseInfo();

private:
    QVBoxLayout *verLayoutCalendar;

    QWidget *widgetTitle;
    QLabel *labelTitle;
    QPushButton *btnPrevMonth;
    QPushButton *btnNextMonth;
    QHBoxLayout *horLayoutTitle;

    QWidget *widgetWeek;
    QLabel *labelWeek[Week];
    QHBoxLayout *horLayoutWeek;

    QWidget *widgetBody;
    DayLabel *labelDay[42];
    QButtonGroup *buttonGroup;
    QGridLayout *gridLayoutBody;

private:
    QDate m_date;  //当月1号日期

    QDate m_selectedDate; //选中的日期

    QString m_dateFormat;

    QList<QDate> m_haveCoursDates;
};

#endif // CCALENDARWIDGET_H
