#include "CourseListWidget.h"
#include <QPushButton>
#include "InterMediaCtrl.h"
#include "common/common.h"
#include <QVBoxLayout>
#include <QEvent>
#include <QResizeEvent>
#include <QScrollBar>
#include <QDebug>
#include "CourseCardWidget.h"
#include "dataCenter/DataProvider.h"

CourseListWidget::CourseListWidget(QWidget *parent) : QWidget(parent)
{
    m_columnCount = 3;
    this->setAttribute(Qt::WA_StyledBackground);
    initUi();

    initConnections();
}

void CourseListWidget::initUi()
{
    setContentsMargins(0,0,0,0);
    QVBoxLayout * layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,4,0);

    m_statusTitle = new QFrame(this);
    m_statusTitle->setObjectName("course_title1");
    m_statusTitle->setFixedHeight(56);
    m_subTitle = new QFrame(this);
    m_subTitle->setObjectName("course_title2");
    m_subTitle->setFixedHeight(56);

    m_stackedLayout = new QStackedLayout;
    m_stackedLayout->setContentsMargins(0,0,4,0);
    m_area = new QScrollArea(this);
    m_noCourseWidget = new QWidget(this);

    m_stackedLayout->addWidget(m_area);
    m_stackedLayout->addWidget(m_noCourseWidget);

    layout->addWidget(m_statusTitle);
    layout->addWidget(m_subTitle);


    layout->addLayout(m_stackedLayout);


    layout->addSpacing(10);

    this->setLayout(layout);

    initTitle1();
    initTitle2();

    initArea();
    initNoCourseUi();

//    changeToNoCourseMode();
}

void CourseListWidget::clearTitle()
{
    clearTitle1();
    clearTitle2();
}
void CourseListWidget::clearTitle1()
{
    QLayoutItem *child;
    while ((child = m_statusTitle->layout()->takeAt(0)) != 0)
    {
        if(child->widget())
        {
            child->widget()->setParent(NULL);
        }
        delete child;
    }
}
void CourseListWidget::clearTitle2()
{
    QLayoutItem *child;
    while ((child = m_subTitle->layout()->takeAt(0)) != 0)
    {
        if(child->widget())
        {
            child->widget()->setParent(NULL);
        }
        delete child;
    }
}

void CourseListWidget::clearArea()
{
    QLayoutItem *child;
    while ((child = m_scrolLayout->takeAt(0)) != 0)
    {
        if(child->widget())
        {
            child->widget()->setParent(NULL);
        }
        delete child;
    }

    m_scrolWidget->setFixedHeight(m_area->height()); // hide scrollbar

    if(m_tip!=nullptr)
        m_tip->setVisible(false);
}


void CourseListWidget::refresh()
{
    //clear
    clearTitle();
    clearArea();

    //==============================
    //request data

    //course info
    QList<CourseCardInfo> lst;

    FilterType filter;
    filter.status = 0;
    filter.subjectType = 0;
    filter.nextZone = m_nextZone;
    int ret = DataProvider::GetInstance().requestCourseCard(filter,lst,m_nextZone);

    //title info
    CourseConfigInfo info1;
    ret = DataProvider::GetInstance().requestCourseConfig(info1);

    updateTitle1ByInfo(info1.courseStatus);
    updateTitle2ByInfo(info1.subjects);

    updateAreaByInfo(lst);

    //==============================

}

void CourseListWidget::requestMoreCourseInfo()
{
    qDebug()<<"CourseListWidget::requestMoreCourseInfo()";

    //===========================================
    //request data

    int id1 = m_groupTitle1->checkedId();
    int id2 = m_groupTitle2->checkedId();

    //course info
    QList<CourseCardInfo> lst;

    FilterType filter;
    filter.status = id1;
    filter.subjectType = id2;
    filter.nextZone = m_nextZone;
    int ret = DataProvider::GetInstance().requestCourseCard(filter,lst,m_nextZone);


    //update by data
    int count = m_cardList.count();

    int start = count;
    int end = count+lst.count();

    for(int i = start; i < end; i++)
    {
        CourseCardWidget *w = new CourseCardWidget(this);
        w->setCourseInfo(lst.at(i-start));

        m_cardList.append(w);
        m_scrolLayout->addWidget(w,i/m_columnCount,i%m_columnCount);
    }

    updateScrollArea(m_area->size());
    //===========================================
}

