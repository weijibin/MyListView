#ifndef ROUNDPROGRESSBAR_H
#define ROUNDPROGRESSBAR_H

#include <QObject>
#include <QWidget>

class RoundProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit RoundProgressBar(QWidget *parent = nullptr);

    void setRotateDelta(int delta);
    void setPresent(int present);

signals:


public slots:

protected:
     void paintEvent(QPaintEvent *);

private:
     int m_rorateAngle;
     int m_present;
     int m_border;
};

#endif // ROUNDPROGRESSBAR_H
