#include "datewidget.h"
#include <QPainter>
#include <QDebug>

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

void DateWidget::setDate(const QDate &date)
{
//    qDebug()<<"DateWidget::setDate==="<<date.toString();
    m_date = date;
    setText(date.toString());
}

const QDate& DateWidget::getDate()
{
    return m_date;
}
