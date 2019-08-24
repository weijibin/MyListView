#ifndef LEARNINGCENTERWIDGET_H
#define LEARNINGCENTERWIDGET_H

#include <QWidget>
#include "common/common.h"

class QStackedLayout;
class InterMediaCtrl;
class ChapterWidget;
class MainWidget;


class LearningCenterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LearningCenterWidget(QWidget *parent = 0);

    enum Index{ Main, Chapter };

    void initState();
    void changeToChapterMode(const CourseToChapterPar & par);
    void changeToHomeMode();

    void enterRoom(const QString& url);

    void refresh();
signals:

    void sigEnterRoom(const QString& url);  // 进入直播间信号

public slots:

private:
    void initUI();

private:
    ChapterWidget * m_chapterWidget;
    MainWidget * m_mainWidget;

    QStackedLayout * m_stackedLayout;

};

#endif // LEARNINGCENTERWIDGET_H
