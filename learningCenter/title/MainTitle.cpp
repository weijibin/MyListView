#include "MainTitle.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QButtonGroup>

#include "HeadImg.h"
#include "InterMediaCtrl.h"

MainTitle::MainTitle(QWidget *parent) : TitleWidget(parent)
{
    initOtherUi();
    initOtherConnections();
}

void MainTitle::initOtherUi()
{
    m_icon = new QLabel(this);
    m_icon->setText(QStringLiteral("学而思网校"));
    m_icon->setFixedSize(137,20);
    m_icon->setObjectName("appTitle");


    m_group = new QButtonGroup(this);
    m_class = new QPushButton(this);
    m_class->setObjectName("inClass");
    m_class->setCheckable(true);
    m_class->setText(QStringLiteral("上课"));
    m_course = new QPushButton(this);
    m_course->setObjectName("myCourse");
    m_course->setCheckable(true);
    m_course->setText(QStringLiteral("我的课程"));

    m_class->setFixedSize(88,36);
    m_course->setFixedSize(88,36);

    m_group->addButton(m_class);
    m_group->addButton(m_course);

    QWidget * tab = new QWidget(this);
    tab->setAttribute(Qt::WA_StyledBackground);
    tab->setFixedSize(178,38);
//    tab->setFixedHeight(38);
    tab->setObjectName("tabWidget");
    tab->setContentsMargins(0,0,0,0);

    QHBoxLayout * tabLayout = new QHBoxLayout(tab);
    tabLayout->setSpacing(0);
    tabLayout->setContentsMargins(1,1,1,1);

    tabLayout->addWidget(m_class);
    tabLayout->addWidget(m_course);

//    tabLayout->setSizeConstraint(QLayout::SetFixedSize);

    tab->setLayout(tabLayout);

    m_img = new HeadImg(QPixmap(":/res/default_boy_img.png"),this);
    m_name = new QLabel(this);
    m_name->setObjectName("stuName");
    m_name->setFixedWidth(50);
    m_name->setText("Hello");

    m_layout->insertWidget(1,m_name);
    m_layout->insertWidget(1,m_img);

//    m_layout->insertWidget(0,m_course);
//    m_layout->insertWidget(0,m_class);
    m_layout->insertWidget(0,tab);

    m_layout->insertStretch(0);
    m_layout->insertWidget(0,m_icon);
    m_layout->insertSpacing(0,20);
    m_layout->setSpacing(0);
}

void MainTitle::initOtherConnections()
{
    connect(m_class,&QPushButton::clicked,[=](){
        InterMediaCtrl::GetInstance().changeToClassMode();
    });

    connect(m_course,&QPushButton::clicked,[=](){
        InterMediaCtrl::GetInstance().changeToCourseMode();
    });
}

void MainTitle::initState()
{
    m_class->setChecked(true);
}
