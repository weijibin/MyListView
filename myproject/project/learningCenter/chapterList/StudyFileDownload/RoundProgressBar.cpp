#include "RoundProgressBar.h"
#include <QPainter>


RoundProgressBar::RoundProgressBar(QWidget *parent)
    : QWidget(parent)
    , m_rorateAngle(0)
    , m_present(0)
    , m_border(2)
{

}

void RoundProgressBar::setRotateDelta(int delta)
{
    m_rorateAngle = delta;

}

void RoundProgressBar::setPresent(int present)
{
    if (present != m_present) {
        m_present = present;
        update();
    }
}

void RoundProgressBar::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    m_rorateAngle = 360 * m_present / 100;

    int side = qMin(width(), height());
    QRectF outRect(0, 0, side, side);
    QRectF inRect(m_border, m_border, side - 2*m_border, side - 2*m_border);
    QString valueStr = QString("%1%").arg(QString::number(m_present));

    p.setPen(Qt::NoPen);
    p.setBrush(QBrush(QColor(221, 225, 229)));
    p.drawEllipse(outRect);
    p.setBrush(QBrush(QColor(255, 77, 69)));
    p.drawPie(outRect, (90-m_rorateAngle)*16, m_rorateAngle*16);

    p.setBrush(QColor(255, 255, 255));
    p.drawEllipse(inRect);

    QFont f = QFont("Microsoft YaHei");
    f.setPixelSize(12);
    p.setFont(f);
    p.setPen(QColor("#858C96"));
    p.drawText(inRect, Qt::AlignCenter, valueStr);
}
