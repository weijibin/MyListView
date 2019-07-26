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
    testDateUi();
}

void DateListWidget::initUi()
{
    m_view = new DateListView();

    QStringList lstStr;
    lstStr.append("monday");
    lstStr.append("tuesday");
    lstStr.append("wednesday");
    lstStr.append("thursday");
    lstStr.append("friday");
    lstStr.append("saturday");
    lstStr.append("sunday");
    m_model = new DateListModel(lstStr,this);
    m_delegate = new DateDelegate(this);

    m_view->setModel(m_model);
    m_view->setItemDelegate(m_delegate);

    m_view->setUniformItemSizes(true);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_view);
    setLayout(layout);


    //======================================================================
    QListWidgetItem *item1 = new QListWidgetItem();
    QListWidgetItem *item2 = new QListWidgetItem();
    QListWidgetItem *item3 = new QListWidgetItem();
    QListWidgetItem *item4 = new QListWidgetItem();
    QListWidgetItem *item5 = new QListWidgetItem(tr("Rectangle3"));
    QListWidgetItem *item6 = new QListWidgetItem(tr("Rectangle3"));
    QListWidgetItem *item7 = new QListWidgetItem(tr("Rectangle3"));
    QListWidget * lst = new QListWidget;
    lst->addItem(item1);
    lst->addItem(item2);
    lst->addItem(item3);
    lst->addItem(item4);
    lst->addItem(item5);
    lst->addItem(item6);
    lst->addItem(item7);

//    lst->setModel(m_model);
//    lst->setIndexWidget();



    DateWidget * w1 = new DateWidget;
    DateWidget * w2 = new DateWidget;
    DateWidget * w3 = new DateWidget;
    DateWidget * w4 = new DateWidget;

    w1->setFixedHeight(50);
    w2->setFixedHeight(50);
    w3->setFixedHeight(50);
    w4->setFixedHeight(50);
    lst->setItemWidget(item1,w1);
    lst->setItemWidget(item2,w2);
    lst->setItemWidget(item3,w3);
    lst->setItemWidget(item4,w4);
    item1->setSizeHint(w1->size());
    item2->setSizeHint(w2->size());
    item3->setSizeHint(w3->size());
    item4->setSizeHint(w4->size());


    for(int i =0; i<300; i++)
    {
        DateWidget * w = new DateWidget;
        w->setFixedHeight(50);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(w->size());
        lst->addItem(item);
        lst->setItemWidget(item,w);
    }

    lst->setFocusPolicy( Qt::NoFocus);

//    lst->setItemWidget(item2,w);
//    lst->setItemWidget(item3,w);
//    lst->setItemWidget(item4,w);
//    lst->setItemWidget(item5,w);

//    lst->setFlow(QListWidget::LeftToRight);
//    lst->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    lst->setUniformItemSizes(true);

    lst->setSelectionMode(QAbstractItemView::NoSelection);

    lst->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);

    lst->setAutoScroll(false);

    layout->addWidget(lst);

    //========================================================

    QScrollArea * m_scrollEvlt = new QScrollArea;
    QWidget* m_scrollWidget = new QWidget;
    QVBoxLayout *layoutScroll = new QVBoxLayout;
    layoutScroll->addWidget(m_scrollWidget);
    m_scrollEvlt->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollEvlt->setWidget(m_scrollWidget);


    QVBoxLayout * scrolLayout = new QVBoxLayout;
    scrolLayout->setContentsMargins(0,0,0,0);
    scrolLayout->setSpacing(0);

    m_scrollWidget->setLayout(scrolLayout);

    for(int i =0; i<300; i++)
    {
        DateWidget * w = new DateWidget;
        qDebug()<<w->parent();
        w->setFixedHeight(50);
        scrolLayout->addWidget(w);

        qDebug()<<w->parent();

        scrolLayout->removeWidget(w);
        qDebug()<<w->parent();
    }

    scrolLayout->addStretch();
    scrolLayout->setSizeConstraint(QLayout::SetFixedSize);


    layout->addWidget(m_scrollEvlt);

    //========================================================================

}


void DateListWidget::testDateUi()
{
    QHBoxLayout * layout = new QHBoxLayout;
    this->setLayout(layout);

    m_area = new QScrollArea;
//    m_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_area->setContentsMargins(0,0,0,0);

    m_scrolWidget = new QWidget;
    m_scrolLayout = new QHBoxLayout;

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

    for(int i =0; i<10; i++)
    {
        DateWidget * w = new DateWidget(m_scrolWidget);
        w->setFixedHeight(50);
        w->setFixedWidth(150);
        m_scrolLayout->addWidget(w);
    }

    m_scrolLayout->setSizeConstraint(QLayout::SetFixedSize);

}


void DateListWidget::onLeftClick()
{
    int startValue = m_area->horizontalScrollBar()->value();
    int endValue = startValue-450;
    QPropertyAnimation *  animation = new QPropertyAnimation(m_area->horizontalScrollBar(),"value");
    animation->setDuration(2000);
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation,&QPropertyAnimation::finished,this,&DateListWidget::updateWidget_pre);

}

void DateListWidget::updateWidget_pre()
{
    int value = m_area->horizontalScrollBar()->value();

    for(int i=0; i<3; i++)
    {
        int count = m_scrolLayout->layout()->count();
        QLayoutItem *child = m_scrolLayout->takeAt(count-1);

        DateWidget *tt1 = qobject_cast<DateWidget *>(child->widget());
        tt1->deleteLater();

        delete child;


        DateWidget * w = new DateWidget(m_scrolWidget);
        w->setFixedHeight(50);
        w->setFixedWidth(150);
        m_scrolLayout->insertWidget(0,w);

        m_area->horizontalScrollBar()->setValue(value += 150);
    }
}

void DateListWidget::updateWidget_back()
{
    qDebug()<<"Before====="<<m_area->horizontalScrollBar()->value();
    int value = m_area->horizontalScrollBar()->value();
    for(int i=0; i<3; i++)
    {
        QLayoutItem *child = m_scrolLayout->takeAt(0);
        DateWidget *tt1 = qobject_cast<DateWidget *>(child->widget());
        tt1->deleteLater();
        delete child;

        DateWidget * w = new DateWidget(m_scrolWidget);
        w->setFixedHeight(50);
        w->setFixedWidth(150);
        m_scrolLayout->addWidget(w);


        m_area->horizontalScrollBar()->setValue(value -= 150);

    }

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

void DateListWidget::onRightClick()
{
    int startValue = m_area->horizontalScrollBar()->value();
    int endValue = startValue+450;

    QPropertyAnimation *  animation = new QPropertyAnimation(m_area->horizontalScrollBar(),"value");
    animation->setDuration(2000);
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animation,&QPropertyAnimation::finished,this,&DateListWidget::updateWidget_back);
}

