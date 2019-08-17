#include "ClassCardWidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include "common/TeacherHeadWidget.h"

#include <QGraphicsDropShadowEffect>

ClassCardWidget::ClassCardWidget(int type,QWidget *parent) : QWidget(parent)
{
    m_type = type;

    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);

//    this->setFixedSize(772,512);

    if(m_type == 1)
        initUi();
    else
        initNoClassUi();

    setMouseTracking(true);

//    setContentsMargins(2,2,2,2);
//    QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect(this);
//    effect->setOffset(QPointF(0,0));
//    effect->setColor(Qt::gray);
//    effect->setBlurRadius(10);
//    this->setGraphicsEffect(effect);
}

void ClassCardWidget::initNoClassUi()
{
    setContentsMargins(0,0,0,0);
    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);

    m_noClassImg = new QLabel(this);
    m_noClassImg->setFixedSize(250,186);
    m_noClassImg->setObjectName("c_noClassImg");
    m_noClassTip = new QLabel(this);
    m_noClassTip->setObjectName("c_noClassTip");
    m_noClassTip->setFixedHeight(14);
    m_noClassTip->setText(QString::fromLocal8Bit("今天没有课程安排哦~"));

    m_layout->addStretch();
    m_layout->addWidget(m_noClassImg,0,Qt::AlignCenter);
    m_layout->addWidget(m_noClassTip,0,Qt::AlignCenter);
    m_layout->addStretch();

    setLayout(m_layout);

    this->setStyleSheet("QWidget{\
                        background:#FFFFFF;\
                        border-radius:8px;\
                    }");
}

void ClassCardWidget::initUi()
{
    setContentsMargins(0,0,0,0);
    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);


    m_widgetEntrance = new QFrame();
    m_widgetEntrance->setObjectName("class_entrance");
    m_widgetCourseInfo = new QFrame();
    m_widgetCourseInfo->setObjectName("class_courseinfo");

    m_layout->addWidget(m_widgetEntrance);
    m_layout->addWidget(m_widgetCourseInfo);

    initEntrance();
    initCourseInfo();

    setLayout(m_layout);

    m_widgetEntrance->setMouseTracking(true);
    m_widgetCourseInfo->setMouseTracking(true);
}

void ClassCardWidget::initEntrance()
{
    m_widgetEntrance->setContentsMargins(0,0,0,0);
    QVBoxLayout * layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);

    QHBoxLayout *layout_time = new QHBoxLayout;
    layout_time->setContentsMargins(0,0,0,0);
    m_classTime = new QLabel(this);
    m_classTime->setObjectName("c_classTime");
    m_classTime->setContentsMargins(16,6,16,6);
    m_classTime->setFixedHeight(32);
    m_classTime->setAlignment(Qt::AlignCenter);
    layout_time->addWidget(m_classTime);
    layout_time->addStretch();
    layout->addLayout(layout_time);

    m_classDescribe = new QLabel(this);
    m_classDescribe->setObjectName("c_classdes");
    m_classDescribe->setAlignment(Qt::AlignCenter);
    m_classDescribe->setFixedHeight(24);
    m_classTip = new QLabel(this);
    m_classTip->setObjectName("c_tip");
    m_classTip->setAlignment(Qt::AlignCenter);
    m_classTip->setFixedHeight(19);

    m_enterClassBtn = new QPushButton(this);
    m_enterClassBtn->setObjectName("c_enterclass");
    m_enterClassBtn->setFixedHeight(44);
    m_enterClassBtn->setFixedWidth(160);

    layout->addStretch();
    layout->addWidget(m_classDescribe,0,Qt::AlignCenter);
    layout->addWidget(m_classTip,0,Qt::AlignCenter);
    layout->addWidget(m_enterClassBtn,0,Qt::AlignCenter);
    layout->addStretch();

    m_widgetEntrance->setLayout(layout);

//    m_classTime->setText(QString::fromLocal8Bit("今日第2场 08:30-10:30"));
//    m_classDescribe->setText(QString::fromLocal8Bit("直播进行中..."));
//    m_classTip->setText(QString::fromLocal8Bit("记得去APP完成课清哦~"));
//    m_enterClassBtn->setText(QString::fromLocal8Bit("去上课"));
}

