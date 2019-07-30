#ifndef CARDLISTWIDGET_H
#define CARDLISTWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QHBoxLayout>

/**
 * @brief The CardListWidget class
 * 上课界面中的  课程卡片类
 */
class CardWidget;

class CardListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardListWidget(QWidget *parent = 0);

    void updateCardBySize(int w,int h);

signals:

public slots:
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual bool eventFilter(QObject *obj, QEvent *ev) override;
private:
    void initUi();

private:
    QScrollArea * m_area;
    QWidget * m_scrolWidget;
    QHBoxLayout * m_scrolLayout;

    QList<CardWidget*> m_cardList;

    int m_cardTotalCount;
    int m_cardVisibleNum;
    int m_cardWidth;
    int m_cardHeight;
    int m_aniDuration;
};

#endif // CARDLISTWIDGET_H
