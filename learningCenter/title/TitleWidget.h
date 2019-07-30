#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
class QHBoxLayout;
class QPushButton;

class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = 0);

    void setOuterWidget(QWidget*w){m_outerWidget = w;}
signals:

public slots:
protected:
    void initUI();
    void initConnections();
protected:
    virtual void mousePressEvent(QMouseEvent*event) override;
    virtual void mouseMoveEvent(QMouseEvent*event) override;
    virtual void paintEvent(QPaintEvent *event) override;

protected:
    QHBoxLayout * m_layout = nullptr;
    QPoint m_offset = QPoint();

    QPushButton * m_menu = nullptr;
    QPushButton * m_minBtn = nullptr;
    QPushButton * m_norBtn = nullptr;
    QPushButton * m_closeBtn = nullptr;

    QWidget * m_outerWidget = nullptr;
};

#endif // TITLEWIDGET_H
