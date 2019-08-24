#include "HeadImg.h"
#include <QPainter>
#include <QPainterPath>
#include <QFont>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>

HeadImg::HeadImg(const QPixmap &map,QWidget*parent) : QWidget(parent)
{
    m_width = 28;

    m_pix = map.scaled(m_width,m_width,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    this->setFixedSize(m_width,m_width);

//    m_pen.setColor("#FB5E50");
//    m_brush.setColor(QColor("#FB5E50"));

//    m_brush.setStyle(Qt::SolidPattern);
//    m_pen.setWidth(2);
    m_catchDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/xesCache/";
}

void HeadImg::setImgUrl(QString img_url)
{
    m_imgName = img_url.mid(img_url.lastIndexOf("/") + 1);

    QFileInfo file(m_catchDir + m_imgName);
    bool isExist = file.exists();

    qDebug()<<"=====HeadImg::setImgUrl==========="<<m_catchDir<<m_imgName;
    if(isExist)
    {
        m_pix.load(m_catchDir+m_imgName);
    }
    else
    {
        setRemoteImg(img_url);
    }
}

void HeadImg::setRemoteImg(const QString &img_url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(QNetworkRequest(img_url));
    connect(reply, &QNetworkReply::finished, [this, reply, manager](){

        qDebug()<<"HeadImg::setRemoteImg ::: finish";
        qDebug()<<reply->error();
        manager->deleteLater();
        if (NULL == reply) {
            return;
        }

        if (reply->error() == QNetworkReply::NoError) {
            QByteArray bytes = reply->readAll();
            m_pix.loadFromData(bytes);

            m_pix.save(m_catchDir+m_imgName);
        }
        reply->deleteLater();
    });
}


void HeadImg::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing,true);


    painter.save();
    QPainterPath path;
    path.addEllipse(rect().center(),m_width/2,m_width/2);
    painter.setClipPath(path);
    painter.drawPixmap(rect(),m_pix);
    painter.restore();

//    painter.save();
//    painter.setPen(m_pen);
//    painter.drawEllipse(rect().center(),m_width/2,m_width/2);
//    painter.restore();

}
