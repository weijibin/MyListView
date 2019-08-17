#include "CardListWidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QPushButton>
#include <QEvent>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QScrollBar>
#include <QMouseEvent>
#include <QDebug>

#include <QTimer>

#include "CardWidget.h"

CardListWidget::CardListWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);

    m_cardTotalCount = 5;

    m_cardVisibleNum = 1;

    m_cardWidth = 790;
    m_cardHeight = 500;

    m_aniDuration = 500;

    initUi();
    initConnections();

    QTimer::singleShot(100,[=](){
       updateScrollArea();
    });
}

void CardListWidget::initUi()
{
    setContentsMargins(0,0,0,0);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,20);   //margin1111
    layout->setSpacing(0);

    m_area = new QScrollArea(this);
    m_area->setMouseTracking(true);
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
        CardWidget * w = new CardWidget(1,m_scrolWidget);

        w->getClassCard()->installEventFilter(this);
        w->getClassCard()->setClassInfo(getCardInfo(i)); //test

        m_cardList.append(w);
        m_scrolLayout->addWidget(w);
    }



    m_leftBtn = new QPushButton(this);
    m_leftBtn->setObjectName("cardLeft");
    m_rightBtn = new QPushButton(this);
    m_rightBtn->setObjectName("cardRight");

    m_leftBtn->setVisible(false);
    m_rightBtn->setVisible(false);

}

void CardListWidget::updateLeftAndRightBtn()
{
    QPoint posL, posR;

    QSize btnSize;
    btnSize.setWidth(40);
    btnSize.setHeight(80);

    m_leftBtn->setFixedSize(btnSize);
    m_rightBtn->setFixedSize(btnSize);

//    posL.setX(m_cardWidth/3 -m_leftBtn->size().width()/2);
    posL.setX(0);
    posL.setY(m_cardHeight/2 - m_leftBtn->size().height()/2);

    posR.setX(width()-40);
    posR.setY(m_cardHeight/2 - m_rightBtn->size().height()/2);


    m_leftBtn->move(posL);
    m_rightBtn->move(posR);
}

void CardListWidget::initConnections()
{
    connect(m_leftBtn,&QPushButton::clicked,this,&CardListWidget::onLeftClick);
    connect(m_rightBtn,&QPushButton::clicked,this,&CardListWidget::onRightClick);
}

ClassCardInfo CardListWidget::getCardInfo(int type)
{
    ClassTime time;
    time.day = QString::fromLocal8Bit("今日");
    time.startTime = "8:30";
    time.endTime = "18:30";
    time.index = 2;

    ClassCardInfo info;
    info.time = time;

    info.classStatusType = type%3;

    info.classStatus = QString::fromLocal8Bit("直播进行中...");
    info.classTip = QString::fromLocal8Bit("记得去APP完成课清哦~");
    if(info.classStatusType == 1)
        info.btnText = QString::fromLocal8Bit("去上课");
    else
        info.btnText = QString::fromLocal8Bit("看回放");

    info.chapterName = QString::fromLocal8Bit("第一讲 函数奇偶性与对称性");
    info.subjectName = QString::fromLocal8Bit("数学");
    info.courseName = QString::fromLocal8Bit("【2019-暑】六年级初一数学直播菁英班（北京人教）");

    TeacherInfo info_t1;
    info_t1.name = QString::fromLocal8Bit("郭德纲");
    info_t1.type = 1;
    info_t1.imgUrl = ":/res/default_boy_img.png";

    TeacherInfo info_t2;
    info_t2.name = QString::fromLocal8Bit("于谦");
    info_t2.type = 4;
    info_t2.imgUrl = ":/res/default_boy_img.png";

    info.teachers.clear();
    info.teachers.append(info_t1);
    info.teachers.append(info_t2);


    return info;

}

void CardListWidget::updateCardBySize(int w, int h)
{
//    m_cardWidth = w/2;
    m_cardWidth = w/5*3;   // 左右显示1/3 上个卡片的
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

            updateLeftAndRightBtn();

            updateScrollArea();

//            qDebug()<<reEvt->size();
//            qDebug()<<m_area->viewport()->size();
        }
    }


    if(event->type() == QEvent::Enter){

        if(m_cardList.at(m_cardTotalCount/2-1)->getClassCard() == obj){
            m_leftBtn->setVisible(true);
        } else if((m_cardList.at(m_cardTotalCount/2+1)->getClassCard()) == obj){
            m_rightBtn->setVisible(true);
        } else {
            m_leftBtn->setVisible(false);
            m_rightBtn->setVisible(false);
        }
    }

    return QWidget::eventFilter(obj, event);
}


void CardListWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}

void CardListWidget::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
    {
        m_leftBtn->setVisible(false);
        m_rightBtn->setVisible(false);
    }
}

void CardListWidget::updateScrollArea()
{
    float value = m_cardVisibleNum+float(0.6666);
    m_area->horizontalScrollBar()->setValue(value*m_cardWidth);
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


        CardWidget * w = new CardWidget(1,m_scrolWidget);
        w->getClassCard()->installEventFilter(this);

        w->getClassCard()->setClassInfo(getCardInfo(count%3)); //test

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

        CardWidget * w = new CardWidget(0,m_scrolWidget);
        w->getClassCard()->installEventFilter(this);

        w->getClassCard()->setClassInfo(getCardInfo(i)); //test

        w->setFixedHeight(m_cardHeight);
        w->setFixedWidth(m_cardWidth);


        m_scrolLayout->addWidget(w);
        m_cardList.append(w);
    }
    updateScrollArea();
}
