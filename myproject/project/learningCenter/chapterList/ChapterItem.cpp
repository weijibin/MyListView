﻿#include "ChapterItem.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>
#include <QStyleOption>
#include <QPainter>
#include "ChapterNameWidget.h"
#include "common/TeacherHeadWidget.h"
#include "common/common.h"

ChapterItem::ChapterItem(QWidget *parent)
    : QWidget(parent)
    , m_title(nullptr)
    , m_teacherHead(nullptr)
    , m_buttonWidget(nullptr)
    , m_hbLayout(nullptr)
{

#ifdef Q_OS_MAC
    setWindowFlag(Qt::NoDropShadowWindowHint);
#endif
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
   // setAttribute(Qt::WA_StyledBackground,true);

}

ChapterItem::~ChapterItem()
{

}

void ChapterItem::setChapterItemContents(const ChapterInfo &info)
{
    if (info.isEngTitle) {
        setChapterEnglishTitle(info.chapterName);

    } else {
        setFixedHeight(96);
        QString classTime = QString::fromLocal8Bit("上课时间: ") + info.time.day +"-" + info.time.startTime +" " +info.time.endTime;
        m_title = new ChapterNameWidget(this);
        m_title->setChapterContents(info.chapterName, classTime, false, info.isExchanged);

        m_hbLayout = new QHBoxLayout(this);
        m_hbLayout->setContentsMargins(32, 0, 32, 0);
        m_hbLayout->addWidget(m_title);
        m_hbLayout->addStretch();

        m_teacherHead = new TeacherHeadWidget(this);

        for(int i = 0; i <info.teachers.size(); i++) {
            m_teacher.append(info.teachers.at(i));
        }

        m_teacherHead->setTeacherHeadInfo(m_teacher);
        m_hbLayout->addWidget(m_teacherHead);
        m_hbLayout->addStretch();

        m_buttonWidget = new ButtonWidget(this);
        m_buttonWidget->setButtonWidgetContents(info.classStatus, info.buttons);
        m_hbLayout->addWidget(m_buttonWidget);
        setStyleSheet("background-color:#ffffff;");
    }

    adjustSize();
}

void ChapterItem::setChapterEnglishTitle(const QString &title)
{
    if (!m_hbLayout) {
        m_hbLayout = new QHBoxLayout(this);
    }

    if (!m_title) {
        m_title = new ChapterNameWidget(this);
        m_title->setChapterContents(title,"",true,false);
    }

    m_hbLayout->setContentsMargins(32, 0, 32, 0);
    m_hbLayout->addWidget(m_title);
    m_hbLayout->addStretch();

    setStyleSheet("background: #F5F5F5;");
    setFixedHeight(64);
    update();

}

void ChapterItem::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

ButtonWidget::ButtonWidget(QWidget *parent)
    : QWidget(parent)
    , m_liveStatusLabel(nullptr)
    , m_hbLayout(nullptr)

{
    initLayout();
    setFixedHeight(96);
    setFixedWidth(480);
}

ButtonWidget::~ButtonWidget()
{
    for(int i =0; i < m_buttonList.size(); i++) {
        QPushButton * button = m_buttonList.at(i);
        delete  button;
        button = nullptr;
    }
    m_buttonList.clear();

}

void ButtonWidget::setButtonWidgetContents(QString livetText, QList<ButtonInfo> infoList)
{
    setLiveStatusLabel(livetText);
    m_hbLayout->addStretch();
    m_hbLayout->addWidget(m_liveStatusLabel);
    for (int i = 0; i < infoList.size(); i++) {
        QPushButton * button = setButtonInfo(infoList.at(i));
        m_buttonList.append(button);
        m_buttonInfoList.append(infoList.at(i));
        m_hbLayout->addWidget(button);
        connect(m_buttonList.at(i), SIGNAL(clicked()), this, SLOT(onButtonClick()));
    }
    adjustSize();
    //show();
}

void ButtonWidget::setLiveStatusLabel(QString text)
{
    if (!m_liveStatusLabel) {
        m_liveStatusLabel = new QLabel(this);
        m_liveStatusLabel->setFixedSize(70, 18);
    }
    m_liveStatusLabel->setText(text);
    if (text == QString::fromLocal8Bit("直播待开始")) {
        m_liveStatusLabel->setStyleSheet("font-size:14px; font-family:Microsoft YaHei; color:#ADB4BE");
    } else if (text == QString::fromLocal8Bit("直播进行中")) {
        m_liveStatusLabel->setStyleSheet("font-size:14px; font-family:Microsoft YaHei; color:#FF5E50");
    } else if (text == QString::fromLocal8Bit("直播未完成")) {
        m_liveStatusLabel->setStyleSheet("font-size:14px; font-family:Microsoft YaHei; color:#212831");
    }
}

