#ifndef CARDLISTWIDGET_H
#define CARDLISTWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QHBoxLayout>
#include "common/common.h"
/**
 * @brief The CardListWidget class
 * 上课界面中的  课程卡片类
 */
class CardWidget;
class QPushButton;

class CardListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardListWidget(QWidget *parent = 0);

    void updateCardBySize(int w,int h);

    void updateScrollArea();

signals:

public slots:
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual bool eventFilter(QObject *obj, QEvent *ev) override;

    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

private slots:
    void onLeftClick();
    void onRightClick();

    void updateWidget_pre();
    void updateWidget_back();

    void updateLeftAndRightBtn();

private:
    void initUi();
    void initConnections();

    ClassCardInfo getCardInfo(int type);

private:
    QScrollArea * m_area;
    QWidget * m_scrolWidget;
    QHBoxLayout * m_scrolLayout;

    QList<CardWidget*> m_cardList;


    QPushButton * m_leftBtn = nullptr;
    QPushButton * m_rightBtn = nullptr;

    int m_cardTotalCount;
    int m_cardVisibleNum;
    int m_cardWidth;
    int m_cardHeight;
    int m_aniDuration;
};

#endif // CARDLISTWIDGET_H
