#ifndef LEARNINGCENTERWIDGET_H
#define LEARNINGCENTERWIDGET_H

#include <QWidget>

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
signals:

public slots:

private:
    void initUI();

private:
    ChapterWidget * m_chapterWidget;
    MainWidget * m_mainWidget;

    QStackedLayout * m_stackedLayout;

};

#endif // LEARNINGCENTERWIDGET_H
