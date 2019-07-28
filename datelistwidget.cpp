#include "datelistwidget.h"

#include <QListView>

#include <QHBoxLayout>
#include <QListWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QDebug>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QDate>

#include <QPropertyAnimation>
#include <QPoint>
#include "dateList/datewidget.h"
#include "date/calendarwidget.h"

DateListWidget::DateListWidget(QWidget *parent) : QWidget(parent)
{
    m_dateCount = 9;

    m_dateVisibleNum = m_dateCount/3;

    m_dateWidgetWidth = 150;
    m_dateWidgetHeight = 50;

    m_aniDuration = 500;


    initUi();
    initConnections();
}

void DateListWidget::initUi()
{
    m_btnGroup = new QButtonGroup(this);

    QHBoxLayout * layout = new QHBoxLayout;
    this->setLayout(layout);

    m_area = new QScrollArea;
    m_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_area->setContentsMargins(0,0,0,0);

    m_scrolWidget = new QWidget;
    m_scrolWidget->setObjectName("weeklist");
    m_scrolLayout = new QHBoxLayout;

    m_scrolLayout->setSpacing(0);
    m_scrolLayout->setContentsMargins(0,0,0,0);
    m_scrolWidget->setContentsMargins(0,0,0,0);

    m_area->setWidget(m_scrolWidget);

    m_scrolWidget->setLayout(m_scrolLayout);
    m_scrolWidget->setLayout(m_scrolLayout);

    m_left = new QPushButton("Left");
    m_left->setFixedWidth(40);
    m_right = new QPushButton("Right");
    m_right->setFixedWidth(40);

    m_dateLabel = new QLabel;
    m_dateLabel->setFixedWidth(150);
    m_subCtrl = new QPushButton;
    m_subCtrl->setFixedWidth(40);

    layout->addStretch();
    layout->addWidget(m_dateLabel);
    layout->addWidget(m_subCtrl);
    layout->addWidget(m_left);
    layout->addWidget(m_area);
    layout->addWidget(m_right);
    layout->addStretch();

    layout->setSpacing(0);

    for(int i =0; i<m_dateCount; i++)
    {
        DateWidget * w = new DateWidget(m_scrolWidget);
        w->setFixedHeight(m_dateWidgetHeight);
        w->setFixedWidth(m_dateWidgetWidth);

        m_dateWidgets.append(w);
        m_scrolLayout->addWidget(w);

        m_btnGroup->addButton(w);
    }

    m_scrolLayout->setSizeConstraint(QLayout::SetFixedSize);
    m_area->setFixedWidth(m_dateVisibleNum*m_dateWidgetWidth);
    m_area->setFixedHeight(m_dateWidgetHeight);

    m_popupWidget = new CalendarWidget(this);
    m_popupWidget->setObjectName("calendarWidget");

//    m_popupWidget->setStyleSheet("QWidget{\
//                                 border-image:url(:/res/calendar_bg.png) 5 15 5 5;\
//                                 border-top: 15px transparent;\
//                                 border-bottom: 5px transparent;\
//                                 border-right: 5px transparent;\
//                                 border-left: 5px transparent;\
//                             }");
}

void DateListWidget::initConnections()
{
    m_dateLabel->setText(QDate::currentDate().toString());

    bool checked = connect(m_popupWidget,&CalendarWidget::sigSelectedDate,[=](const QDate& date){
        m_dateLabel->setText(date.toString());
    });

    checked = connect(m_subCtrl,&QPushButton::clicked,[=](){
        m_popupWidget->show();
        QRect rect = m_subCtrl->rect();
        int width = m_popupWidget->width();

        QPoint pos1 = m_subCtrl->pos() + QPoint(rect.width()/2,rect.height());

        QPoint offset = QPoint(-1*width/2, 0);

        QPoint pos = this->mapToGlobal(pos1 + offset);
        m_popupWidget->move(pos);
    });

    connect(m_left,&QPushButton::clicked,this,&DateListWidget::onLeftClick);
    connect(m_right,&QPushButton::clicked,this,&DateListWidget::onRightClick);
}

void DateListWidget::updateScrollArea()
{
    m_area->horizontalScrollBar()->setValue(m_dateVisibleNum*m_dateWidgetWidth);
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
    for(int i=0; i<m_dateVisibleNum; i++)
    {
        int count = m_scrolLayout->layout()->count();
        QLayoutItem *child = m_scrolLayout->takeAt(count-1);

        DateWidget *tt1 = qobject_cast<DateWidget *>(child->widget());
        m_dateWidgets.removeOne(tt1);
        m_btnGroup->removeButton(tt1);
        tt1->deleteLater();

        delete child;


        DateWidget * w = new DateWidget(m_scrolWidget);
        w->setFixedHeight(m_dateWidgetHeight);
        w->setFixedWidth(m_dateWidgetWidth);

        m_scrolLayout->insertWidget(0,w);
        m_dateWidgets.insert(0,w);
        m_btnGroup->addButton(w);
    }

    updateScrollArea();

//    printLayoutWidgetsInfo();
}

void DateListWidget::updateWidget_back()
{
    for(int i=0; i<m_dateVisibleNum; i++)
    {
        QLayoutItem *child = m_scrolLayout->takeAt(0);

        DateWidget *tt1 = qobject_cast<DateWidget *>(child->widget());
        m_dateWidgets.removeOne(tt1);
        m_btnGroup->removeButton(tt1);
        tt1->deleteLater();

        delete child;

        DateWidget * w = new DateWidget(m_scrolWidget);
        w->setFixedHeight(m_dateWidgetHeight);
        w->setFixedWidth(m_dateWidgetWidth);
        m_scrolLayout->addWidget(w);
        m_dateWidgets.append(w);
        m_btnGroup->addButton(w);
    }
    updateScrollArea();

//    printLayoutWidgetsInfo();
}


void DateListWidget::printLayoutWidgetsInfo()
{

    qDebug()<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
    for (int cc = m_scrolLayout->layout()->count()-1; cc >= 0; --cc)
    {
        QLayoutItem *it = m_scrolLayout->layout()->itemAt(cc);
        DateWidget *orderHistory = qobject_cast<DateWidget *>(it->widget());
        if (orderHistory != 0)
        {
            qDebug()<<orderHistory->text();
        }
    }
    qDebug()<<"=============================================================";

    for (int cc = m_dateWidgets.count()-1; cc >= 0; --cc)
    {
        DateWidget *orderHistory = m_dateWidgets.at(cc);
        if (orderHistory != 0)
        {
            qDebug()<<orderHistory->text();
        }
    }
    qDebug()<<"=============================================================";
    for (int cc = m_btnGroup->buttons().count()-1; cc >= 0; --cc)
    {
        DateWidget *orderHistory = qobject_cast<DateWidget*>(m_btnGroup->buttons().at(cc));
        if (orderHistory != 0)
        {
            qDebug()<<orderHistory->text();
        }
    }
    qDebug()<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
}



