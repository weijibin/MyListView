#include "RoundMovieWidget.h"

#include <QPainter>
#include <QConicalGradient>

RoundMovieWidget::RoundMovieWidget(QWidget *parent)
    : QWidget(parent)
    , m_angle(0)
    , m_radius(4)
{
    m_borderColor = QColor("#F1F1F1");
    m_timeLine.setFrameRange(1, 360);
    m_timeLine.setDuration(1500);
    m_timeLine.setLoopCount(0);
    m_timeLine.setCurveShape(QTimeLine::LinearCurve);
    connect(&m_timeLine, SIGNAL(frameChanged(int)), this, SLOT(onFrameChanged(int)));
}

void RoundMovieWidget::setPixmap(const QPixmap &pix)
{
    m_pix = pix;
}

void RoundMovieWidget::startMovie()
{
    m_timeLine.start();
}

void RoundMovieWidget::stopMovie()
{
    m_timeLine.stop();
}

void RoundMovieWidget::setRadius(int radius)
{
    m_radius = radius;
}

void RoundMovieWidget::setBorderColor(QColor color)
{
    m_borderColor = color;
}

void RoundMovieWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    int w = width();
    int h = height();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QConicalGradient conicalGradient(w/2, h/2, -m_angle);
    conicalGradient.setColorAt(0, QColor(241, 50, 50, 255));
    conicalGradient.setColorAt(0.7, QColor(136, 202, 255, 0));
    conicalGradient.setColorAt(1.0, QColor(255, 0, 0, 0));

    QPainterPath path;
    path.setFillRule(Qt::OddEvenFill);
    path.addEllipse(m_radius, m_radius, w-m_radius*2, h-m_radius*2); // in circle
    path.addEllipse(0, 0, w, h); // out circle

    painter.setBrush(QBrush(m_borderColor));
    painter.fillPath(path, QBrush(m_borderColor));

    if (m_timeLine.state() == QTimeLine::Running) {
        painter.setPen(m_borderColor);
        painter.setBrush(QBrush(conicalGradient));
        painter.drawPath(path);
    }

    QPainterPath head;
    head.addEllipse(m_radius, m_radius, w-m_radius*2, h-m_radius*2);
    painter.fillPath(head, QBrush(m_pix));
}

void RoundMovieWidget::onFrameChanged(int frame)
{
    m_angle = frame;
    if (m_angle >= 360) {
        m_angle %= 360;
    }

    update();
}
