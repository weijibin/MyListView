#include "StudyFileItem.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QPixmap>
#include <QWidget>
#include <QPainter>
#include <QStyleOption>

#include "StackDownload.h"

StudyFileItem::StudyFileItem(QWidget *parent)
    : QWidget(parent)
    , m_fileNameWidget(nullptr)
    , m_dateLabel(nullptr)
    , m_downloadWidget(nullptr)
    , m_hLayout(nullptr)
{

#ifdef Q_OS_MAC
    setWindowFlag(Qt::NoDropShadowWindowHint);
#endif
    setAttribute(Qt::WA_TranslucentBackground);

    initUi();
}

void StudyFileItem::setStudyFileContent(MaterialInfo info, bool isDir)
{
    m_fileInfo = info;
    m_fileNameWidget->setFileNameWidgetContent(info.name,isDir);
    m_dateLabel->setText(info.uploadTime);
    m_dateLabel->adjustSize();
    if (info.status == 0) {
        m_downloadWidget->initDownPage();
    } else {
        m_downloadWidget->initOpenFilePage();
    }
    adjustSize();
}

void StudyFileItem::initUi()
{
    m_fileNameWidget = new FileNameWidget(this);

    m_dateLabel = new QLabel(this);
    m_dateLabel->setMinimumSize(114, 15);
    m_dateLabel->setStyleSheet("font-size:12px; font-family:Microsoft YaHei; color:rgba(133,140,150);");

    m_downloadWidget = new StackDownload(this);
    m_hLayout = new QHBoxLayout(this);
    m_hLayout->addWidget(m_fileNameWidget);
    m_hLayout->addWidget(m_dateLabel);
    m_hLayout->addWidget(m_downloadWidget);
    m_hLayout->setContentsMargins(0,0,0,0);
    m_hLayout->setSpacing(24);
    setLayout(m_hLayout);
  //  setStyleSheet("border-bottom: 1px solid #000000;");
    adjustSize();
}

void StudyFileItem::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}



FileNameWidget::FileNameWidget(QWidget *parent)
    : QWidget(parent)
    , m_icon(nullptr)
    , m_fileNameLabel(nullptr)
{
    setFixedSize(326, 20);
    initUi();
}

FileNameWidget::~FileNameWidget()
{


}

void FileNameWidget::setDirFileNameContent(const QString &fileName)
{
    m_icon->setPixmap(QPixmap(":/res/icon_wenjianjia.png"));

    m_fileNameLabel->setText(fileName);
    m_hLayout->setContentsMargins(0,0,0,0);

    adjustSize();
}

void FileNameWidget::setFileNameWidgetContent(const QString &fileName, bool isDir)
{
    m_icon->setPixmap(QPixmap(":/res/icon_xuexiziliao_hover.png"));

    m_fileNameLabel->setText(fileName);

    if (isDir) {
        m_hLayout->setContentsMargins(24,0,0,0);

    } else {
        m_hLayout->setContentsMargins(0,0,0,0);
    }


    m_hLayout->update();
    adjustSize();
}

void FileNameWidget::initUi()
{
    m_icon = new QLabel(this);
    m_icon->setFixedSize(20, 20);

    m_fileNameLabel = new QLabel(this);
    m_fileNameLabel->setStyleSheet("font-size:14px;font-family:Microsoft YaHei;color:rgba(33,40,49,1);");

    m_hLayout = new QHBoxLayout(this);
    m_hLayout->addWidget(m_icon);
    m_hLayout->addWidget(m_fileNameLabel);
    m_hLayout->setSpacing(8);
    setLayout(m_hLayout);
    adjustSize();
}
