#include "CardListWidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QPushButton>
#include <QEvent>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QScrollBar>
#include <QDebug>

#include <QTimer>

#include "CardWidget.h"

CardListWidget::CardListWidget(QWidget *parent) : QWidget(parent)
{
    m_cardTotalCount = 6;

    m_cardVisibleNum = 2;

    m_cardWidth = 600;
    m_cardHeight = 500;

    m_aniDuration = 2000;

    initUi();

    QTimer::singleShot(5000,[=](){
        onLeftClick();
    });

    QTimer::singleShot(100,[=](){
       updateScrollArea();
    });
}

void CardListWidget::initUi()
{
    setContentsMargins(0,0,0,0);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,10);
    layout->setSpacing(0);

    m_area = new QScrollArea(this);
//    m_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
    m_cardWidth = w/2;
    m_cardHeight = h-2;

    for(int i =0; i< m_cardList.size(); i++)
    {
        m_cardList.at(i)->setFixedSize(m_cardWidth,m_cardHeight);
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



void CardListWidget::updateScrollArea()
{
    m_area->horizontalScrollBar()->setValue(m_cardVisibleNum*m_cardWidth);
}

void CardListWidget::onLeftClick()
{
    int startValue = m_area->horizontalScrollBar()->value();
    int endValue = startValue-m_cardVisibleNum*m_cardWidth;
    QPropertyAnimation *  animation = new QPropertyAnimation(m_area->horizontalScrollBar(),"value");
    animation->setDuration(m_aniDuration);
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation,&QPropertyAnimation::finished,this,&CardListWidget::updateWidget_pre);
}

void CardListWidget::onRightClick()
{
    int startValue = m_area->horizontalScrollBar()->value();
    int endValue = startValue+m_cardVisibleNum*m_cardWidth;

    QPropertyAnimation *  animation = new QPropertyAnimation(m_area->horizontalScrollBar(),"value");
    animation->setDuration(m_aniDuration);
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation,&QPropertyAnimation::finished,this,&CardListWidget::updateWidget_back);
}


void CardListWidget::updateWidget_pre()
{
    for(int i=0; i<m_cardVisibleNum; i++)
    {
        int count = m_scrolLayout->layout()->count();
        QLayoutItem *child = m_scrolLayout->takeAt(count-1);

        CardWidget *tt1 = qobject_cast<CardWidget *>(child->widget());
        m_cardList.removeOne(tt1);
        tt1->deleteLater();

        delete child;


        CardWidget * w = new CardWidget(m_scrolWidget);
        w->setFixedHeight(m_cardHeight);
        w->setFixedWidth(m_cardWidth);



        m_scrolLayout->insertWidget(0,w);
        m_cardList.insert(0,w);
    }

    updateScrollArea();
}

void CardListWidget::updateWidget_back()
{
    for(int i=0; i<m_cardVisibleNum; i++)
    {
        QLayoutItem *child = m_scrolLayout->takeAt(0);

        CardWidget *tt1 = qobject_cast<CardWidget *>(child->widget());
        m_cardList.removeOne(tt1);
        tt1->deleteLater();

        delete child;

        CardWidget * w = new CardWidget(m_scrolWidget);
        w->setFixedHeight(m_cardHeight);
        w->setFixedWidth(m_cardWidth);


        m_scrolLayout->addWidget(w);
        m_cardList.append(w);
    }
    updateScrollArea();
}
