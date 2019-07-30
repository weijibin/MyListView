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
private:
    void initUi();
};

#endif // CARDWIDGET_H
