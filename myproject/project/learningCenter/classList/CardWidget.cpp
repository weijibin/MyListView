#include "CardWidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>;

CardWidget::CardWidget(QWidget *parent) : QWidget(parent)
{

    setMouseTracking(true);

    initUi();

    setContentsMargins(0,20,0,10);  //margin1111
}

void CardWidget::initUi()
{
    QVBoxLayout * layout = new QVBoxLayout;

    m_card = new ClassCardWidget;

    ClassCardInfo info;
    info.type = 2;
    m_card->setClassInfo(info);

    layout->addWidget(m_card);
    this->setLayout(layout);
}

int CardWidget::getType()
{
    if(m_card != nullptr)
        return m_card->getClassInfo().type;
    return 2;
}

void CardWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    if(m_card->getClassInfo().type != 2)
    {
        p.save();
        p.setRenderHint(QPainter::Antialiasing, true);

        QRect rect = QRect(m_card->pos(),QSize(m_card->rect().width(),m_card->rect().height()));
        QColor color(92, 93, 95, 50);
        int arr[10] = {80, 50, 40, 30, 20, 10, 5, 5};
        for (int i = 0; i < 5; i++) {
            QRect r1 = rect.adjusted(-1*i,-1*i,1*i,1*i);
            color.setAlpha(arr[i]);
            p.setPen(color);
            p.drawRoundedRect(QRectF(r1),8,8);
        }
        p.restore();
    }
}
