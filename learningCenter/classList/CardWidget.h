#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>

class CardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardWidget(QWidget *parent = 0);

signals:

public slots:
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
private:
    void initUi();
    int m_num;
};

#endif // CARDWIDGET_H
