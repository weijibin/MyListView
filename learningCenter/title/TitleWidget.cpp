#include "TitleWidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>

TitleWidget::TitleWidget(QWidget *parent) : QWidget(parent)
{

}

void TitleWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        m_offset = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void TitleWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_offset);
        event->accept();
    }
}

void TitleWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
