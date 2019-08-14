#ifndef ROUNDMOVIEWIDGET_H
#define ROUNDMOVIEWIDGET_H

#include <QWidget>
#include <QTimeLine>

class RoundMovieWidget : public QWidget
{
    Q_OBJECT
public:
    RoundMovieWidget(QWidget *parent = 0);

    void setPixmap(const QPixmap &pix);
    void startMovie();
    void stopMovie();
    void setRadius(int radius);
    void setBorderColor(QColor color);

protected:
    void paintEvent(QPaintEvent *e);

private slots:
    void onFrameChanged(int frame);

private:
    QPixmap m_pix;
    QTimeLine m_timeLine;
    int m_angle;
    int m_radius;
    QColor m_borderColor;
};

#endif // ROUNDMOVIEWIDGET_H
