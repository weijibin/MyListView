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
#include "common/common.h"
#include "dataCenter/DataProvider.h"

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
        CardWidget * w = new CardWidget(m_scrolWidget);

        w->getClassCard()->installEventFilter(this);

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

void CardListWidget::updateLeftAndRightVisible()
{
    if(m_cardList.at(3)->getType() == 2)
    {
        m_rightBtn->setVisible(false);
    }
    if(m_cardList.at(1)->getType() == 2)
    {
        m_leftBtn->setVisible(false);
    }
}

void CardListWidget::initConnections()
{
    connect(m_leftBtn,&QPushButton::clicked,this,&CardListWidget::onLeftClick);
    connect(m_rightBtn,&QPushButton::clicked,this,&CardListWidget::onRightClick);
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
            if(m_cardList.at(m_cardTotalCount/2-1)->getType() == 2)
                m_leftBtn->setVisible(false);
            else
                m_leftBtn->setVisible(true);
        } else if((m_cardList.at(m_cardTotalCount/2+1)->getClassCard()) == obj){
            if(m_cardList.at(m_cardTotalCount/2+1)->getType() == 2)
                m_rightBtn->setVisible(false);
            else
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
    //=========================================
    int nextCenterIndex = m_cardCurIndex-1;
    m_requestLeftDataNum = 0;
    if((nextCenterIndex-2) < 0)
    {
        qDebug()<<"CardListWidget::onLeftClick  new Data";
        //request data
        QList<ClassCardInfo> cards;
        ClassCardsPar par;
        int ret = DataProvider::GetInstance().requestClassCard(m_cardInfos.first().time.date.addDays(-1),
                                                               2,cards,par);
//        m_cardCurIndex = par.curIndex;

        m_requestLeftDataNum = cards.count();

        for(int i = 0 ; i< cards.count(); i++)
        {
            m_cardInfos.insert(0,cards.at(i));
        }
    }
    //========================================

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

    //=========================================
    int nextCenterIndex = m_cardCurIndex+1;
    if((nextCenterIndex+2)>(m_cardInfos.count()-1))
    {
        qDebug()<<"CardListWidget::updateWidget_back  new Data";

        //request data
        //request cards data by date
        QList<ClassCardInfo> cards;
        ClassCardsPar par;
        int ret = DataProvider::GetInstance().requestClassCard(m_cardInfos.last().time.date.addDays(1),
                                                               1,cards,par);
//        m_cardCurIndex = par.curIndex;

        for(int i = 0 ; i< cards.count(); i++)
        {
            m_cardInfos.append(cards.at(i));
        }
    }
    //========================================


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

    qDebug()<<"CardListWidget::updateWidget_pre";

    for(int i=0; i<m_cardVisibleNum; i++)
    {
        int count = m_scrolLayout->layout()->count();
        QLayoutItem *child = m_scrolLayout->takeAt(count-1);

        CardWidget *tt1 = qobject_cast<CardWidget *>(child->widget());
        m_cardList.removeOne(tt1);
        tt1->deleteLater();

        delete child;

        //=================================================================

        CardWidget * w = new CardWidget(m_scrolWidget);
        int nextCenterIndex = m_cardCurIndex-1;
        w->getClassCard()->installEventFilter(this);
        w->getClassCard()->setClassInfo(m_cardInfos.at(nextCenterIndex-2 + m_requestLeftDataNum)); //test

        m_cardCurIndex = nextCenterIndex + m_requestLeftDataNum;

        m_requestLeftDataNum = 0;

        //==================================================================

        w->setFixedHeight(m_cardHeight);
        w->setFixedWidth(m_cardWidth);

        m_scrolLayout->insertWidget(0,w);
        m_cardList.insert(0,w);


        updateLeftAndRightVisible();
    }

    updateScrollArea();
    emit sigCurCardDate(m_cardList.at(2)->getClassCard()->getClassInfo().time.date);

    //remove no class card
    removeNoClassCard();

}

void CardListWidget::removeNoClassCard()
{
    if(m_noClassIndex != -1)
    {
        m_cardInfos.removeAt(m_noClassIndex);

        updateUiByCardInfos(m_noClassIndex);

        m_noClassIndex = -1;
    }
}

void CardListWidget::updateUiByCardInfos(int curIndex)
{
    for(int i =0; i<m_cardTotalCount; i++)
    {
        m_cardList.at(i)->getClassCard()->setClassInfo(m_cardInfos.at(curIndex-2 + i ));
    }
    m_cardCurIndex = curIndex;
}

void CardListWidget::updateWidget_back()
{
    qDebug()<<"CardListWidget::updateWidget_back";
    {
        for(int i=0; i<m_cardVisibleNum; i++)
        {
            QLayoutItem *child = m_scrolLayout->takeAt(0);

            CardWidget *tt1 = qobject_cast<CardWidget *>(child->widget());
            m_cardList.removeOne(tt1);
            tt1->deleteLater();

            delete child;


            //=================================================================

            int nextCenterIndex = m_cardCurIndex+1;

            CardWidget * w = new CardWidget(m_scrolWidget);
            w->getClassCard()->installEventFilter(this);
            w->getClassCard()->setClassInfo(m_cardInfos.at(nextCenterIndex+2)); //test
            m_cardCurIndex = nextCenterIndex;
            //==================================================================


            w->setFixedHeight(m_cardHeight);
            w->setFixedWidth(m_cardWidth);


            m_scrolLayout->addWidget(w);
            m_cardList.append(w);

            //================
            updateLeftAndRightVisible();
        }
        updateScrollArea();

        emit sigCurCardDate(m_cardList.at(2)->getClassCard()->getClassInfo().time.date);

        //remove no class card
        removeNoClassCard();
    }
}

void CardListWidget::updateUiByDate(const QDate &date)
{
    qDebug()<<"======CardListWidget::updateUiByDate=====start==="<<date;

    //=================================================
    //request data
    //request cards data by date
    ClassCardsPar par;
    int ret = DataProvider::GetInstance().requestClassCard(date,0,m_cardInfos,par);
    m_cardCurIndex = par.curIndex;
    qDebug()<<m_cardInfos.count();
    qDebug()<<par.curIndex;
    //==================================================

    updateUiByCardInfos(m_cardCurIndex);

    //=============================================================

    qDebug()<<"======CardListWidget::updateUiByDate========end";
}
