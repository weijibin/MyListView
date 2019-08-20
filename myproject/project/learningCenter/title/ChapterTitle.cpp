#include "ChapterTitle.h"
#include "InterMediaCtrl.h"
#include <QHBoxLayout>

ChapterTitle::ChapterTitle(QWidget *parent) : TitleBaseWidget(parent)
{
    initOtherUi();
    initOtherConnections();
}


void ChapterTitle::initOtherUi()
{
    m_backHome = new ToolButton(this);
    m_backHome->setObjectName("l_back");
    m_backHome->setFixedSize(60,30);
    m_backHome->setDisplyText("返回");
//    m_backHome->setIconSize(QSize(20,20));
//    m_backHome->setIcon(QIcon(":/res/icon_fanhui_hover.png"));


    m_courseName = new QLabel(this);
    m_courseName->setObjectName("l_courseName");
    m_courseName->setText("dadfadfadfasdfasdfasdfasdfsaf");

    m_material = new QPushButton(this);
    m_material->setFixedSize(80,32);
    m_material->setObjectName("l_material");
    m_material->setText("学习资料");

#if defined(Q_OS_WIN)
    m_layout->insertSpacing(0,20);
    m_layout->insertWidget(1,m_backHome);
    m_layout->insertStretch(2);
    m_layout->insertWidget(3, m_courseName);
    m_layout->insertStretch(4);
    m_layout->insertWidget(5, m_material);
    m_layout->insertSpacing(6,10);
#else
    m_layout->addWidget(m_backHome);
    m_layout->addStretch();
    m_layout->addWidget(m_courseName);
    m_layout->addStretch();
    m_layout->addWidget(m_material);
    m_layout->addWidget(m_updateBtn);
#endif
}

void ChapterTitle::initOtherConnections()
{
    connect(m_backHome,&QPushButton::clicked,[=](){
        InterMediaCtrl::GetInstance().changeToHome();
    });
    connect(m_material,&QPushButton::clicked,[=](){
//        setMaterialVisible(!(m_material->isVisible()));
    });
}

void ChapterTitle::setMaterialVisible(bool visible)
{
    if(m_material != nullptr)
    {
        m_material->setVisible(visible);
    }
}

void ChapterTitle::setCourseName(const QString &name)
{
    m_courseName->setText(name);
}
