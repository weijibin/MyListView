#include "ClassListWidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QResizeEvent>
#include <QDebug>
#include "date/DateListWidget.h"
#include "classList/CardListWidget.h"

ClassListWidget::ClassListWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    initUi();
}

void ClassListWidget::initUi()
{
    setContentsMargins(0,0,0,0);
    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);


    m_dateListWidget = new DateListWidget(this);
    m_dateListWidget->setFixedHeight(88);


    m_cardList = new CardListWidget(this);

    layout->addWidget(m_dateListWidget);

//    layout->addWidget(m_cardList);

    //=======================================
    m_initCardListSize.setWidth(1280);
    m_initCardListSize.setHeight(576);

    m_cardListMaxSize.setWidth(m_initCardListSize.width()*3/2);
    m_cardListMaxSize.setHeight(m_initCardListSize.height()*3/2);

    m_cardList->setFixedSize(m_initCardListSize);

    QVBoxLayout *cardSLayout = new QVBoxLayout;
    cardSLayout->setContentsMargins(0,0,0,0);

    QHBoxLayout * card_bodyLayout = new QHBoxLayout;
    card_bodyLayout->setContentsMargins(0,0,0,0);
    card_bodyLayout->addStretch();
    card_bodyLayout->addWidget(m_cardList);
    card_bodyLayout->addStretch();

    cardSLayout->addStretch();
    cardSLayout->addLayout(card_bodyLayout);
    cardSLayout->addStretch();

    layout->addLayout(cardSLayout);
    //=====================================


    layout->setSpacing(0);

    setLayout(layout);

    //
    QTimer::singleShot(100,[=](){
       m_dateListWidget->updateScrollArea();
    });
}

void ClassListWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    {
        QResizeEvent *reEvt = static_cast<QResizeEvent*>(event);

        if(m_cardList != nullptr){
            m_cardList->setFixedSize(getCardListSize(reEvt->size()-QSize(0,88)));
        }

    }
}

QSize ClassListWidget::getCardListSize(const QSize &size)
{
    QSize sizet;
    float ratio1 = float(m_initCardListSize.width())/float(m_initCardListSize.height());
    float ratio2 = float(size.width())/float(size.height());

    if(ratio1 > ratio2)
    {
        sizet.setWidth(size.width());
        sizet.setHeight(size.width()/ratio1);
    }
    else
    {
        sizet.setWidth(size.height() * ratio1);
        sizet.setHeight(size.height());
    }

    if(sizet.width() < m_initCardListSize.width())
        sizet = m_initCardListSize;
    if(sizet.width() > m_cardListMaxSize.width())
    {
        sizet = m_cardListMaxSize;
    }
    return sizet;
}
