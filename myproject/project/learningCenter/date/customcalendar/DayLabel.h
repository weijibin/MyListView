#ifndef DAYLABEL_H
#define DAYLABEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDate>

class DayLabel : public QPushButton
{
    Q_OBJECT

public:
    explicit DayLabel(QWidget *parent = 0);

    QDate getDate() const {return m_date;}
    void setDate(const QDate&date);
    void clearText();

    void setIsHaveCourse(bool is);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    QDate m_date;
    bool m_isHaveCourse = false;
    QRect m_rect_point;
};

#endif // DAYLABEL_H
