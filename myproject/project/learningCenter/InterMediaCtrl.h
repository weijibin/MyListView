#ifndef INTERMEDIACTRL_H
#define INTERMEDIACTRL_H

#include "common/common.h"

class LearningCenterWidget;
class MainWidget;
class ChapterWidget;
class MainTitle;
class ChapterTitle;
class CourseListWidget;

class InterMediaCtrl
{
    InterMediaCtrl();

    InterMediaCtrl(const InterMediaCtrl &)=delete;
    InterMediaCtrl& operator=(const InterMediaCtrl &)=delete;
public:
    static InterMediaCtrl & GetInstance()
    {
        static InterMediaCtrl instance;
        return instance;
    }

    void initState();

    void refresh();

    void setCenterWidget(LearningCenterWidget*w){m_centerWidget=w;}
    void setMainWidget(MainWidget*w){m_mainWidget=w;}
    void setChapterWidget(ChapterWidget*w){m_chapterWidget=w;}
    void setCourseListWidget(CourseListWidget*w){m_courseListWidget=w;}

    void changeToClassMode();
    void changeToCourseMode();
    void changeToChapterMode(const CourseToChapterPar & par);

    //课程列表相关
    void changeToNoCourseMode();
    void changeToCourseListMode();

    void changeToHome();

    void changeToCefModel();
    void changeToChapterModeFromCef();

    void enterRoom(const QString & url);

//    void setMainTitle(MainTitle*w){m_mainTitle=w;}
//    void setChapterTitle(ChapterTitle*w){m_chapterTitle=w;}

private:
    LearningCenterWidget* m_centerWidget =nullptr;

    MainWidget* m_mainWidget =nullptr;

    ChapterWidget* m_chapterWidget =nullptr;  //场次列表

    CourseListWidget *m_courseListWidget = nullptr; //课程列表

//    MainTitle* m_mainTitle =nullptr;
//    ChapterTitle* m_chapterTitle =nullptr;
};

#endif // INTERMEDIACTRL_H

