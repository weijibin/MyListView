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
private:
    DateListWidget * m_dateListWidget = nullptr;
    CardListWidget * m_cardList = nullptr;
};

#endif // CLASSLISTWIDGET_H
