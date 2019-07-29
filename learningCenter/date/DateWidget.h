#ifndef DATEWIDGET_H
#define DATEWIDGET_H

#include <QPushButton>
#include <QDate>

class DateWidget : public QPushButton
{
    Q_OBJECT

public:
    explicit DateWidget(QWidget *parent = 0);
    ~DateWidget();

    void setDate(const QDate& date);
    const QDate& getDate();
protected:
    virtual void paintEvent(QPaintEvent *e) override;

private:
    QDate m_date;
};

#endif // DATEWIDGET_H
