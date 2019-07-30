#include "LearningCenterWidget.h"
#include "MainWidget.h"
#include "ChapterWidget.h"
#include "InterMediaCtrl.h"

#include <QStackedLayout>
#include <QVBoxLayout>



LearningCenterWidget::LearningCenterWidget(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    initUI();
}

void LearningCenterWidget::initUI()
{
    m_mainWidget = new MainWidget(this);
    m_chapterWidget = new ChapterWidget(this);

    m_mainWidget->setOuterWidget(this);
    m_chapterWidget->setOuterWidget(this);


    m_stackedLayout = new QStackedLayout;
    m_stackedLayout->addWidget(m_mainWidget);
    m_stackedLayout->addWidget(m_chapterWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(m_stackedLayout);
    setLayout(mainLayout);

    this->setContentsMargins(0,0,0,0);
    mainLayout->setContentsMargins(0,0,0,0); 

    InterMediaCtrl::GetInstance().setMainWidget(m_mainWidget);
    InterMediaCtrl::GetInstance().setChapterWidget(m_chapterWidget);

    initState();
}

void LearningCenterWidget::initState()
{
    m_stackedLayout->setCurrentIndex(Main);
    m_mainWidget->initState();
}

void LearningCenterWidget::changeToChapterMode()
{
    m_stackedLayout->setCurrentIndex(Chapter);
}

void LearningCenterWidget::changeToHomeMode()
{
    m_stackedLayout->setCurrentIndex(Main);
}
