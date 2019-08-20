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

    // interact
    void updateUiByDate(const QDate& date);

signals:
    void sigCurCardDate(const QDate& date);
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

    void updateLeftAndRightVisible();

    void removeNoClassCard();

    void updateUiByCardInfos(int curIndex);

private:
    QScrollArea * m_area;
    QWidget * m_scrolWidget;
    QHBoxLayout * m_scrolLayout;

    QList<CardWidget*> m_cardList;
    QList<ClassCardInfo> m_cardInfos;


    QPushButton * m_leftBtn = nullptr;
    QPushButton * m_rightBtn = nullptr;

    int m_cardTotalCount;
    int m_cardVisibleNum;

    int m_cardCurIndex = -1;

    int m_cardWidth;
    int m_cardHeight;
    int m_aniDuration;

    int m_noClassIndex = -1;

    int m_requestLeftDataNum = 0;
};

#endif // CARDLISTWIDGET_H
