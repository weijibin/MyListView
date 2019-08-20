#ifndef TITLEBASEWIDGET_H
#define TITLEBASEWIDGET_H

#include <QWidget>
class QHBoxLayout;
class QPushButton;

class TitleBaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBaseWidget(QWidget *parent = 0);

    void setOuterWidget(QWidget*w){m_outerWidget = w;}
signals:

public slots:
protected:
    void initUI();
    void initConnections();
protected:
    virtual void mousePressEvent(QMouseEvent*event) override;
    virtual void mouseMoveEvent(QMouseEvent*event) override;
    virtual void mouseReleaseEvent(QMouseEvent*event) override;
    virtual void paintEvent(QPaintEvent *event) override;

protected:
    QHBoxLayout * m_layout = nullptr;
    QPoint m_offset = QPoint();
    bool m_isPressed = false;

    QPushButton * m_minBtn = nullptr;
    QPushButton * m_norBtn = nullptr;
    QPushButton * m_closeBtn = nullptr;
    QPushButton * m_updateBtn = nullptr;

    QWidget * m_outerWidget = nullptr;

    QSize m_btnSize;
};

#endif // TITLEBASEWIDGET_H