void CourseListWidget::updateTitle1ByInfo(const QMap<int, QString> &info)
{
    qDebug()<<m_statusTitle->layout()->count();
    clearTitle1();
    qDebug()<<m_statusTitle->layout()->count();


    QHBoxLayout * h_layout = qobject_cast<QHBoxLayout*>(m_statusTitle->layout());
    h_layout->setSpacing(46);
    h_layout->addSpacing(30);

    QMap<int, QString>::const_iterator i = info.constBegin();
    while (i != info.constEnd()) {

        QPushButton * btn = new QPushButton(m_statusTitle);
//        btn->setFixedSize(64,24);

        btn->setCheckable(true);
        btn->setText(i.value());

        m_groupTitle1->addButton(btn,i.key());
        h_layout->addWidget(btn);

        if(i.key() == 0)
        {
            btn->setChecked(true);
        }

        ++i;
    }
    h_layout->addStretch();
    m_statusTitle->setLayout(h_layout);
}

void CourseListWidget::updateTitle2ByInfo(const QMap<int, QString> &info)
{
    qDebug()<<m_subTitle->layout()->count();
    clearTitle2();
    qDebug()<<m_subTitle->layout()->count();


    QHBoxLayout * h_layout = qobject_cast<QHBoxLayout*>(m_subTitle->layout());
    h_layout->setSpacing(24);
    h_layout->addSpacing(30);

    QMap<int, QString>::const_iterator i = info.constBegin();
    while (i != info.constEnd()) {

        QPushButton * btn = new QPushButton(m_subTitle);
        btn->setFixedSize(64,24);

        btn->setCheckable(true);
        btn->setText(i.value());

        m_groupTitle2->addButton(btn,i.key());
        h_layout->addWidget(btn);

        if(i.key() == 0)
        {
            btn->setChecked(true);
        }

        ++i;
    }
    h_layout->addStretch();
    m_subTitle->setLayout(h_layout);
}


void CourseListWidget::updateAreaByInfo(const QList<CourseCardInfo> &info)
{
    if(info.count() == 0)
    {
        changeToNoCourseMode();
    }
    else
    {
        changeToCourseListMode();

        clearArea();

        m_cardList.clear();

        for(int i  = 0; i<info.count(); i++)
        {
            CourseCardWidget *w = new CourseCardWidget(this);
            w->setCourseInfo(info.at(i));

            m_cardList.append(w);
            m_scrolLayout->addWidget(w,i/m_columnCount,i%m_columnCount);
        }
        updateScrollArea(m_area->size());
    }
}

void CourseListWidget::initConnections()
{
//    QScrollBar * vscrollBar = m_area->verticalScrollBar();
//    connect(vscrollBar, &QScrollBar::valueChanged,[=](int value) {
//        if(vscrollBar->maximum() == value)
//        {
//            qDebug()<<"============need loading========";
//        }
//    });

    connect(m_groupTitle1,static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
            [=](QAbstractButton * btn){
        //==========================================
        //request data
        int id1 = m_groupTitle1->checkedId();
        int id2 = m_groupTitle2->checkedId();

        //course info
        QList<CourseCardInfo> lst;

        FilterType filter;
        filter.status = id1;
        filter.subjectType = id2;
        filter.nextZone = m_nextZone;
        int ret = DataProvider::GetInstance().requestCourseCard(filter,lst,m_nextZone);

        updateAreaByInfo(lst);
        //===========================================

           });
    connect(m_groupTitle2,static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
            [=](QAbstractButton * btn){
        //==========================================
        //request data
        int id1 = m_groupTitle1->checkedId();
        int id2 = m_groupTitle2->checkedId();

        //course info
        QList<CourseCardInfo> lst;

        FilterType filter;
        filter.status = id1;
        filter.subjectType = id2;
        filter.nextZone = m_nextZone;
        int ret = DataProvider::GetInstance().requestCourseCard(filter,lst,m_nextZone);

        updateAreaByInfo(lst);
        //===========================================

    });
}

