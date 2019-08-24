#include "ChapterWidget.h"
#include "title/ChapterTitle.h"
#include "chapterList/ChapterListWidget.h"
#include "chapterList/CefViewWidget.h"
#include "dataCenter/DataProvider.h"
#include "chapterList/StudyFileDownload/StudyFilesListWidget.h"
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QDebug>

ChapterWidget::ChapterWidget(QWidget *parent)
    : QWidget(parent)
    , m_studyWidgetOpen(false)
{
    initUI();
}

void ChapterWidget::initUI()
{
    m_title = new ChapterTitle(this);
    m_title->setObjectName("chapterTitle");
    connect(m_title, SIGNAL(StudyFileClicked()), this, SLOT(onShowStudyFileWidget()));
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

void ChapterWidget::refresh()
{
    if(m_stackedLayout->currentIndex() == Chapter)
    {
//        m_chapterList
    }
}


void ChapterWidget::onInitShowStudyFileWidget()
{
    // 显示窗口
    QList<MaterialUnit> m_fileList;
    for (int i = 0; i < 10; i++) {
        MaterialUnit unit;
        unit.isDir = true;
        unit.title = QString::fromLocal8Bit("春季小小加油站合集");
        unit.uploadTime = "2019.04.04 12:22:50";
        for (int j = 0; j < 4; j++) {
            MaterialInfo info;
            info.name = QString::fromLocal8Bit("全等三角型中考题");
            info.uploadTime = "2019.04.04 12:22:50";
            info.status = 0;
            unit.lst.append(info);
        }
        m_fileList.append(unit);
    }

    m_studyFileWidget = new StudyFilesListWidget(this);
    m_studyFileWidget->setFilesContents(m_fileList);
    QPoint p = mapToGlobal(QPoint(0,0));
    m_studyFileWidget->move(p.x() +m_chapterList->x() + width() - m_studyFileWidget->width(), p.y()+m_chapterList->y());
    m_studyFileWidget->show();
    qDebug() << "init studty file first!";
}

void ChapterWidget::onShowStudyFileWidget()
{
    m_studyWidgetOpen = !m_studyWidgetOpen;
    // 请求 数据
    qDebug() << "studyFile Clicked!!!" << m_courseInfo.stuCouID;
    if (!m_studyFileWidget) {
        onInitShowStudyFileWidget();
    } else {

//        if (!m_studyFileWidget->isVisible()) {
            m_studyFileWidget->show();
//            qDebug() << "study widget --->show";
//        } else {
//            m_studyFileWidget->hide();
//             qDebug() << "study widget --->hide";
//        }
    }
}
