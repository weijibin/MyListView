#include "DayLabel.h"
#include "CCalendarWidget.h"
#include <QPainter>
#include <QDebug>

DayLabel::DayLabel(QWidget *parent):
    QPushButton(parent)
{
    setCheckable(true);
    setFixedHeight(46);
    m_rect_point.setRect((48/2),39,5,5);

    this->setContentsMargins(9,9,9,9);
}

void DayLabel::clearText()
{
    this->setText("");
    this->setEnabled(false);
}

void DayLabel::setDate(const QDate &date)
{
    this->setEnabled(true);

    m_date = date;

    QString str;
    if(m_date == QDate::currentDate()){
        str = QString::fromLocal8Bit("今");
    } else {
        str = QString::number(m_date.day());
    }
    this->setText(str);
}

void DayLabel::setIsHaveCourse(bool is)
{
    m_isHaveCourse = is;
}

void DayLabel::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);


    if(m_isHaveCourse)
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing,true);
        painter.save();
        painter.setPen(QColor("#FF5E50"));

        painter.setBrush(QBrush(QColor("#FF5E50")));
        painter.drawEllipse(m_rect_point);

        painter.restore();
    }
}
