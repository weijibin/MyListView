#ifndef CHAPTERLISTWIDGET_H
#define CHAPTERLISTWIDGET_H
#include "common/common.h"
#include <QWidget>
class QVBoxLayout;
class QScrollArea;
class ChapterItem;
class QLabel;
class ChapterListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChapterListWidget(QWidget *parent = 0);
    ~ChapterListWidget();

public:
    void setChapterListContents(const QList<ChapterInfo> &list, const QString &validTime);

    void clearAllContens();
signals:

protected:
    virtual void paintEvent(QPaintEvent *event) override;

public slots:
private:
    void initUi();
    void initConnections();

private:
    QList<ChapterInfo>     m_chapterInfoList;
    QList<ChapterItem*>    m_chapterItemList;
    QLabel                *m_endLabel;

    QVBoxLayout           *m_vbLayout;
    QVBoxLayout           *m_scrollLayout;
    QScrollArea           *m_chapterScroll;
    QWidget               *m_scrollWidget;

};

#endif // CHAPTERLISTWIDGET_H
