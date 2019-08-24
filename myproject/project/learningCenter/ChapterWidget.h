#ifndef CHAPTERWIDGET_H
#define CHAPTERWIDGET_H

#include <QWidget>
#include "common/common.h"

class ChapterTitle;
class ChapterListWidget;
class QStackedLayout;
class CefViewWidget;
class StudyFilesListWidget;

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

    void refresh();

signals:

public slots:
    void onInitShowStudyFileWidget();
    void onShowStudyFileWidget();
private:
    void initUI();
    void updateUi();

private:

    ChapterTitle *m_title = nullptr;
    ChapterListWidget *m_chapterList = nullptr;
    CefViewWidget    * m_cefViewWidget = nullptr;

    QStackedLayout * m_stackedLayout = nullptr;

    CourseToChapterPar m_courseInfo;
    QList<ChapterInfo> m_chapterInfoList;
    StudyFilesListWidget     *m_studyFileWidget = nullptr;
    bool                      m_studyWidgetOpen;

};

#endif // CHAPTERWIDGET_H