void CourseListWidget::initNoCourseUi()
{
    QVBoxLayout *layout = new QVBoxLayout;

    m_noCourseWidget->setContentsMargins(0,0,0,10);

    layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    QLabel* noClassImg = new QLabel(this);
    noClassImg->setFixedSize(250,186);
    noClassImg->setObjectName("c_noClassImg");
    QLabel* noClassTip = new QLabel(this);
    noClassTip->setObjectName("c_noClassTip");
    noClassTip->setFixedHeight(14);
    noClassTip->setText(QString::fromLocal8Bit("暂无课程，快去选课看看吧~"));

    layout->addStretch();
    layout->addWidget(noClassImg,0,Qt::AlignCenter);
    layout->addWidget(noClassTip,0,Qt::AlignCenter);
    layout->addStretch();

    m_noCourseWidget->setStyleSheet("QWidget{\
                        background:#FFFFFF;\
                    }");


    m_noCourseWidget->setLayout(layout);
}

void CourseListWidget::changeToCourseListMode()
{
    m_stackedLayout->setCurrentIndex(Course);
}

void CourseListWidget::changeToNoCourseMode()
{
    m_stackedLayout->setCurrentIndex(NoCourse);
}

void CourseListWidget::initTitle1()
{
    m_groupTitle1 = new QButtonGroup(this);
    QPushButton * btn1 = new QPushButton(m_statusTitle);
    QPushButton * btn2 = new QPushButton(m_statusTitle);
    QPushButton * btn3 = new QPushButton(m_statusTitle);
    QPushButton * btn4 = new QPushButton(m_statusTitle);

    btn1->setCheckable(true);
    btn2->setCheckable(true);
    btn3->setCheckable(true);
    btn4->setCheckable(true);

    m_groupTitle1->addButton(btn1,0);
    m_groupTitle1->addButton(btn2,1);
    m_groupTitle1->addButton(btn3,2);
    m_groupTitle1->addButton(btn4,3);

    btn1->setText(QString::fromLocal8Bit("全部"));
    btn2->setText(QString::fromLocal8Bit("未开始"));
    btn3->setText(QString::fromLocal8Bit("正在学"));
    btn4->setText(QString::fromLocal8Bit("已结束"));

    QHBoxLayout * h_layout = new QHBoxLayout;
    h_layout->setSpacing(46);
    h_layout->addSpacing(30);
    h_layout->addWidget(btn1);
    h_layout->addWidget(btn2);
    h_layout->addWidget(btn3);
    h_layout->addWidget(btn4);
    h_layout->addStretch();
    m_statusTitle->setLayout(h_layout);
}

void CourseListWidget::initTitle2()
{
    m_groupTitle2 = new QButtonGroup(this);
    QPushButton * btn1 = new QPushButton(m_subTitle);
    QPushButton * btn2 = new QPushButton(m_subTitle);
    QPushButton * btn3 = new QPushButton(m_subTitle);
    QPushButton * btn4 = new QPushButton(m_subTitle);

    btn1->setCheckable(true);
    btn2->setCheckable(true);
    btn3->setCheckable(true);
    btn4->setCheckable(true);

    btn1->setFixedSize(64,24);
    btn2->setFixedSize(64,24);
    btn3->setFixedSize(64,24);
    btn4->setFixedSize(64,24);

    m_groupTitle2->addButton(btn1,1);
    m_groupTitle2->addButton(btn2,2);
    m_groupTitle2->addButton(btn3,3);
    m_groupTitle2->addButton(btn4,4);

    btn1->setText(QString::fromLocal8Bit("全部"));
    btn2->setText(QString::fromLocal8Bit("语文"));
    btn3->setText(QString::fromLocal8Bit("数学"));
    btn4->setText(QString::fromLocal8Bit("英语"));

    QHBoxLayout * h_layout = new QHBoxLayout;
    h_layout->setSpacing(24);
    h_layout->addSpacing(30);
    h_layout->addWidget(btn1);
    h_layout->addWidget(btn2);
    h_layout->addWidget(btn3);
    h_layout->addWidget(btn4);
    h_layout->addStretch();
    m_subTitle->setLayout(h_layout);
}

