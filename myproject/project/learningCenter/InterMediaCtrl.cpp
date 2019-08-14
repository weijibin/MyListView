#include "InterMediaCtrl.h"
#include "LearningCenterWidget.h"
#include "MainWidget.h"
#include "ChapterWidget.h"

InterMediaCtrl::InterMediaCtrl()
{

}

void InterMediaCtrl::initState()
{
    if(m_centerWidget != nullptr)
    {
        m_centerWidget->initState();
    }
}

void InterMediaCtrl::changeToClassMode()
{
    if(m_mainWidget != nullptr)
    {
        m_mainWidget->changeToClassMode();
    }
}

void InterMediaCtrl::changeToCourseMode()
{
    if(m_mainWidget != nullptr)
    {
        m_mainWidget->changeToCourseMode();
    }
}

void InterMediaCtrl::changeToChapterMode(const CourseToChapterPar & par)
{
    if(m_centerWidget != nullptr)
    {
        m_centerWidget->changeToChapterMode(par);
    }
}

void InterMediaCtrl::changeToHome()
{
    if(m_centerWidget != nullptr)
    {
        m_centerWidget->changeToHomeMode();
    }
}

void InterMediaCtrl::changeToCefModel()
{
    if(m_chapterWidget != nullptr)
    {
        m_chapterWidget->changeToCefView();
    }
}

void InterMediaCtrl::changeToChapterModeFromCef()
{
    if(m_chapterWidget != nullptr)
    {
        m_chapterWidget->changeToChapter();
    }
}

void InterMediaCtrl::enterRoom(const QString &url)
{
    if(m_centerWidget != nullptr)
    {
        m_centerWidget->enterRoom(url);
    }
}