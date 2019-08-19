#include "CCalendarWidget.h"
#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QLabel>
#include <QDate>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QDebug>
#include <QFont>
#include <QButtonGroup>

static const QString s_strWeek[] = {
    QString::fromLocal8Bit("一"), QString::fromLocal8Bit("二"),
    QString::fromLocal8Bit("三"), QString::fromLocal8Bit("四"), QString::fromLocal8Bit("五"),
    QString::fromLocal8Bit("六"),QString::fromLocal8Bit("日"),
};

CCalendarWidget::CCalendarWidget(QWidget *parent) : QWidget(parent)
{
    m_dateFormat = QString::fromLocal8Bit("yyyy年M月");
    initWidget();
}

CCalendarWidget::~CCalendarWidget()
{

}

QDate CCalendarWidget::getDate() const
{
    return m_date;
}

void CCalendarWidget::setDate(const QDate &date)
{
    m_date = date;
    updateUiByDate();
}

QDate CCalendarWidget::getSelectedDate() const
{
    return m_selectedDate;
}

void CCalendarWidget::setSelectedDate(const QDate &date)
{
    qDebug()<<"CCalendarWidget::setSelectedDate=="<< date;
    int day = date.day();
    setDate(date.addDays(-1*day+1));

    m_selectedDate = date;
    updateUiBySelectedDate();

    //更新有课的控件
    updateUiByCourseInfo();
}

void CCalendarWidget::setCourseDate(const QList<QDate> &info)
{
    m_haveCoursDates = info;
    updateUiByCourseInfo();
}

void CCalendarWidget::initWidget()
{
    this->setObjectName("customCalendar");
    this->setContentsMargins(0,0,0,0);

    verLayoutCalendar = new QVBoxLayout(this);
//    verLayoutCalendar->setContentsMargins(2, 2, 2, 2);
    verLayoutCalendar->setContentsMargins(0, 0, 0, 0);
    verLayoutCalendar->setSpacing(0);

    //! [2]
    widgetTitle = new QWidget(this);
    widgetTitle->setObjectName("customCalendarTitle");


    widgetTitle->setFixedHeight(40);

    btnPrevMonth = new QPushButton(widgetTitle);
    btnPrevMonth->setObjectName("customCalendarPrev");

    labelTitle = new QLabel(widgetTitle);
    labelTitle->setAlignment(Qt::AlignCenter);
    labelTitle->setObjectName("customDateTitle");
    labelTitle->setText(QString::fromLocal8Bit("2016 年 04 月"));

    btnNextMonth = new QPushButton(widgetTitle);
    btnNextMonth->setObjectName("customCalendarNext");

    horLayoutTitle = new QHBoxLayout(widgetTitle);
    horLayoutTitle->addWidget(btnPrevMonth);
    horLayoutTitle->addWidget(labelTitle, 1);
    horLayoutTitle->addWidget(btnNextMonth);

    verLayoutCalendar->addWidget(widgetTitle);

    connect(btnPrevMonth, SIGNAL(clicked(bool)), this, SLOT(sltShowPrevMonth()));
    connect(btnNextMonth, SIGNAL(clicked(bool)), this, SLOT(sltShowNextMonth()));
    //! [2]

    //! [3]
    widgetWeek = new QWidget(this);
    widgetWeek->setFixedHeight(40);
    widgetWeek->setObjectName("widgetCalendarWeek");

    horLayoutWeek = new QHBoxLayout(widgetWeek);
    horLayoutWeek->setContentsMargins(0, 0, 0, 0);
    horLayoutWeek->setSpacing(0);
    for (int i = 0; i < Week; i++) {
        labelWeek[i] = new QLabel(widgetWeek);
        labelWeek[i]->setText(s_strWeek[i]);
        labelWeek[i]->setMinimumHeight(30);
        labelWeek[i]->setAlignment(Qt::AlignCenter);
        horLayoutWeek->addWidget(labelWeek[i]);
    }

    verLayoutCalendar->addWidget(widgetWeek);
    //! [3]

    //! [4]
    widgetBody = new QWidget(this);
    widgetBody->setObjectName("customCalendarBody");
    verLayoutCalendar->addWidget(widgetBody, 1);

    gridLayoutBody = new QGridLayout(widgetBody);
    gridLayoutBody->setHorizontalSpacing(0);
    gridLayoutBody->setVerticalSpacing(0);
    gridLayoutBody->setContentsMargins(0, 0, 0, 0);

    buttonGroup = new QButtonGroup(this);

    for (int i = 0; i < 42; i++) {
        labelDay[i] = new DayLabel(widgetBody);
        labelDay[i]->setText(QString::number(i));
        gridLayoutBody->addWidget(labelDay[i], i / 7, i % 7);

        buttonGroup->addButton(labelDay[i]);
    }
    //! [4]

    connect(buttonGroup,static_cast<void(QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked),
    [=,this](QAbstractButton*button){
        DayLabel * cur = qobject_cast<DayLabel*>(button);
        m_selectedDate = cur->getDate();
        emit sigDayClicked(m_selectedDate);
    });
}


void CCalendarWidget::updateUiByDate()
{
    int nWeek  = m_date.dayOfWeek();
    int nMonthDays = m_date.daysInMonth();

    labelTitle->setText(m_date.toString(m_dateFormat));

    for(int i = 0; i< nWeek-1; i++)
    {
        labelDay[i]->clearText();
    }

    for (int i = nWeek-1 ; i < (nWeek+nMonthDays-1); i++) {
        labelDay[i]->setDate(m_date.addDays(i-nWeek+1));
    }

    for (int i = (nWeek+nMonthDays-1); i < 42; i++) {
        labelDay[i]->clearText();
    }
}

void CCalendarWidget::updateUiBySelectedDate()
{
    if(m_selectedDate.month() != m_date.month())
    {
        for(int i=0; i<42; i++)
        {
           DayLabel*label = labelDay[i];

           //noExclusive
           buttonGroup->setExclusive(false);
           label->setChecked(false);
           buttonGroup->setExclusive(true);
        }
    }
    else
    {
        for(int i=0; i<42; i++)
        {
           DayLabel*label = labelDay[i];
           if(label->getDate() == m_selectedDate)
           {
               label->setChecked(true);
           }
           else
           {
               label->setChecked(false);
           }
        }
    }
}

void CCalendarWidget::updateUiByCourseInfo()
{
    for(int i=0; i<42; i++)
    {
        DayLabel*label = labelDay[i];
        if(m_haveCoursDates.contains(label->getDate()))
        {
            label->setIsHaveCourse(true);
        }
        else
        {
            label->setIsHaveCourse(false);
        }
    }
}

void CCalendarWidget::sltShowPrevMonth()
{
    //===============================
    //request data
    qDebug()<<"need update sltShowPrevMonth";
    QList<QDate> lst;
    lst.append(QDate::currentDate());
    lst.append(QDate::currentDate().addDays(2));
    lst.append(QDate::currentDate().addDays(5));
    this->setCourseDate(lst);
    //===============================

    setDate(m_date.addMonths(-1));
    updateUiBySelectedDate();
    updateUiByCourseInfo();
}

void CCalendarWidget::sltShowNextMonth()
{
    //===============================
    //request data
    qDebug()<<"need update sltShowNextMonth";
    QList<QDate> lst;
    lst.append(QDate::currentDate());
    lst.append(QDate::currentDate().addDays(2));
    lst.append(QDate::currentDate().addDays(5));
    this->setCourseDate(lst);
    //===============================

    setDate(m_date.addMonths(1));
    updateUiBySelectedDate();
    updateUiByCourseInfo();
}
