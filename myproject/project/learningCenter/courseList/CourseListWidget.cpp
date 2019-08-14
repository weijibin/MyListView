#include "CourseListWidget.h"
#include <QPushButton>
#include "InterMediaCtrl.h"
#include "common/common.h"
#include <QVBoxLayout>
#include "CourseCardWidget.h"

CourseListWidget::CourseListWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    initUi();
}

void CourseListWidget::initUi()
{
//    QPushButton * btn = new QPushButton(this);
//    btn->move(100,100);

//    btn->setText("ChapterListWidget");

//    connect(btn,&QPushButton::clicked,[=](){

//        CourseToChapterPar par;
//        par.courseName = QStringLiteral("【2019-暑】六年级初一数学直播菁英班（北京人教）");
//        par.courseType = 1;
//        par.stuCouID = 12212121;
//        InterMediaCtrl::GetInstance().changeToChapterMode(par);
//    });

    setContentsMargins(0,0,0,0);
    QVBoxLayout * layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);

    m_statusTitle = new QFrame(this);
    m_statusTitle->setObjectName("course_title1");
    m_statusTitle->setFixedHeight(56);
    m_subTitle = new QFrame(this);
    m_subTitle->setObjectName("course_title2");
    m_subTitle->setFixedHeight(56);
    m_area = new QScrollArea(this);

    layout->addWidget(m_statusTitle);
    layout->addWidget(m_subTitle);
    layout->addWidget(m_area);
    layout->addSpacing(10);

    this->setLayout(layout);

    initTitle1();
    initTitle2();

    initArea();
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

    m_groupTitle1->addButton(btn1,1);
    m_groupTitle1->addButton(btn2,2);
    m_groupTitle1->addButton(btn3,3);
    m_groupTitle1->addButton(btn4,4);

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
//    m_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    m_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_area->setContentsMargins(0,0,0,0);
    m_area->installEventFilter(this);


    m_scrolWidget = new QWidget(m_area);
//    m_scrolWidget->setContentsMargins(0,0,0,0);
    m_scrolLayout = new QGridLayout(m_area);

    m_scrolLayout->setContentsMargins(0,0,0,0);
    m_scrolLayout->setSpacing(0);
//    m_scrolLayout->setSizeConstraint(QLayout::SetFixedSize);

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
    for(int i  = 0; i<14; i++)
    {
        CourseCardWidget *w = new CourseCardWidget(this);
        w->setCourseInfo(info);
        m_scrolLayout->addWidget(w,i/3,i%3);
    }

    m_scrolWidget->setLayout(m_scrolLayout);
    m_area->setWidget(m_scrolWidget);
}
