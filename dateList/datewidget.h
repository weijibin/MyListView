#ifndef DATEWIDGET_H
#define DATEWIDGET_H

#include <QPushButton>

class DateWidget : public QPushButton
{
    Q_OBJECT

public:
    explicit DateWidget(QWidget *parent = 0);
    ~DateWidget();
protected:
    virtual void paintEvent(QPaintEvent *e) override;
};

#endif // DATEWIDGET_H
