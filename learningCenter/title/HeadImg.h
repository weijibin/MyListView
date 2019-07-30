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
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    QPixmap m_pix;
    QPen    m_pen;
    QBrush  m_brush;
};

#endif // TEACHERHEADIMG_H
