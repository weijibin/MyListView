#ifndef DATEWIDGET_H
#define DATEWIDGET_H

#include <QPushButton>
#include <QDate>
#include <QColor>
#include <QFont>
#include <QMap>

#include "common/common.h"

class DateWidget : public QPushButton
{
    Q_OBJECT

public:
    explicit DateWidget(QWidget *parent = 0);
    ~DateWidget();

    void setDateInfo(const DateInfo& info);
    const DateInfo & getDateInfo();
protected:
    virtual void paintEvent(QPaintEvent *e) override;

private:
    void updateInfo();
private:
    DateInfo m_info;
    QString m_color;
    QString m_color_info;
    QString m_color_checked;

    QFont m_font;
    QFont m_font_info;

    static QMap<int,QString> m_dayOfWeek;

    QString m_dateNum;
    QRect m_rect_num;
    QString m_dateOfWeek;
    QRect m_rect_week;
    QString m_courseInfo;
    QRect m_rect_info;

    QRect m_rect_point;
};

#endif // DATEWIDGET_H
