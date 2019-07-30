#include "CardListWidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QPushButton>
#include <QEvent>
#include <QResizeEvent>
#include <QDebug>

#include "CardWidget.h"

CardListWidget::CardListWidget(QWidget *parent) : QWidget(parent)
{
    m_cardTotalCount = 5;

    m_cardVisibleNum = m_cardTotalCount/3;

    m_cardWidth = 600;
    m_cardHeight = 500;

    m_aniDuration = 1000;

    initUi();
}

void CardListWidget::initUi()
{
    setContentsMargins(0,0,0,0);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,10);
    layout->setSpacing(0);

    m_area = new QScrollArea(this);
    m_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_area->setContentsMargins(0,0,0,0);
    m_area->installEventFilter(this);


    m_scrolWidget = new QWidget(m_area);
    m_scrolWidget->setContentsMargins(0,0,0,0);
    m_scrolLayout = new QHBoxLayout(m_area);
    m_scrolLayout->setContentsMargins(0,0,0,0);
    m_scrolLayout->setSpacing(0);
    m_scrolLayout->setSizeConstraint(QLayout::SetFixedSize);

    m_scrolWidget->setLayout(m_scrolLayout);

    m_area->setWidget(m_scrolWidget);

    layout->addWidget(m_area);



    for(int i =0; i<m_cardTotalCount; i++)
    {
        CardWidget * w = new CardWidget(m_scrolWidget);
        m_cardList.append(w);
        m_scrolLayout->addWidget(w);

    }


}

void CardListWidget::updateCardBySize(int w, int h)
{
    int cardW = w/2;
    int cardH = h-2;

    for(int i =0; i< m_cardList.size(); i++)
    {
        m_cardList.at(i)->setFixedSize(cardW,cardH);
    }
}

void CardListWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

//    qDebug()<<">>>>>>>>>>>>>>>>>>>>>>>>";
//    qDebug()<<this->size();
//    qDebug()<<m_scrolWidget->size();
//    qDebug()<<m_area->viewport()->size();
//    qDebug()<<m_area->widgetResizable();
//    qDebug()<<"<<<<<<<<<<<<<<<<<<<<<<<<";
}

bool CardListWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_area) {
        if (event->type() == QEvent::Resize) {
            QResizeEvent *reEvt = static_cast<QResizeEvent*>(event);
            updateCardBySize(reEvt->size().width(),reEvt->size().height());

//            qDebug()<<reEvt->size();
//            qDebug()<<m_area->viewport()->size();
        }
    }
    return QWidget::eventFilter(obj, event);
}
