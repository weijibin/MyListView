#include "DateWidget.h"
#include <QPainter>
#include <QDebug>


QMap<int,QString> DateWidget::m_dayOfWeek;

DateWidget::DateWidget(QWidget *parent) :
    QPushButton(parent)
{
    this->setCheckable(true);

    m_color = "#212831";
    m_color_info = "#ADB4BE";
    m_color_checked = "#FF5E50";

    m_font.setFamily("Microsoft YaHei");
    m_font.setPixelSize(20);

    m_font_info.setFamily("Microsoft YaHei");
    m_font_info.setPixelSize(12);

    m_dayOfWeek.insert(1,QString::fromLocal8Bit("周一"));
    m_dayOfWeek.insert(2,QString::fromLocal8Bit("周二"));
    m_dayOfWeek.insert(3,QString::fromLocal8Bit("周三"));
    m_dayOfWeek.insert(4,QString::fromLocal8Bit("周四"));
    m_dayOfWeek.insert(5,QString::fromLocal8Bit("周五"));
    m_dayOfWeek.insert(6,QString::fromLocal8Bit("周六"));
    m_dayOfWeek.insert(7,QString::fromLocal8Bit("周日"));
}

DateWidget::~DateWidget()
{

}

void DateWidget::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing,true);




    if(this->isChecked()){
        painter.setPen(QColor(m_color_checked));

        painter.save();
        painter.setFont(m_font);
        painter.drawText(m_rect_num,m_dateNum);
        painter.restore();

        painter.save();
        painter.setFont(m_font_info);
        painter.drawText(m_rect_week,m_dateOfWeek);

        {
            painter.setBrush(QBrush(QColor(m_color_checked)));
            painter.drawEllipse(m_rect_point);
        }

        painter.drawText(m_rect_info,m_courseInfo);
        painter.restore();

        painter.save();
        QPen pen;
        pen.setColor(QColor("#FF5E50"));
        pen.setWidth(4);
        painter.setPen(pen);
        painter.drawLine(rect().bottomRight(),rect().bottomLeft());
        painter.restore();

    } else {
        painter.save();
        painter.setPen(QColor(m_color));
        painter.setFont(m_font);
        painter.drawText(m_rect_num,m_dateNum);
        painter.restore();

        painter.save();
        painter.setPen(QColor(m_color_info));
        painter.setFont(m_font_info);
        painter.drawText(m_rect_week,m_dateOfWeek);

        {
            painter.setBrush(QBrush(QColor(m_color_info)));
            painter.drawEllipse(m_rect_point);
        }

        painter.drawText(m_rect_info,m_courseInfo);
        painter.restore();


        painter.save();
        QPen pen;
        pen.setColor(QColor("#F5F5F5"));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawLine(rect().topLeft(),rect().bottomLeft());
        painter.drawLine(rect().bottomRight(),rect().bottomLeft());
        painter.restore();
    }
}

const DateInfo& DateWidget::getDateInfo()
{
    return m_info;
}

void DateWidget::setDateInfo(const DateInfo &info)
{
    m_info = info;
    updateInfo();
}

void DateWidget::updateInfo()
{
    if(m_info.num < 1){
        m_courseInfo = "";
    } else {
        m_courseInfo = QString(QString::fromLocal8Bit("有%1场直播")).arg(m_info.num);
    }
    m_rect_info = QRect(26,54,70,18);

    m_rect_point = QRect(16,61,6,6);

    if(m_info.date == QDate::currentDate()){
        m_dateNum = QString::fromLocal8Bit("今日");
        m_rect_num = QRect(17,16,40,26);
    } else {
        m_dateNum = QString::number(m_info.date.day());
        m_rect_num = QRect(16,16,24,26);
    }

    m_dateOfWeek = m_dayOfWeek.value(m_info.date.dayOfWeek());
    m_rect_week = QRect(117,18,24,24);

    update();
}
