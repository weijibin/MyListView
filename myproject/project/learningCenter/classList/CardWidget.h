#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include "classcard/ClassCardWidget.h"

class CardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardWidget(QWidget *parent = 0);

    ClassCardWidget * getClassCard(){return m_card;}

signals:

public slots:
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    void initUi();
private:
    ClassCardWidget *m_card = nullptr;
};

#endif // CARDWIDGET_H
