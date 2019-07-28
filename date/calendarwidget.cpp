#include "calendarwidget.h"
#include <QCalendarWidget>
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

CalendarWidget::CalendarWidget(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::NoDropShadowWindowHint | Qt::FramelessWindowHint | Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground, true);
//    setAttribute(Qt::WA_NoSystemBackground, false);

//    setAutoFillBackground(true);

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

    m_calendar = new QCalendarWidget(this);
    m_calendar->setObjectName("calendarObj");
    m_calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    layout->addWidget(m_calendar);

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

//    p.drawRect(this->rect());
}
