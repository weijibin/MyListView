#include "ToolButton.h"
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QFont>

ToolButton::ToolButton(QWidget *parent) : QPushButton(parent)
{
    m_icon = ":/res/icon_fanhui.png";
    m_icon_hover = ":/res/icon_fanhui_hover.png";
    m_font.setFamily("Microsoft YaHei");
    m_font.setPixelSize(15);

    m_color = "#212831";
    m_color_hover = "#FF5E50";
}

void ToolButton::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing,true);
    p.setFont(m_font);
    if(m_isHover)
    {
        p.setPen(QColor(m_color_hover));
        p.drawPixmap(5,5,20,20,QPixmap(m_icon_hover));
    }
    else
    {
        p.setPen(QColor(m_color));
        p.drawPixmap(5,5,20,20,QPixmap(m_icon));
    }

    p.drawText(30,6,28,18,Qt::AlignCenter,m_name);

}

void ToolButton::enterEvent(QEvent *event)
{
    m_isHover = true;
    QPushButton::enterEvent(event);
}

void ToolButton::leaveEvent(QEvent *event)
{
    m_isHover = false;
    QPushButton::leaveEvent(event);
}

void ToolButton::setDisplyText(const QString & str)
{
    m_name = str;
    update();
}
