#ifndef STUDYFILESLISTWIDGET_H
#define STUDYFILESLISTWIDGET_H

#include <QObject>
#include <QWidget>
#include "common/common.h"
class StudyDirWidget;
class StudyFileItem;
class QScrollArea;
class QVBoxLayout;
class QHBoxLayout;
class QStackedWidget;
class StudyFilesListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StudyFilesListWidget(QWidget *parent = nullptr);

    void setFilesContents(QList<MaterialUnit> list);
    void initUi();
    void clearContents();

//    void setNofilesWidget();
//    void setLoadingWidget();


signals:

public slots:

private:
    QList<StudyFileItem *>      m_fileList;
    QList<StudyDirWidget*>      m_dirList;
    QScrollArea                *m_scrollWidget;
    QWidget                    *m_widget;
    QHBoxLayout                *m_hLayout;
    QVBoxLayout                *m_scrollLayout;
    QStackedWidget             *m_stackWidget;
    QWidget                    *m_otherWidget;
};

#endif // STUDYFILESLISTWIDGET_H
