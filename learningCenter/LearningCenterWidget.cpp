#include "LearningCenterWidget.h"
#include "MainWidget.h"
#include "ChapterWidget.h"
#include "InterMediaCtrl.h"

#include <QStackedLayout>
#include <QVBoxLayout>



LearningCenterWidget::LearningCenterWidget(QWidget *parent) : QWidget(parent)
{

    initUI();
}

void LearningCenterWidget::initUI()
{
    m_mainWidget = new MainWidget(this);
    m_chapterWidget = new ChapterWidget(this);

    m_stackedLayout = new QStackedLayout;
    m_stackedLayout->addWidget(m_mainWidget);
    m_stackedLayout->addWidget(m_chapterWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(m_stackedLayout);
    setLayout(mainLayout);

    this->setContentsMargins(0,0,0,0);
    mainLayout->setContentsMargins(0,0,0,0);

    m_stackedLayout->setCurrentIndex(Main);

    InterMediaCtrl::GetInstance().setMainWidget(m_mainWidget);
    InterMediaCtrl::GetInstance().setChapterWidget(m_chapterWidget);

}
