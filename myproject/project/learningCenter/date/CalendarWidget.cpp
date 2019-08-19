#include "CalendarWidget.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QTextCharFormat>
#include <QDebug>
#include <QGraphicsDropShadowEffect>

#include "customcalendar/CCalendarWidget.h"

CalendarWidget::CalendarWidget(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::NoDropShadowWindowHint | Qt::FramelessWindowHint | Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground, true);

    initUI();

    this->setContentsMargins(10,30,10,10);

    this->setFixedSize(374,381);



    initOutLineWithShadow();

//    QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect(this);
//    effect->setOffset(QPointF(0,0));
//    effect->setColor(QColor("#444444"));
//    effect->setBlurRadius(10);
//    this->setGraphicsEffect(effect);


    //init data
//    this->setCalendarDate(QDate::currentDate());

}

void CalendarWidget::initOutLineWithShadow()
{
    int shadowWidth = 4;
    int arrowWidth = 15;
    int arrowHeight = 14;
    int arrowPos = 50;

    m_realRect.setRect(shadowWidth,(shadowWidth+arrowHeight),(374-2*shadowWidth),(381-(2*shadowWidth+arrowHeight)));

    QPoint p1 = (m_realRect.topLeft()+QPoint(arrowPos,0));
    m_outLine.moveTo(p1);
    QPoint p2 = (p1+QPoint(arrowWidth,-1*arrowHeight));
    m_outLine.lineTo(p2);
    QPoint p3 = (p2+QPoint(arrowWidth,arrowHeight));
    m_outLine.lineTo(p3);
    m_outLine.addRoundedRect(QRectF(m_realRect),8,8);

    int radius = 5;

    {
        arrowPos--;
        arrowWidth +=2;

        QRect rect = m_realRect.adjusted(-1,-1,1,1);
        QPoint p11 = (rect.topLeft()+QPoint(arrowPos,0));
        m_shadowPath1.moveTo(p11);
        QPoint p12 = (p11+QPoint(arrowWidth,-1*arrowHeight));
        m_shadowPath1.lineTo(p12);
        QPoint p13 = (p12+QPoint(arrowWidth,arrowHeight));
        m_shadowPath1.lineTo(p13);
        m_shadowPath1.addRoundedRect(QRectF(rect),radius,radius);
    }
    {
        arrowPos--;
        arrowWidth +=2;

        QRect rect = m_realRect.adjusted(-2,-2,2,2);
        QPoint p11 = (rect.topLeft()+QPoint(arrowPos,0));
        m_shadowPath2.moveTo(p11);
        QPoint p12 = (p11+QPoint(arrowWidth,-1*arrowHeight));
        m_shadowPath2.lineTo(p12);
        QPoint p13 = (p12+QPoint(arrowWidth,arrowHeight));
        m_shadowPath2.lineTo(p13);
        m_shadowPath2.addRoundedRect(QRectF(rect),radius,radius);
    }
    {

//        arrowPos--;
//        arrowWidth +=2;

        QRect rect = m_realRect.adjusted(-3,-3,3,3);
        QPoint p11 = (rect.topLeft()+QPoint(arrowPos,0));
        m_shadowPath3.moveTo(p11);
        QPoint p12 = (p11+QPoint(arrowWidth,-1*arrowHeight));
        m_shadowPath3.lineTo(p12);
        QPoint p13 = (p12+QPoint(arrowWidth,arrowHeight));
        m_shadowPath3.lineTo(p13);
        m_shadowPath3.addRoundedRect(QRectF(rect),radius,radius);
    }
    {
//        arrowPos--;
//        arrowWidth +=2;

        QRect rect = m_realRect.adjusted(-4,-4,4,4);
        QPoint p11 = (rect.topLeft()+QPoint(arrowPos,0));
        m_shadowPath4.moveTo(p11);
        QPoint p12 = (p11+QPoint(arrowWidth,-1*arrowHeight));
        m_shadowPath4.lineTo(p12);
        QPoint p13 = (p12+QPoint(arrowWidth,arrowHeight));
        m_shadowPath4.lineTo(p13);
        m_shadowPath4.addRoundedRect(QRectF(rect),radius,radius);
    }
}

void CalendarWidget::initUI()
{
    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    m_calendar = new CCalendarWidget(this);

    layout->addWidget(m_calendar);

    this->setLayout(layout);

    connect(m_calendar,&CCalendarWidget::sigDayClicked,[=](const QDate&cur){
        this->hide();
        emit sigSelectedDate(cur);
    });
}

void CalendarWidget::paintEvent(QPaintEvent*event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    //shadow
    {
        p.save();
        p.setRenderHint(QPainter::Antialiasing, true);
        QColor color(92, 93, 95, 50);
        int arr[10] = {80, 50, 40, 30, 20, 10, 5, 5};
        color.setAlpha(arr[0]);
        p.setPen(color);
        p.drawPath(m_shadowPath1);
        color.setAlpha(arr[1]);
        p.setPen(color);
        p.drawPath(m_shadowPath2);
        color.setAlpha(arr[2]);
        p.setPen(color);
        p.drawPath(m_shadowPath3);
        color.setAlpha(arr[3]);
        p.setPen(color);
        p.drawPath(m_shadowPath4);
        p.restore();
    }

    //outline
    p.save();
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(QPen(Qt::NoPen));
    p.setBrush(QColor("#FFFFFF"));
    p.drawPath(m_outLine);
    p.restore();
}


void CalendarWidget::setCalendarDate(const QDate &date)
{
    qDebug()<<"CalendarWidget::setCalendarDate"<<date;

    if(m_calendar->getSelectedDate().month() != date.month())
    {
        //request data
        qDebug()<<"need update courseInfo";
        //========================================
        //setNew Couse Date
        QList<QDate> lst;
        lst.append(QDate::currentDate());
        lst.append(QDate::currentDate().addDays(2));
        lst.append(QDate::currentDate().addDays(5));
        setCourseDate(lst);
        //======================================
    }
    m_calendar->setSelectedDate(date);
}

const QDate& CalendarWidget::getCalendarDate()
{
    return m_calendar->getSelectedDate();
}

void CalendarWidget::setCourseDate(const QList<QDate> &coursesInfo)
{
    m_calendar->setCourseDate(coursesInfo);
}
