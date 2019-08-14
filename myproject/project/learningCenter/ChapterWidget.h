#ifndef CHAPTERWIDGET_H
#define CHAPTERWIDGET_H

#include <QWidget>
#include "common/common.h"

class ChapterTitle;
class ChapterListWidget;
class QStackedLayout;
class CefViewWidget;

class ChapterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChapterWidget(QWidget *parent = 0);

    void setOuterWidget(QWidget*w);

    enum Index{ Chapter, CefView};

    void changeToCefView();
    void changeToChapter();

    void setCourseInfo(const CourseToChapterPar & par);

signals:

public slots:
private:
    void initUI();

private:

    ChapterTitle *m_title = nullptr;
    ChapterListWidget *m_chapterList = nullptr;
    CefViewWidget    * m_cefViewWidget = nullptr;

    QStackedLayout * m_stackedLayout = nullptr;

    CourseToChapterPar m_courseInfo;


};

#endif // CHAPTERWIDGET_H
