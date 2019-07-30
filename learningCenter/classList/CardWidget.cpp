#include "CardWidget.h"
#include <QStyleOption>
#include <QPainter>

CardWidget::CardWidget(QWidget *parent) : QWidget(parent)
{

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

    p.drawEllipse(this->rect());
    p.drawRect(this->rect());
}
