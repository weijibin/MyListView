#include "datelistwidget.h"

#include <QListView>

#include <QHBoxLayout>
#include <QListWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QDebug>
#include <QPushButton>

#include <QPropertyAnimation>
#include "dateList/datewidget.h"

DateListWidget::DateListWidget(QWidget *parent) : QWidget(parent)
{
//    initUi();

    m_dateCount = 21;

    m_dateVisibleNum = m_dateCount/3;

    m_dateWidgetWidth = 150;
    m_dateWidgetHeight = 50;

    m_aniDuration = 800;

    initUi();
}

void DateListWidget::initUi()
{
    QHBoxLayout * layout = new QHBoxLayout;
    this->setLayout(layout);

    m_area = new QScrollArea;
    m_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_area->setContentsMargins(0,0,0,0);

    m_scrolWidget = new QWidget;
    m_scrolLayout = new QHBoxLayout;

    m_scrolLayout->setSpacing(0);
    m_scrolLayout->setContentsMargins(0,0,0,0);
    m_scrolWidget->setContentsMargins(0,0,0,0);

    m_area->setWidget(m_scrolWidget);

    m_scrolWidget->setLayout(m_scrolLayout);
    m_scrolWidget->setLayout(m_scrolLayout);

    m_left = new QPushButton("Left");
    m_left->setFixedWidth(40);
    connect(m_left,&QPushButton::clicked,this,&DateListWidget::onLeftClick);
    m_right = new QPushButton("Right");
    m_right->setFixedWidth(40);
    connect(m_right,&QPushButton::clicked,this,&DateListWidget::onRightClick);

    layout->addWidget(m_left);
    layout->addWidget(m_area);
    layout->addWidget(m_right);

    for(int i =0; i<m_dateCount; i++)
    {
        DateWidget * w = new DateWidget(m_scrolWidget);
        w->setFixedHeight(m_dateWidgetHeight);
        w->setFixedWidth(m_dateWidgetWidth);

        m_dateWidgets.append(w);
        m_scrolLayout->addWidget(w);
    }

    m_scrolLayout->setSizeConstraint(QLayout::SetFixedSize);
    m_area->setFixedWidth(m_dateVisibleNum*m_dateWidgetWidth);

}


void DateListWidget::updateScrollArea()
{
    qDebug()<<m_area->horizontalScrollBar()->value();
    m_area->horizontalScrollBar()->setValue(m_dateVisibleNum*m_dateWidgetWidth);
    qDebug()<<m_area->horizontalScrollBar()->value();
}

void DateListWidget::onLeftClick()
{
    int startValue = m_area->horizontalScrollBar()->value();
    int endValue = startValue-m_dateVisibleNum*m_dateWidgetWidth;
    QPropertyAnimation *  animation = new QPropertyAnimation(m_area->horizontalScrollBar(),"value");
    animation->setDuration(m_aniDuration);
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation,&QPropertyAnimation::finished,this,&DateListWidget::updateWidget_pre);
}

void DateListWidget::onRightClick()
{
    int startValue = m_area->horizontalScrollBar()->value();
    int endValue = startValue+m_dateVisibleNum*m_dateWidgetWidth;

    QPropertyAnimation *  animation = new QPropertyAnimation(m_area->horizontalScrollBar(),"value");
    animation->setDuration(m_aniDuration);
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation,&QPropertyAnimation::finished,this,&DateListWidget::updateWidget_back);
}



void DateListWidget::updateWidget_pre()
{
    int value = m_area->horizontalScrollBar()->value();

    for(int i=0; i<m_dateVisibleNum; i++)
    {
        int count = m_scrolLayout->layout()->count();
        QLayoutItem *child = m_scrolLayout->takeAt(count-1);

        DateWidget *tt1 = qobject_cast<DateWidget *>(child->widget());

        m_dateWidgets.removeOne(tt1);

        tt1->deleteLater();

        delete child;


        DateWidget * w = new DateWidget(m_scrolWidget);
        w->setFixedHeight(m_dateWidgetHeight);
        w->setFixedWidth(m_dateWidgetWidth);

        m_scrolLayout->insertWidget(0,w);
        m_dateWidgets.insert(0,w);

//        m_area->horizontalScrollBar()->setValue(value += m_dateWidgetWidth);
    }

    updateScrollArea();
}

void DateListWidget::updateWidget_back()
{
    qDebug()<<"Before====="<<m_area->horizontalScrollBar()->value();
    int value = m_area->horizontalScrollBar()->value();
    for(int i=0; i<m_dateVisibleNum; i++)
    {
        QLayoutItem *child = m_scrolLayout->takeAt(0);

        DateWidget *tt1 = qobject_cast<DateWidget *>(child->widget());
        m_dateWidgets.removeOne(tt1);
        tt1->deleteLater();

        delete child;

        DateWidget * w = new DateWidget(m_scrolWidget);
        w->setFixedHeight(m_dateWidgetHeight);
        w->setFixedWidth(m_dateWidgetWidth);
        m_scrolLayout->addWidget(w);
        m_dateWidgets.append(w);


//        m_area->horizontalScrollBar()->setValue(value -= m_dateWidgetWidth);

    }

    updateScrollArea();
    qDebug()<<"After====="<<m_area->horizontalScrollBar()->value();
}


void DateListWidget::printLayoutWidgets()
{

    qDebug()<<"=============================================================";
    for (int cc = m_scrolLayout->layout()->count()-1; cc >= 0; --cc)
    {
        QLayoutItem *it = m_scrolLayout->layout()->itemAt(cc);
        DateWidget *orderHistory = qobject_cast<DateWidget *>(it->widget());
        if (orderHistory != 0)
        {
            qDebug()<<orderHistory->text();
            qDebug()<<orderHistory;
        }
    }
    qDebug()<<"=============================================================";
}



