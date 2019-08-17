#include "ChapterWidget.h"
#include "title/ChapterTitle.h"
#include "chapterList/ChapterListWidget.h"
#include "chapterList/CefViewWidget.h"
#include "dataCenter/DataProvider.h"

#include <QVBoxLayout>
#include <QStackedLayout>
#include <QDebug>

ChapterWidget::ChapterWidget(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void ChapterWidget::initUI()
{
    m_title = new ChapterTitle(this);
    m_title->setObjectName("chapterTitle");
    m_chapterList = new ChapterListWidget(this);

    m_cefViewWidget = new CefViewWidget(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_title);

    m_stackedLayout = new QStackedLayout;
    m_stackedLayout->addWidget(m_chapterList);
    m_stackedLayout->addWidget(m_cefViewWidget);


    mainLayout->addLayout(m_stackedLayout);


//    mainLayout->addWidget(m_chapterList);

    mainLayout->setSpacing(0);
    this->setContentsMargins(0,0,0,0);
    mainLayout->setContentsMargins(0,0,0,0);

    setLayout(mainLayout);

    m_stackedLayout->setCurrentIndex(Chapter);
}

void ChapterWidget::setOuterWidget(QWidget *w)
{
    m_title->setOuterWidget(w);
}

void ChapterWidget::changeToCefView()
{
    if(m_stackedLayout != nullptr)
    {
        m_stackedLayout->setCurrentIndex(CefView);
    }
}


void ChapterWidget::changeToChapter()
{
    if(m_stackedLayout != nullptr)
    {
        m_stackedLayout->setCurrentIndex(Chapter);
    }
}

void ChapterWidget::setCourseInfo(const CourseToChapterPar & par)
{
    m_courseInfo = par;
    qDebug()<<m_courseInfo.courseName;
    m_title->setCourseName(m_courseInfo.courseName);

    int ret = DataProvider::GetInstance().requestChapterList(par,m_chapterInfoList);
    qDebug() << "ret :" << ret << m_chapterInfoList.size() << " " << m_chapterInfoList.at(0).teachers.at(0).imgUrl;
    m_chapterList->setChapterListContents(m_chapterInfoList, m_courseInfo.deadLine);

}
