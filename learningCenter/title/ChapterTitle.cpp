#include "ChapterTitle.h"
#include "InterMediaCtrl.h"
#include <QHBoxLayout>

ChapterTitle::ChapterTitle(QWidget *parent) : TitleWidget(parent)
{
    initOtherUi();
}


void ChapterTitle::initOtherUi()
{
    m_backHome = new QPushButton(this);

    m_layout->insertWidget(0,m_backHome);
    m_layout->insertSpacing(0,20);

    connect(m_backHome,&QPushButton::clicked,[=](){
        InterMediaCtrl::GetInstance().changeToHome();
    });
}