QPushButton *ButtonWidget::setEnterRoomButton(QString text, int status)
{
    QPushButton *button = new QPushButton;
    button->setText(text);
    button->setFixedSize(96, 36);
    button->setStyleSheet("QPushButton{ \
                              border: 0px solid;\
                              background-color:#F65345;\
                              font: 14px \"Microsoft YaHei\"; \
                              color:#FFFFFF;\
                              border-radius: 18px;\
                          }\
                           QPushButton:disabled{\
                              background-color:#DCDCDC;\
                              border-radius:18px;\
                              color:#FFFFFF;    \
                          }\
                          QPushButton:hover{\
                              border: 0px solid;\
                              background-color:#f67469;\
                              border-radius:18px;\
                              color:#FFFFFF;\
                              opacity:0.2;\
                          }\
                          QPushButton:pressed{\
                              background-color:#c44237;\
                              border-radius:18px;\
                              color:#FFFFFF;    \
                          }");

    if (0 == status) {
        // 可用

    } else if (1 == status) {
        // 不可用
        button->setDisabled(true);

    } else if (2 == status) {
        // 可用高亮状态
        button->setStyleSheet("QPushButton{ \
                              border: 0px solid;\
                              font: 14px \"Microsoft YaHei\"; \
                              color:#FFFFFF;\
                              border-radius: 18px;\
                              background:rgba(255,94,80,1); \
                              box-shadow:0px 4px 4px -2px rgba(255,94,80,0.3); \
                          }");
    }

   if (button->isEnabled()) {
       button->setCursor(QCursor(Qt::PointingHandCursor));
   } else {
       button->setCursor(QCursor(Qt::ArrowCursor));
   }
    return button;
}

QPushButton *ButtonWidget::setProgramButton(QString text, int status)
{
    QPushButton *button = new QPushButton;
    button->setText(text);
    button->setFixedSize(96, 36);
    button->setStyleSheet("QPushButton{ \
                          background:rgba(255,255,255,1); \
                          border-radius:18px; \
                          border:1px solid rgba(173,180,190,0.4); \
                          font-size:14px; \
                          color:rgba(33,40,49,1); \
                       } \
                       QPushButton:disabled{\
                          background:rgba(255,255,255,1);\
                          border-radius:18px;\
                          border:1px solid rgba(173,180,190,0.2); \
                          color:rgba(173,180,190,1); \
                       }\
                       QPushButton:hover{\
                          background:rgba(255,255,255,1); \
                          border-radius:18px; \
                          border:1px solid rgba(255,94,80,1); \
                          font-size:14px; \
                          color:rgba(255,94,80,1); \
                       }\
                       QPushButton:pressed{\
                          background:rgba(255,255,255,1); \
                          border-radius:18px; \
                          border:1px solid rgba(173,180,190,0.4); \
                          font-size:14px; \
                          color:rgba(33,40,49,1); \
                       }");

    if (0 == status) {  // 可用

    } else if (1 == status) { // 不可用
      button->setDisabled(true);
    } else if (2 == status) { // 可用高亮
     button->setStyleSheet("QPushButton{ \
                           background:rgba(255,255,255,1); \
                           border-radius:18px; \
                           border:1px solid rgba(173,180,190,0.4); \
                           font-size:14px; \
                           color:rgba(33,40,49,1); \
                        } ");
    } else {

    }

    if (button->isEnabled()) {
        button->setCursor(QCursor(Qt::PointingHandCursor));
    } else {
        button->setCursor(QCursor(Qt::ArrowCursor));
    }
    return button;
}

QPushButton *ButtonWidget::setButtonInfo(ButtonInfo info)
{
    if (!info.text.isNull()) {
        if (info.btnType == 0) {
            return setEnterRoomButton(info.text, info.status);
        } else {
            return  setProgramButton(info.text, info.status);
        }
    } else {
        return nullptr;
    }

}

void ButtonWidget::initLayout()
{
    if (!m_hbLayout) {
        m_hbLayout = new QHBoxLayout(this);
    }

    m_hbLayout->setContentsMargins(0,0,0,0);
    m_hbLayout->setSpacing(24);
}

void ButtonWidget::onButtonClick()
{
    // 获取发送方
    QPushButton *button = dynamic_cast<QPushButton*>(sender());
     int index = m_buttonList.indexOf(button);
     qDebug() << "press--->" << m_buttonInfoList.at(index).text;

    // URL 跳转
}
