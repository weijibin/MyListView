#ifndef CHAPTERLISTWIDGET_H
#define CHAPTERLISTWIDGET_H

#include <QWidget>

class ChapterListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChapterListWidget(QWidget *parent = 0);

signals:

public slots:
private:
    void initUi();
    void initConnections();
};

#endif // CHAPTERLISTWIDGET_H
