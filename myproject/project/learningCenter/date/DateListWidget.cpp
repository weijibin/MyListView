#include "DateListWidget.h"

#include <QListView>

#include <QHBoxLayout>
#include <QVBoxLayout>
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
#include <QPainter>
#include <QGraphicsDropShadowEffect>

#include "date/DateWidget.h"
#include "date/CalendarWidget.h"
#include "date/CalendarButton.h"
#include "dataCenter/DataProvider.h"


DateListWidget::DateListWidget(QWidget *parent) : QWidget(parent)
{
    m_dateCount = 21;

    m_dateVisibleNum = m_dateCount/3;

    m_dateWidgetWidth = 158;
    m_dateWidgetHeight = 88;

    m_aniDuration = 1000;

    m_dateFormat = QString::fromLocal8Bit("yyyy年M月");

    initUi();
    initConnections();
}

void DateListWidget::initUi()
{
    m_btnGroup = new QButtonGroup(this);

    QHBoxLayout * layout = new QHBoxLayout;
    layout->setContentsMargins(0,0,0,1);
    this->setLayout(layout);

    m_area = new QScrollArea(this);
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

    m_left = new QPushButton();
    m_left->setObjectName("d_left");
    m_left->setFixedSize(24,24);
    m_right = new QPushButton();
    m_right->setObjectName("d_right");
    m_right->setFixedSize(24,24);

    m_today = new QPushButton(QStringLiteral("今天"));
    m_today->setObjectName("dToday");
    m_today->setFixedSize(64,24);


    m_dateBtn = new CalendarButton(this);
    m_dateBtn->setText(QStringLiteral("今天"));
    m_dateBtn->setFixedSize(90,20);

    QVBoxLayout * vBLayout = new QVBoxLayout;
    vBLayout->setContentsMargins(0,0,0,0);
    QHBoxLayout* h1Layout = new QHBoxLayout;
    vBLayout->setContentsMargins(0,0,0,0);
    QHBoxLayout* h2Layout = new QHBoxLayout;
    vBLayout->setContentsMargins(0,0,0,0);

    h1Layout->addSpacing(50);
    h1Layout->addWidget(m_dateBtn);
    h1Layout->addSpacing(40);

    h2Layout->addSpacing(32);
    h2Layout->addWidget(m_left);
    h2Layout->addSpacing(8);
    h2Layout->addWidget(m_today);
    h2Layout->addSpacing(8);
    h2Layout->addWidget(m_right);
    h2Layout->addSpacing(20);



    vBLayout->addLayout(h1Layout);
    vBLayout->addLayout(h2Layout);


    layout->addStretch();
    layout->addLayout(vBLayout);
    layout->addWidget(m_area);
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

    m_scrolWidget->setFixedWidth(m_dateCount*m_dateWidgetWidth);

    m_popupWidget = new CalendarWidget(this);
    m_popupWidget->setObjectName("calendarWidget");
}

void DateListWidget::initConnections()
{
    m_dateBtn->setDisplyText(QDate::currentDate().toString(m_dateFormat));

    bool checked = connect(m_popupWidget,&CalendarWidget::sigSelectedDate,[=](const QDate& date){
        m_dateBtn->setDisplyText(date.toString(m_dateFormat));
        emit sigSelectedDate(date);

        updateWeekListByDate(date);
    });

    checked = connect(m_dateBtn,&QPushButton::clicked,[=](){

        bool ret = m_popupWidget->requestDataBeforeShow();  //显示之前请求数据

        if(ret) {
            m_popupWidget->show();
            QRect rect = m_dateBtn->rect();
            int width = m_popupWidget->width();
            QPoint pos1 = m_dateBtn->pos() + QPoint(rect.width()/2,rect.height());
            QPoint offset = QPoint(-1*width/2+120, 0);
            QPoint pos = this->mapToGlobal(pos1 + offset);
            m_popupWidget->move(pos);
        }
    });

    connect(m_btnGroup,static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
            [=](QAbstractButton * btn){
                DateWidget *w = qobject_cast<DateWidget*>(btn);
                m_popupWidget->setCalendarDate(w->getDateInfo().date);
                m_dateBtn->setDisplyText(w->getDateInfo().date.toString(m_dateFormat));
                emit sigSelectedDate(w->getDateInfo().date);
           });

    connect(m_left,&QPushButton::clicked,this,&DateListWidget::onLeftClick);
    connect(m_right,&QPushButton::clicked,this,&DateListWidget::onRightClick);
    connect(m_today,&QPushButton::clicked,[=](){

        m_dateBtn->setDisplyText(QDate::currentDate().toString(m_dateFormat));
        emit sigSelectedDate(QDate::currentDate());
        m_popupWidget->setCalendarDate(QDate::currentDate());
        updateWeekListByDate(QDate::currentDate());
    });

}

void DateListWidget::refreshByDate(const QDate &date)
{
    qDebug()<<"DateListWidget::refreshByDate== start";
    m_dateBtn->setDisplyText(date.toString(m_dateFormat));

    //=========================================
    //update calendar widget

    m_popupWidget->setCalendarDate(date);
    //=========================================

    // 刷新日期列表
    updateWeekListByDate(date);

    qDebug()<<"DateListWidget::refreshByDate== end";
//    //通知外部选中哪一天
//    emit sigSelectedDate(date);
}

void DateListWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);


    p.save();
    QPen pen;
    pen.setColor(QColor("#F5F5F5"));
    pen.setWidth(2);
    p.setPen(pen);
    p.drawLine(rect().bottomRight(),rect().bottomLeft());
    p.restore();
}


void DateListWidget::updateScrollArea()
{
//    qDebug()<<m_area->horizontalScrollBar()->maximum();
//    qDebug()<<m_area->horizontalScrollBar()->minimum();
//    qDebug()<<m_dateVisibleNum*m_dateWidgetWidth;
//    qDebug()<<m_area->widget()->size();

    m_area->horizontalScrollBar()->setValue(m_dateVisibleNum*m_dateWidgetWidth);

}

void DateListWidget::onLeftClick()
{
    //====================================
    //request data

    QDate endDate = m_dateWidgets.at(7)->getDateInfo().date.addDays(-1);
    QDate startDate = endDate.addDays(-6);
    qDebug()<<"request pre "<<"from: "<<startDate<<" to: "<<endDate;

    DataProvider::GetInstance().requestClassNumInPeriod(startDate,endDate,m_curDateInfos);

    for(int i =0; i<7; i++)
    {
        m_dateWidgets.at(i)->setDateInfo(m_curDateInfos.at(i));
    }
    //====================================

    int startValue = m_area->horizontalScrollBar()->value();
    int endValue = startValue-m_dateVisibleNum*m_dateWidgetWidth;

    if(m_animation == nullptr) {
        m_animation = new QPropertyAnimation(m_area->horizontalScrollBar(),"value",this);
        m_animation->setDuration(m_aniDuration);
        m_animation->setStartValue(startValue);
        m_animation->setEndValue(endValue);
        m_animation->start();
        connect(m_animation,&QPropertyAnimation::finished,this,&DateListWidget::updateWidget_pre);
    }
}

void DateListWidget::onRightClick()
{
    //====================================
    //request data
    QDate startDate = m_dateWidgets.at(13)->getDateInfo().date.addDays(1);
    QDate endDate = startDate.addDays(6);
    qDebug()<<"request week "<<"from: "<<startDate<<" to: "<<endDate;
    DataProvider::GetInstance().requestClassNumInPeriod(startDate,endDate,m_curDateInfos);
    for(int i =0; i<7; i++)
    {
        m_dateWidgets.at(14+i)->setDateInfo(m_curDateInfos.at(i));
    }
    //====================================

    int startValue = m_area->horizontalScrollBar()->value();
    int endValue = startValue+m_dateVisibleNum*m_dateWidgetWidth;

    if(m_animation == nullptr) {
//        qDebug()<<"=====DateListWidget::onRightClick()========";
        m_animation = new QPropertyAnimation(m_area->horizontalScrollBar(),"value",this);
        m_animation->setDuration(m_aniDuration);
        m_animation->setStartValue(startValue);
        m_animation->setEndValue(endValue);
        m_animation->start(QAbstractAnimation::DeleteWhenStopped);
        connect(m_animation,&QPropertyAnimation::finished,this,&DateListWidget::updateWidget_back);
    }

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

    if(m_animation != nullptr){
        delete m_animation;
        m_animation = nullptr;
    }
//    printLayoutWidgetsInfo();
    QDate date = m_popupWidget->getCalendarDate();
    updateWeekSelected(date);
}

void DateListWidget::updateWidget_back()
{
//    qDebug()<<"DateListWidget::updateWidget_back()";
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

    if(m_animation != nullptr){
        delete m_animation;
        m_animation = nullptr;
    }
//    printLayoutWidgetsInfo();
    QDate date = m_popupWidget->getCalendarDate();
    updateWeekSelected(date);
}


void DateListWidget::setCalendarDate(const QDate &date)
{
    m_popupWidget->setCalendarDate(date);
}

QDate DateListWidget::getCalendarDate()
{
    return m_popupWidget->getCalendarDate();
}

void DateListWidget::updateWeekListByDate(const QDate &date)
{
    qDebug()<<"====DateListWidget::updateWeek===date";

    if((m_curDateInfos.count()<1)||
            (date > m_curDateInfos.last().date)|| (date < m_curDateInfos.first().date) )
    {
        //====================================
        //request data
        int index = date.dayOfWeek();
        QDate startDate = date.addDays(-1*index + 1);
        QDate endDate = startDate.addDays(6);
        qDebug()<<"request weekData "<<"from: "<<startDate<<" to: "<<endDate;
        DataProvider::GetInstance().requestClassNumInPeriod(startDate,endDate,m_curDateInfos);

        //====================================
    }
    //new data
    for(int i = 0; i<7; i++)
    {
        m_dateWidgets.at(i+7)->setDateInfo(m_curDateInfos.at(i));
    }

    updateWeekSelected(date);
}

void DateListWidget::updateWeekSelected(const QDate &date)
{
    qDebug()<<"====DateListWidget::updateWeekSelected"<<date;
    if(date.isValid()){
        for(int i = 0; i < m_dateWidgets.count(); i++)
        {
            if(m_dateWidgets.at(i)->getDateInfo().date == date)
            {
                m_dateWidgets.at(i)->setChecked(true);
            }
        }
    } else {
        qDebug()<<"updateWeekSelected error";
    }
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



