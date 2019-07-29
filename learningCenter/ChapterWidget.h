#ifndef CHAPTERWIDGET_H
#define CHAPTERWIDGET_H

#include <QWidget>

class ChapterTitle;
class ChapterListWidget;

class ChapterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChapterWidget(QWidget *parent = 0);

signals:

public slots:
private:
    void initUI();

private:

    ChapterTitle *m_title = nullptr;
    ChapterListWidget *m_chapterList = nullptr;
};

#endif // CHAPTERWIDGET_H
