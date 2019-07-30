#include "ClassListWidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QResizeEvent>
#include "date/DateListWidget.h"
#include "classList/CardListWidget.h"

ClassListWidget::ClassListWidget(QWidget *parent) : QWidget(parent)
{
    initUi();
}

void ClassListWidget::initUi()
{
    setContentsMargins(0,0,0,0);
    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);


    m_dateListWidget = new DateListWidget(this);
    m_dateListWidget->setFixedHeight(50);


    m_cardList = new CardListWidget(this);

    layout->addWidget(m_dateListWidget);
    layout->addWidget(m_cardList);
//    layout->addStretch();

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
//    if(m_cardList != nullptr)
//    {
//        m_cardList->updateCardBySize(event->size().width(),event->size().height());
//    }
}
