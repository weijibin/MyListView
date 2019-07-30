#include "InterMediaCtrl.h"
#include "LearningCenterWidget.h"
#include "MainWidget.h"

InterMediaCtrl::InterMediaCtrl()
{

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

void InterMediaCtrl::changeToChapterMode()
{
    if(m_centerWidget != nullptr)
    {
        m_centerWidget->changeToChapterMode();
    }
}

void InterMediaCtrl::changeToHome()
{
    if(m_centerWidget != nullptr)
    {
        m_centerWidget->changeToHomeMode();
    }
}
