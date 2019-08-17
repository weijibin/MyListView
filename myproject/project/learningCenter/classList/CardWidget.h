#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include "classcard/ClassCardWidget.h"

class CardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardWidget(int type=1 ,QWidget *parent = 0);

    ClassCardWidget * getClassCard(){return m_card;}

    int getType() {return m_type;}

signals:

public slots:
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    void initUi();
private:
    ClassCardWidget *m_card = nullptr;
    int m_type;  //1 课程卡片 , 0 无课的卡片
};

#endif // CARDWIDGET_H
