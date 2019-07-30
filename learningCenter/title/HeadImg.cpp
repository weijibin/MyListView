#include "HeadImg.h"
#include <QPainter>
#include <QPainterPath>
#include <QFont>

HeadImg::HeadImg(const QPixmap &map,QWidget*parent) : QWidget(parent)
{;
    m_pix = map.scaled(30,30,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    this->setFixedSize(30,30);

    m_pen.setColor("#FB5E50");
    m_brush.setColor(QColor("#FB5E50"));


    m_brush.setStyle(Qt::SolidPattern);
    m_pen.setWidth(2);

}

void HeadImg::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing,true);


    painter.save();
    QPainterPath path;
    path.addEllipse(rect().center(),13,13);
    painter.setClipPath(path);
    painter.drawPixmap(rect(),m_pix);
    painter.restore();

    painter.save();
    painter.setPen(m_pen);
    painter.drawEllipse(rect().center(),13,13);
    painter.restore();

}
