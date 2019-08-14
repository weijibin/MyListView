﻿#include "ChapterNameWidget.h"
#include <QLabel>
#include <QVBoxLayout>

ChapterNameWidget::ChapterNameWidget(QWidget *parent)
    : QWidget(parent)
    , m_nameLabel(nullptr)
    , m_timeLabel(nullptr)
    , m_changeChapterLabel(nullptr)
    , m_vbLayout(nullptr)
{
    initLayout();
}

ChapterNameWidget::~ChapterNameWidget()
{

}

void ChapterNameWidget::setChapterContents(QString name, QString time, bool isTitle, bool isChange)
{
    if (isTitle) {
        setEnglishTitle(name);
    } else {
        setChapterNameLabel(name);
        setChapterTimeLabel(time);

        if (isChange) {
            setAdjustChapterLabel();

            QHBoxLayout *hbLayout = new QHBoxLayout;
            hbLayout->addWidget(m_changeChapterLabel);
            hbLayout->addWidget(m_nameLabel);
            hbLayout->setContentsMargins(0,0,0,0);
            hbLayout->setSpacing(8);

            m_vbLayout->addLayout(hbLayout);
            m_vbLayout->addWidget(m_timeLabel);
        } else {
            m_vbLayout->addWidget(m_nameLabel);
            m_vbLayout->addWidget(m_timeLabel);
        }
    }

    adjustSize();
}

void ChapterNameWidget::initLayout()
{
    if (!m_vbLayout) {
        m_vbLayout = new QVBoxLayout(this);
        m_vbLayout->setContentsMargins(0,24,0,24);
        m_vbLayout->setSpacing(8);
    }
}

void ChapterNameWidget::setChapterNameLabel(QString name)
{
    if (!m_nameLabel){
        m_nameLabel = new QLabel(this);
    }

    m_nameLabel->setText(name);
    m_nameLabel->setStyleSheet("font-size:16px;color:#212831;");
}

void ChapterNameWidget::setChapterTimeLabel(QString time)
{

    if (!m_timeLabel) {
        m_timeLabel = new QLabel(this);
    }
    m_timeLabel->setText(time);
    m_timeLabel->setStyleSheet("font-size:12px; color:#858C96");
}

void ChapterNameWidget::setAdjustChapterLabel()
{
    if (!m_changeChapterLabel) {
        m_changeChapterLabel = new QLabel(this);
    }

    m_changeChapterLabel->setText(QString::fromLocal8Bit("已调讲"));
    m_changeChapterLabel->setStyleSheet("border-radius:2px; \
                                        border:1px solid; \
                                        font-size:12px; \
                                        color:#60637E;\
                                        border-color:#60637E;");

   m_changeChapterLabel->setFixedSize(41, 16);
}

void ChapterNameWidget::setEnglishTitle(QString name)
{
    if (!m_nameLabel) {
        m_nameLabel = new QLabel(this);
    }

    m_nameLabel->setText(name);
    m_nameLabel->setStyleSheet("font-size:16px; font-weight:bold;color:#858C96;");
    m_vbLayout->addWidget(m_nameLabel);
}