#include "StudyFilesListWidget.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QGraphicsDropShadowEffect>
#include <QStackedWidget>
#include "StudyDirWidget.h"
#include "StudyFileItem.h"
#include "learningCenter/dataCenter/DataProvider.h"

StudyFilesListWidget::StudyFilesListWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::Popup);
    setFixedWidth(592);
    setStyleSheet("background-color: #ffffff;");

    initUi();
//    DataProvider::GetInstance().setParentWidget(this);
}

void StudyFilesListWidget::setFilesContents(QList<MaterialUnit> list)
{
    clearContents();
    for(int i = 0; i < list.size(); i++) {
        if (list.at(i).isDir) {
            StudyDirWidget *dirFile = new StudyDirWidget(this);
            dirFile->setStuDirContents(list.at(i));
            m_scrollLayout->addWidget(dirFile);
            m_dirList.append(dirFile);

        } else {
            StudyFileItem *item = new StudyFileItem(this);
            item->setStudyFileContent(list.at(i).lst.first());
            m_scrollLayout->addWidget(item);
            m_fileList.append(item);
        }
    }
    adjustSize();
    update();
    show();

}

void StudyFilesListWidget::initUi()
{
    m_scrollWidget =new QScrollArea(this);
    m_scrollWidget->setWidgetResizable(true);
    m_scrollWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollWidget->setStyleSheet("background:transparent; border: 0 transparent;");
    m_scrollWidget->verticalScrollBar()->setStyleSheet(SCROLLBAR_CSS);
    setMinimumSize(592, 664);

    m_widget = new QWidget(this);
    m_widget->setMinimumWidth(544);
    m_scrollLayout = new QVBoxLayout();
    m_scrollLayout->setContentsMargins(0,0,20,0);
    m_scrollLayout->setSpacing(0);
    m_widget->setLayout(m_scrollLayout);

    m_scrollWidget->setWidget(m_widget);

    m_hLayout = new QHBoxLayout();
    m_hLayout->setContentsMargins(24, 0, 4, 0);
    m_hLayout->setSpacing(0);
    m_hLayout->addWidget(m_scrollWidget);
    setLayout(m_hLayout);

//    QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect(this);
//    dse->setBlurRadius(20);
//    dse->setColor(QColor(0, 0, 0, 6));
//    dse->setOffset(-20, 0);
//    setGraphicsEffect(dse);

    // init stackWidget
//    m_stackWidget = new QStackedWidget(this);

//    m_otherWidget = new QWidget(this);

    adjustSize();
}

void StudyFilesListWidget::clearContents()
{
    StudyFileItem *item = nullptr;
    StudyDirWidget *dir = nullptr;
    while (m_fileList.size() > 0) {
        item = m_fileList.takeFirst();
        m_scrollLayout->removeWidget(item);
        delete item;
        item = nullptr;
    }
    m_fileList.clear();

    while (m_dirList.size() > 0) {
        dir = m_dirList.takeFirst();
        m_scrollLayout->removeWidget(dir);
        delete dir;
        dir = nullptr;
    }
    m_dirList.clear();
}
