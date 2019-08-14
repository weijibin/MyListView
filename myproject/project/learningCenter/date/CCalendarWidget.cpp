#include "CCalendarWidget.h"
#include <QPainter>
#include <QString>
#include <QBrush>
#include <QRect>

CCalendarWidget::CCalendarWidget(QWidget *parent) : QCalendarWidget(parent)
{

}

void CCalendarWidget::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    if(date == QDate::currentDate()) {
        QCalendarWidget::paintCell(painter,rect,date);
        painter->drawText(rect,QStringLiteral("今"));
        painter->drawLine(rect.left(),rect.center().y(),rect.right(),rect.center().y());
    } else {
        QCalendarWidget::paintCell(painter,rect,date);
    }

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing,true);
    QRect rectangle(rect.bottomLeft()+QPoint(13,-5),QSize(4,4));
    QPen pen;
    pen.setBrush(QBrush(Qt::red));
    pen.setStyle(Qt::NoPen);
    painter->setPen(pen);
//    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::red));
    painter->drawEllipse(rectangle);
    painter->restore();
}
