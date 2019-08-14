#ifndef CHAPTERITEM_H
#define CHAPTERITEM_H

#include <QObject>
#include <QWidget>
#include "common/common.h"
class ChapterNameWidget;
class TeacherHeadWidget;

class QPushButton;
class QLabel;
class QHBoxLayout;
class ButtonWidget;

class ChapterItem : public QWidget
{
    Q_OBJECT
public:
    explicit ChapterItem(QWidget *parent = nullptr);
    ~ChapterItem();

public:
    void setChapterItemContents(ChapterInfo info);
    void setChapterEnglishTitle(QString title);

signals:

public slots:


private:
    ChapterNameWidget       *m_title;
    TeacherHeadWidget       *m_teacherHead;
    ButtonWidget            *m_buttonWidget;
    ChapterInfo              m_chapterInfo;
    QHBoxLayout             *m_hbLayout;
};

class ButtonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonWidget(QWidget *parent = nullptr);
    ~ButtonWidget();

    void setButtonWidgetContents(QString livetText, QList<ButtonInfo> infoList);

    void setLiveStatusLabel(QString text);
    QPushButton* setEnterRoomButton(QString text, int status = 1);
    QPushButton* setProgramButton(QString text, int status = 1);
    QPushButton* setButtonInfo(ButtonInfo info);
    void initLayout();

public slots:
    void onButtonClick();

private:
    QList<QPushButton*>      m_buttonList;
    QLabel                  *m_liveStatusLabel;
    QList<ButtonInfo>        m_buttonInfoList;
    QHBoxLayout             *m_hbLayout;
};

#endif // CHAPTERITEM_H
