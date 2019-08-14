#include "CalendarButton.h"
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QFont>

CalendarButton::CalendarButton(QWidget *parent) : QPushButton(parent)
{
    m_icon = ":/res/icon_down.png";
    m_font.setFamily("Microsoft YaHei");
    m_font.setPixelSize(14);
}

void CalendarButton::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing,true);
    p.setFont(m_font);
    p.drawText(0,0,70,20,Qt::AlignCenter,m_name);
    p.drawPixmap(74,8,6,4,QPixmap(m_icon));
}

void CalendarButton::setDisplyText(const QString & str)
{
    m_name = str;
    update();
}
