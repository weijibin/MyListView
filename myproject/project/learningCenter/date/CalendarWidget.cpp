#include "CalendarWidget.h"
#include <QCalendarWidget>
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QTextCharFormat>
#include <QDebug>

#include "CCalendarWidget.h"

CalendarWidget::CalendarWidget(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::NoDropShadowWindowHint | Qt::FramelessWindowHint | Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground, true);

    initUI();

    this->setContentsMargins(10,30,10,10);

}
///
///QToolButton *prevBtn = calendar->findChild<QToolButton*>(QLatin1String("qt_calendar_prevmonth"));
///QToolButton *bextBtn = calendar->findChild<QToolButton*>(QLatin1String("qt_calendar_nextmonth"));
///prevBtn->setIcon("你自己的图标");
///bextBtn->setIcon("你自己的图标");

void CalendarWidget::initUI()
{
    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    m_calendar = new CCalendarWidget(this);
    m_calendar->setObjectName("calendarObj");
//    m_calendar->setFocusPolicy(Qt::NoFocus);
    m_calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    layout->addWidget(m_calendar);


//    QTextCharFormat selectday;
//    //刷新日历表背景颜色
//    QBrush brush;
//    QColor color("#141414");
//    brush.setColor(color);
//    selectday.setBackground(brush);
//    m_calendar->setDateTextFormat(QDate::currentDate(), selectday);


    this->setLayout(layout);

    connect(m_calendar,&QCalendarWidget::clicked,[=](){
        this->hide();
        emit sigSelectedDate(m_calendar->selectedDate());
    });
}

void CalendarWidget::paintEvent(QPaintEvent*event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


void CalendarWidget::setCalendarDate(const QDate &date)
{
    m_calendar->setSelectedDate(date);
}
