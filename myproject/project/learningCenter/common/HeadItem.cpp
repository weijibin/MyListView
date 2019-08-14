#include "HeadItem.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "RoundMovieWidget.h"

HeadItem::HeadItem(QWidget *parent) :
    QWidget(parent)
{

    initUi();
}

HeadItem::~HeadItem()
{

}

void HeadItem::initUi()
{
    m_roundWidget = new RoundMovieWidget(this);

    m_typeLabel = new QLabel(this);

    m_nameLabel = new QLabel(this);

    m_vLayout = new QVBoxLayout;
    m_vLayout->setContentsMargins(0,0,0,0);
    m_vLayout->setSpacing(0);
    m_vLayout->addWidget(m_typeLabel);
    m_vLayout->addWidget(m_nameLabel);

    m_hLayout = new QHBoxLayout(this);
    m_hLayout->setContentsMargins(0,0,0,0);
    m_hLayout->setSpacing(8);
    m_hLayout->addWidget(m_roundWidget);
    m_hLayout->addLayout(m_vLayout);

    setFixedSize(100, 32);

}

void HeadItem::setHeadInfo(QString pixPath, int type, QString teacherName)
{
    setHeadPixmap(pixPath);
    QString teacherType = "主讲";
    if (1 == type) {
        teacherType = QString::fromLocal8Bit("主讲");
    } else if (4 == type) {
        teacherType = QString::fromLocal8Bit("辅导");
    } else if (5 == type) {
        teacherType = QString::fromLocal8Bit("外教");
    } else if (7 == type) {
        teacherType = QString::fromLocal8Bit("专属");
    } else {
        teacherType = QString::fromLocal8Bit("主讲");
    }

    setHeadText(teacherType, teacherName);
}

void HeadItem::setHeadPixmap(QString pixPath, int radius)
{
    m_roundWidget->setPixmap(QPixmap(pixPath).scaled(radius, radius, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_roundWidget->setRadius(0);
    m_roundWidget->setFixedSize(radius, radius);
    setFixedSize(100, 32);
}

void HeadItem::setHeadText(QString type, QString teacherName)
{
    m_typeLabel->setText(type);
    m_nameLabel->setText(teacherName);
    m_typeLabel->setStyleSheet("font-size:12px;color:#858C96;");
    m_nameLabel->setStyleSheet("font-size:12px;color:#858C96;");
}
