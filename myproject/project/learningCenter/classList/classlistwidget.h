#ifndef CLASSLISTWIDGET_H
#define CLASSLISTWIDGET_H

#include <QWidget>

class DateListWidget;
class CardListWidget;

class ClassListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClassListWidget(QWidget *parent = 0);

signals:

public slots:
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
private:
    void initUi();

    QSize getCardListSize(const QSize &size);
private:
    DateListWidget * m_dateListWidget = nullptr;
    CardListWidget * m_cardList = nullptr;

    QSize m_initCardListSize;
    QSize m_cardListMaxSize;
};

#endif // CLASSLISTWIDGET_H
