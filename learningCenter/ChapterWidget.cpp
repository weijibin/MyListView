#include "ChapterWidget.h"
#include "title/ChapterTitle.h"
#include "chapterList/ChapterListWidget.h"

#include <QVBoxLayout>

ChapterWidget::ChapterWidget(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void ChapterWidget::initUI()
{
    m_title = new ChapterTitle(this);
    m_title->setObjectName("chapterTitle");
    m_chapterList = new ChapterListWidget(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_title);
    mainLayout->addWidget(m_chapterList);

    this->setContentsMargins(0,0,0,0);
    mainLayout->setContentsMargins(0,0,0,0);


    setLayout(mainLayout);
}

void ChapterWidget::setOuterWidget(QWidget *w)
{
    m_title->setOuterWidget(w);
}