void ClassCardWidget::initCourseInfo()
{
    //courseinfo

    m_widgetCourseInfo->setFixedHeight(80);
    m_widgetCourseInfo->setContentsMargins(0,0,0,0);
    QHBoxLayout * layout = new QHBoxLayout;
    layout->setContentsMargins(30,0,0,15);

    QVBoxLayout * layout_info = new QVBoxLayout;
    layout_info->setContentsMargins(0,0,0,0);
    layout_info->setSpacing(0);

    m_chaperName = new QLabel(this);
    m_chaperName->setObjectName("c_chaptername");
    m_chaperName->setFixedHeight(18);


    QHBoxLayout * layout_c = new QHBoxLayout;
    layout_c->setContentsMargins(0,0,0,0);

    m_subjectName = new QLabel(this);
    m_subjectName->setContentsMargins(2,0,2,0);
    m_subjectName->setObjectName("c_subname");
    m_courseName = new QLabel(this);
    m_courseName->setObjectName("c_courname");



    layout_c->addWidget(m_subjectName);
    layout_c->addWidget(m_courseName);
    layout_c->addStretch();

    layout_info->addSpacing(15);
    layout_info->addWidget(m_chaperName,Qt::AlignLeft);
    layout_info->addSpacing(10);
    layout_info->addLayout(layout_c);
    layout_info->addStretch();


    m_teachersInfo = new TeacherHeadWidget(this);

//    m_teachersInfo->setContentsMargins(0,0,0,30);


    layout->addLayout(layout_info);
    layout->addStretch();

    layout->addWidget(m_teachersInfo,0,Qt::AlignTop);

    layout->addSpacing(20);

    m_widgetCourseInfo->setLayout(layout);

//    m_chaperName->setText(QString::fromLocal8Bit("第一讲 函数奇偶性与对称性"));
//    m_subjectName->setText(QString::fromLocal8Bit("数学"));
//    m_courseName->setText(QString::fromLocal8Bit("【2019-暑】六年级初一数学直播菁英班（北京人教）"));
}

void ClassCardWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

const ClassCardInfo& ClassCardWidget::getClassInfo()
{
    return m_info;
}

void ClassCardWidget::setClassInfo(const ClassCardInfo &info)
{
    m_info = info;
    if(m_type ==1)
        updateUiByInfo();
}

void ClassCardWidget::updateUiByInfo()
{
    QString str = QString::fromLocal8Bit("%1第%2场 %3-%4").arg(m_info.time.day)
            .arg(m_info.time.index).arg(m_info.time.startTime).arg(m_info.time.endTime);
    m_classTime->setText(str);
    m_classDescribe->setText(m_info.classStatus);
    m_classTip->setText(m_info.classTip);

    if(m_info.classStatusType == 0) {
        m_enterClassBtn->setVisible(false);
        m_classTip->setVisible(true);
    } else if(m_info.classStatusType == 1) {
        m_enterClassBtn->setVisible(true);
        m_classTip->setVisible(false);
        m_enterClassBtn->setText(m_info.btnText);
        m_enterClassBtn->setProperty("liveType","live");
    } else if(m_info.classStatusType == 2){
        m_enterClassBtn->setVisible(true);
        m_classTip->setVisible(false);
        m_enterClassBtn->setText(m_info.btnText);
        m_enterClassBtn->setProperty("liveType","playback");
    } else {
        m_enterClassBtn->setVisible(true);
        m_classTip->setVisible(true);
        m_enterClassBtn->setText(m_info.btnText);
        m_enterClassBtn->setProperty("liveType","playback");
    }

    {
        m_enterClassBtn->style()->unpolish(m_enterClassBtn);
        m_enterClassBtn->style()->polish(m_enterClassBtn);
    }

    m_chaperName->setText(m_info.chapterName);
    m_subjectName->setText(m_info.subjectName);
    m_courseName->setText(m_info.courseName);

    m_teachersInfo->setTeacherHeadInfo(m_info.teachers);
}
