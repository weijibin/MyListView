#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
class QHBoxLayout;

class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = 0);

signals:

public slots:
protected:
    virtual void mousePressEvent(QMouseEvent*event) override;
    virtual void mouseMoveEvent(QMouseEvent*event) override;
    virtual void paintEvent(QPaintEvent *event) override;

protected:
    QHBoxLayout * m_layout;
    QPoint m_offset = QPoint();
};

#endif // TITLEWIDGET_H
