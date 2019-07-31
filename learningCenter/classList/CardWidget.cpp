#include "CardWidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

CardWidget::CardWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);

    static int num = 0;
    num++;
    m_num = num;
    initUi();
}

void CardWidget::initUi()
{

}

void CardWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    //test
    p.drawText(100,100,QString("num::%1").arg(m_num));
}

void CardWidget::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug()<<"CardWidget::mouseMoveEvent====="<<event->pos();
    QWidget::mouseMoveEvent(event);
//    event->ignore();
}
