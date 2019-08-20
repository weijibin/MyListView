#include "MainWidget.h"

#include "title/MainTitle.h"
#include "classlist/ClassListWidget.h"
#include "courselist/CourseListWidget.h"
#include "InterMediaCtrl.h"
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QPushButton>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    initUI();
    initAbnormalUi();
    initConnections();
}

void MainWidget::initUI()
{
    m_title = new MainTitle(this);
    m_title->setObjectName("centerTitle");
    m_classList = new ClassListWidget(this);
    m_courseList = new CourseListWidget(this);


    m_stackedLayout = new QStackedLayout;
    m_stackedLayout->addWidget(m_classList);
    m_stackedLayout->addWidget(m_courseList);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_title);
    mainLayout->addLayout(m_stackedLayout);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    this->setContentsMargins(0,0,0,0);
    mainLayout->setContentsMargins(0,0,0,0);

    m_stackedLayout->setCurrentIndex(Class);

}

void MainWidget::initAbnormalUi()
{
    initTakeClassUi();
    initNoClassUi();
    initRetryClassUi();
}

void MainWidget::initTakeClassUi()
{
    QVBoxLayout *layout = new QVBoxLayout;
    QWidget * w = new QWidget;
    w->setObjectName("c_takewidget");
    w->setContentsMargins(0,0,0,10);

    layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    QLabel* noClassImg = new QLabel(this);
    noClassImg->setFixedSize(250,186);
    noClassImg->setObjectName("c_takeClassImg");
    QLabel* noClassTip = new QLabel(this);
    noClassTip->setObjectName("c_noClassTip");
    noClassTip->setFixedHeight(14);
    noClassTip->setText(QString::fromLocal8Bit("网校赠你一节精品课，快去领取吧！"));

    m_takeClassBtn = new QPushButton(this);
    m_takeClassBtn->setObjectName("c_takeClassBtn");
    m_takeClassBtn->setFixedSize(164,40);
    m_takeClassBtn->setText(QString::fromLocal8Bit("立即领取"));

    layout->addStretch();
    layout->addWidget(noClassImg,0,Qt::AlignCenter);
    layout->addWidget(noClassTip,0,Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(m_takeClassBtn,0,Qt::AlignCenter);
    layout->addStretch();

    w->setStyleSheet("QWidget#c_takewidget{\
                        background:#FFFFFF;\
                        border-bottom-right-radius: 8px;\
                        border-bottom-left-radius: 8px;\
                    }");
    w->setLayout(layout);
    m_stackedLayout->addWidget(w);
}

void MainWidget::initNoClassUi()
{
    QVBoxLayout *layout = new QVBoxLayout;
    QWidget * w = new QWidget;
    w->setContentsMargins(0,0,0,10);

    layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    QLabel* noClassImg = new QLabel(this);
    noClassImg->setFixedSize(250,186);
    noClassImg->setObjectName("c_noClassImg");
    QLabel* noClassTip = new QLabel(this);
    noClassTip->setObjectName("c_noClassTip");
    noClassTip->setFixedHeight(14);
    noClassTip->setText(QString::fromLocal8Bit("近期没有课程安排"));

    layout->addStretch();
    layout->addWidget(noClassImg,0,Qt::AlignCenter);
    layout->addWidget(noClassTip,0,Qt::AlignCenter);
    layout->addStretch();

    w->setStyleSheet("QWidget{\
                        background:#FFFFFF;\
                        border-bottom-right-radius: 8px;\
                        border-bottom-left-radius: 8px;\
                    }");


    w->setLayout(layout);
    m_stackedLayout->addWidget(w);
}

void MainWidget::initRetryClassUi()
{
    QVBoxLayout *layout = new QVBoxLayout;
    QWidget * w = new QWidget;
    w->setObjectName("c_retryWidget");
    w->setContentsMargins(0,0,0,10);

    layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    QLabel* noClassImg = new QLabel(this);
    noClassImg->setFixedSize(250,186);
    noClassImg->setObjectName("c_retryImg");
    QLabel* noClassTip = new QLabel(this);
    noClassTip->setObjectName("c_noClassTip");
    noClassTip->setFixedHeight(14);
    noClassTip->setText(QString::fromLocal8Bit("出了点错误，请稍后重试"));

    m_retryBtn = new QPushButton(this);
    m_retryBtn->setObjectName("c_retryBtn");
    m_retryBtn->setText(QString::fromLocal8Bit("重试"));
    m_retryBtn->setFixedSize(140,40);

    layout->addStretch();
    layout->addWidget(noClassImg,0,Qt::AlignCenter);
    layout->addWidget(noClassTip,0,Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(m_retryBtn,0,Qt::AlignCenter);
    layout->addStretch();

    w->setStyleSheet("QWidget#c_retryWidget{\
                        background:#FFFFFF;\
                        border-bottom-right-radius: 8px;\
                        border-bottom-left-radius: 8px;\
                    }");
    w->setLayout(layout);
    m_stackedLayout->addWidget(w);
}

void MainWidget::initConnections()
{

}

void MainWidget::setOuterWidget(QWidget *w)
{
    m_title->setOuterWidget(w);
}

void MainWidget::initState()
{
    //========================================
//    m_stackedLayout->setCurrentIndex(NoClass);
//    m_stackedLayout->setCurrentIndex(Retry);
//    m_stackedLayout->setCurrentIndex(TakeClass);
    //=========================================
    m_stackedLayout->setCurrentIndex(Class);
    m_title->initState();
    QDate date = QDate::currentDate();
    m_classList->refresh(date);
}

void MainWidget::initData()
{
    m_classList->refresh(QDate::currentDate());
}

void MainWidget::changeToClassMode()
{
    m_stackedLayout->setCurrentIndex(Class);
}

void MainWidget::changeToCourseMode()
{
    m_stackedLayout->setCurrentIndex(Course);
    m_courseList->refresh();
}

void MainWidget::changeToNoClassMode()
{
    m_stackedLayout->setCurrentIndex(NoClass);
}

void MainWidget::changeToRetryMode()
{
    m_stackedLayout->setCurrentIndex(Retry);
}

void MainWidget::changeToTakeClassMode()
{
    m_stackedLayout->setCurrentIndex(TakeClass);
}