void CourseListWidget::initArea()
{
    m_area->setMouseTracking(true);
    m_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    m_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_area->verticalScrollBar()->setStyleSheet(SCROLLBAR_CSS);

    m_area->setContentsMargins(0,0,0,0);
    m_area->installEventFilter(this);


    m_scrolWidget = new QWidget(m_area);
    m_scrolWidget->setObjectName("course_scrol");
    m_scrolWidget->setContentsMargins(32,8,32,0);
    m_scrolLayout = new QGridLayout;

    m_scrolLayout->setContentsMargins(2,2,2,2);
    m_scrolLayout->setSpacing(32);
    m_scrolLayout->setSizeConstraint(QLayout::SetFixedSize);

    CourseCardInfo info;
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

    info.isRefund = true;

    m_cardList.clear();
    for(int i  = 0; i<45; i++)
    {
        CourseCardWidget *w = new CourseCardWidget(this);
        w->setCourseInfo(info);

        m_cardList.append(w);
        m_scrolLayout->addWidget(w,i/3,i%3);
    }

    m_tip = new QLabel(m_scrolWidget);
    m_tip->setFixedHeight(16);
    m_tip->setObjectName("cList_tip");
    m_tip->setText(QString::fromLocal8Bit("没有更多了~"));
    QVBoxLayout *v_layout = new QVBoxLayout;
    v_layout->setContentsMargins(0,0,0,0);

    v_layout->addLayout(m_scrolLayout,0);
    v_layout->addStretch();
    v_layout->addWidget(m_tip,0,Qt::AlignCenter);

    m_scrolWidget->setLayout(v_layout);
    m_area->setWidget(m_scrolWidget);
}

bool CourseListWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_area) {
        if (event->type() == QEvent::Resize) {
            QResizeEvent *reEvt = static_cast<QResizeEvent*>(event);
            updateScrollArea(reEvt->size());
        }
        if(event->type() == QEvent::Wheel) {
            if(m_area->verticalScrollBar()->value() == m_area->verticalScrollBar()->maximum())
            {
                //=====================================================
                qDebug()<<"=====NEED LOADING MoreData======";
                requestMoreCourseInfo();
                //=====================================================
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void CourseListWidget::updateScrollArea(const QSize &size)
{
    int width = size.width();
    int height = size.height();

    m_scrolWidget->setFixedWidth(width);

    //调整列数
    {
        int max_width = (m_columnCount+1) *(384 +32);

        if(width > max_width)
        {
            m_columnCount++;
            updateUiByColumn();
        }

        int min_width = (m_columnCount-1)*(384+50);

        if(width <= min_width)
        {
            m_columnCount--;
            updateUiByColumn();
        }
    }


    //调整高度
    if(m_scrolWidget->height() < height)
    {
        m_scrolWidget->setFixedHeight(height);
    }
    else
    {
        int contentHeight = (m_cardList.count()/m_columnCount + 1)*(174+32);
        if(contentHeight < height)
            m_scrolWidget->setFixedHeight(height);
        else
            m_scrolWidget->setFixedHeight(contentHeight);
    }
}

void CourseListWidget::updateUiByColumn()
{
    while (m_scrolLayout->count()) {

        m_scrolLayout->takeAt(0);
    }

    for(int i  = 0; i<m_cardList.count(); i++)
    {
        CourseCardWidget *w = m_cardList.at(i);

        m_scrolLayout->addWidget(w,i/m_columnCount,i%m_columnCount);
    }
}
