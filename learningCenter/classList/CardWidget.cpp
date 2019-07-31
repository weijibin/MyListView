#include "CardWidget.h"
#include <QStyleOption>
#include <QPainter>


CardWidget::CardWidget(QWidget *parent) : QWidget(parent)
{
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
