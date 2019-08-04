#ifndef CCALENDARWIDGET_H
#define CCALENDARWIDGET_H
#include <QCalendarWidget>
#include <QWidget>

class CCalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    CCalendarWidget(QWidget* parent = nullptr);

protected:
    virtual void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const override;
};

#endif // CCALENDARWIDGET_H
