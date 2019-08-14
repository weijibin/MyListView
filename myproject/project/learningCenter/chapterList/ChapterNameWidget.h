#ifndef CHAPTERNAMEWIDGET_H
#define CHAPTERNAMEWIDGET_H

#include <QObject>
#include <QWidget>

class QLabel;
class QVBoxLayout;
class ChapterNameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChapterNameWidget(QWidget *parent = nullptr);
    ~ChapterNameWidget();

public:
    void setChapterContents(QString name, QString time, bool isTitle =false, bool isChange=false);

private:
    void initLayout();
    void setChapterNameLabel(QString name);
    void setChapterTimeLabel(QString time);
    void setAdjustChapterLabel();
    void setEnglishTitle(QString name);

private:
    QLabel       *m_nameLabel;
    QLabel       *m_timeLabel;
    QLabel       *m_changeChapterLabel;
    QVBoxLayout  *m_vbLayout;
};

#endif // CHAPTERNAMEWIDGET_H
