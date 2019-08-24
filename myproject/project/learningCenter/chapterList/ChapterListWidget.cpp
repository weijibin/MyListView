#include "ChapterListWidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include "InterMediaCtrl.h"
#include "ChapterItem.h"
#include <QDebug>
#include <QStyleOption>
#include <QPainter>
#include <QScrollBar>

ChapterListWidget::ChapterListWidget(QWidget *parent)
    : QWidget(parent)
    , m_endLabel(nullptr)
    , m_chapterScroll(nullptr)
    , m_scrollWidget(nullptr)
    , m_vbLayout(nullptr)
    , m_scrollLayout(nullptr)

{
#ifdef Q_OS_MAC
    setWindowFlag(Qt::NoDropShadowWindowHint);
#endif
    //setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    initUi();
    initConnections();
    setStyleSheet("background:rgba(255,255,255,1);");
}

ChapterListWidget::~ChapterListWidget()
{
    clearAllContens();
    delete m_chapterScroll;
    m_chapterScroll = nullptr;
    delete m_scrollWidget;
    m_scrollWidget = nullptr;
}

void ChapterListWidget::setChapterListContents(const QList<ChapterInfo> &list, const QString &validTime)
{
    clearAllContens();
    for (int i = 0; i <list.size(); i++) {
        ChapterItem *item = new ChapterItem(this);
        item->setChapterItemContents(list.at(i));

        m_chapterInfoList.append(list.at(i));
        m_chapterItemList.append(item);
        m_scrollLayout->addWidget(item);
    }

    // init end label
    m_endLabel = new QLabel(this);
    QString vTime = QString::fromLocal8Bit("课程有效期至: ");
    vTime.append(validTime);
    m_endLabel->setText(vTime);
    m_endLabel->setAlignment(Qt::AlignCenter);
    m_endLabel->setStyleSheet("font-size:12px; font-family:Microsoft YaHei; color:#858C96;");
    m_endLabel->setFixedHeight(64);
    m_scrollLayout->addWidget(m_endLabel);
    adjustSize();
    show();

}

void ChapterListWidget::clearAllContens()
{
    if (m_chapterItemList.size() == 0) {
        return ;
    }

    while (m_chapterItemList.size()>0) {

        ChapterItem *item = m_chapterItemList.first();
        m_vbLayout->removeWidget(item);
        m_chapterItemList.removeFirst();
        m_chapterInfoList.removeFirst();
        delete  item;
        item = nullptr;
    }
    m_chapterInfoList.clear();
    m_chapterItemList.clear();
    m_vbLayout->removeWidget(m_endLabel);
    delete m_endLabel;
    m_endLabel = nullptr;

}

void ChapterListWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ChapterListWidget::initUi()
{
    m_chapterScroll = new QScrollArea(this);
    m_chapterScroll->setWidgetResizable(true);
    m_chapterScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_chapterScroll->verticalScrollBar()->setStyleSheet(SCROLLBAR_CSS);
    m_chapterScroll->setStyleSheet("background:transparent; border: 0 transparent;");
    setMinimumSize(1280, 664);

    m_scrollWidget = new QWidget(this);
    m_scrollWidget->setMinimumWidth(1270);

    m_scrollLayout = new QVBoxLayout(m_scrollWidget);
    m_scrollLayout->setContentsMargins(0,0,0,0);
    m_scrollLayout->setSpacing(0);
    m_scrollWidget->setLayout(m_scrollLayout);

    m_chapterScroll->setWidget(m_scrollWidget);

    m_vbLayout = new QVBoxLayout(this);
    m_vbLayout->setContentsMargins(0,0,4,0);
    m_vbLayout->setSpacing(0);
    m_vbLayout->addWidget(m_chapterScroll);
    setLayout(m_vbLayout);
    adjustSize();
}

void ChapterListWidget::initConnections()
{

}
