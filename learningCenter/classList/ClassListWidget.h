#ifndef CLASSLISTWIDGET_H
#define CLASSLISTWIDGET_H

#include <QWidget>

class DateListWidget;

class ClassListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClassListWidget(QWidget *parent = 0);

signals:

public slots:
private:
    void initUi();
private:
    DateListWidget * m_dateListWidget = nullptr;
    QWidget * m_cardList = nullptr;
};

#endif // CLASSLISTWIDGET_H
