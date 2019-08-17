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
    void setChapterContents(const QString &name,const QString &time, bool isTitle =false, bool isChange=false);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void initLayout();
    void setChapterNameLabel(const QString &name);
    void setChapterTimeLabel(const QString &time);
    void setAdjustChapterLabel();
    void setEnglishTitle(const QString &name);

private:
    QLabel       *m_nameLabel;
    QLabel       *m_timeLabel;
    QLabel       *m_changeChapterLabel;
    QVBoxLayout  *m_vbLayout;
};

#endif // CHAPTERNAMEWIDGET_H
