#include "datewidget.h"
#include <QPainter>
DateWidget::DateWidget(QWidget *parent) :
    QPushButton(parent)
{
    this->setCheckable(true);
    static int  num = 0;
    setText(QString::number(num++));
}

DateWidget::~DateWidget()
{

}

void DateWidget::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);
}
