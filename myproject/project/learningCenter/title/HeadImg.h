#ifndef HEADIMG_H
#define HEADIMG_H

#include <QWidget>
#include <QPixmap>
#include <QPen>

class HeadImg : public QWidget
{
    Q_OBJECT
public:
    HeadImg(const QPixmap &map,QWidget*parent = 0);
    void setImgUrl(QString url);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    void setRemoteImg(const QString & url);
private:
    QPixmap m_pix;
    QPen    m_pen;
    QBrush  m_brush;
    int m_width;

    QString m_imgName;
    QString m_catchDir;
};

#endif // TEACHERHEADIMG_H
