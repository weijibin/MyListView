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

class CalendarWidget;

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


    void setParentDlg(CalendarWidget *w ){m_parentDlg = w;}

    QDate getDate() const;
    void setDate(const QDate&date);

    QDate getSelectedDate() const;
    void setSelectedDate(const QDate& date);

    void setCourseDate(const QList<QDate>& m_coursesInfo);

    const QList<QDate>& getCourseDate() {return m_haveCoursDates;}

signals:
    void sigDayClicked(const QDate& date);
public slots:
    void sltShowPrevMonth();
    void sltShowNextMonth();
protected:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

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

    CalendarWidget* m_parentDlg = nullptr;
    bool m_isRequestData = false;
};

#endif // CCALENDARWIDGET_H
