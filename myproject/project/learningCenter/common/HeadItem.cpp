#include "HeadItem.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "RoundMovieWidget.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QCryptographicHash>
#include <QNetworkReply>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
HeadItem::HeadItem(QWidget *parent)
    : QWidget(parent)
{
    initUi();
}

HeadItem::~HeadItem()
{

}

void HeadItem::initUi()
{
    m_roundWidget = new RoundMovieWidget(this);
    m_roundWidget->setFixedSize(32, 32);
    m_roundWidget->setRadius(0);

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

void HeadItem::setHeadInfo(const QString &pixPath, int type, const QString &teacherName)
{
    setHeadPixmap(pixPath);
    QString teacherType = QString::fromLocal8Bit("主讲");
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

void HeadItem::setHeadPixmap(const QString &pixPath, int radius)
{
    m_roundWidget->setPixmap(QPixmap(":/res/default_boy_img.png").scaled(m_roundWidget->width(), m_roundWidget->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    downloadImg(pixPath);
    m_roundWidget->update();
}

void HeadItem::setHeadText(const QString &type,const QString &teacherName)
{
    m_typeLabel->setText(type);
    m_nameLabel->setText(teacherName);
    m_typeLabel->setStyleSheet("font-size:12px; font-family:Microsoft YaHei;color:#858C96;");
    m_nameLabel->setStyleSheet("font-size:12px; font-family:Microsoft YaHei; color:#858C96;");
}

void HeadItem::downloadImg(const QString &url)
{
    if (url.isEmpty()) {
        m_roundWidget->setPixmap(QPixmap(":/res/default_boy_img.png").scaled(m_roundWidget->width(), m_roundWidget->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    } else {
        QString filename = QCryptographicHash::hash(url.toUtf8(), QCryptographicHash::Md5).toHex();
        QString path = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/xes_imgCache/" + filename + ".png";

        if (QFile::exists(path)) {
            m_roundWidget->setPixmap(QPixmap(path).scaled(m_roundWidget->width(), m_roundWidget->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        } else {
            QNetworkReply *headImage = m_networkAccess.get(QNetworkRequest(QUrl(url)));
            headImage->setProperty("filename", filename);
            connect(headImage, SIGNAL(finished()), this, SLOT(onHeadImg()));
        }
    }
}

void HeadItem::onHeadImg()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply *> (sender());
    if (!reply) {
        return;
    }
    reply->deleteLater();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray array = reply->readAll();
        QImage image = QImage::fromData(array);
        QPixmap scaledPixmap = QPixmap::fromImage(image);
        scaledPixmap = scaledPixmap.scaled(m_roundWidget->width(), m_roundWidget->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        m_roundWidget->setPixmap(scaledPixmap);

        QString filename = reply->property("filename").toString();
        QString path = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/xes_imgCache/";
        QDir d;
        if (d.mkdir(path)) {
            path = path + filename + ".png";
        } else {
            if (d.exists(path)) {
                qDebug() << "dir exists.";
                path = path + filename + ".png";
            } else {
                qDebug() << "create dir: " << path << " failed.";
                return;
            }
        }
        scaledPixmap.save(path);
    } else {
        m_roundWidget->setPixmap(QPixmap(":/res/default_boy_img.png").scaled(m_roundWidget->width(), m_roundWidget->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}

