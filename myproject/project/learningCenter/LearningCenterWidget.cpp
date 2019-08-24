#include "LearningCenterWidget.h"
#include "MainWidget.h"
#include "ChapterWidget.h"
#include "InterMediaCtrl.h"

#include <QStackedLayout>
#include <QVBoxLayout>
#include "dataCenter/DataProvider.h"


LearningCenterWidget::LearningCenterWidget(QWidget *parent) : QWidget(parent)
{
#ifdef Q_OS_MAC
    setWindowFlag(Qt::NoDropShadowWindowHint);
#endif
//    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    initUI();
//    this->setFixedSize(1280,720);   //固定大小
    this->setMinimumSize(1280,720);

    DataProvider::GetInstance().setParentWidget(this);
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
}

void LearningCenterWidget::initState()
{
    m_stackedLayout->setCurrentIndex(Main);
    m_mainWidget->initState();

}

void LearningCenterWidget::changeToChapterMode(const CourseToChapterPar & par)
{
    m_stackedLayout->setCurrentIndex(Chapter);
    m_chapterWidget->setCourseInfo(par);
}

void LearningCenterWidget::changeToHomeMode()
{
    m_stackedLayout->setCurrentIndex(Main);
}

void LearningCenterWidget::enterRoom(const QString &url)
{
    emit sigEnterRoom(url);
}

void LearningCenterWidget::refresh()
{
    if(this->isVisible())
    {
        if(m_stackedLayout->currentIndex() == Main)
        {
            m_mainWidget->refresh();
        }
        else
        {
            m_chapterWidget->refresh();
        }
    }

}
