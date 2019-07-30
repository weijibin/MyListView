#include "ClassListWidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "date/DateListWidget.h"

ClassListWidget::ClassListWidget(QWidget *parent) : QWidget(parent)
{
    initUi();
}

void ClassListWidget::initUi()
{
    setContentsMargins(0,0,0,0);
    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);


    m_dateListWidget = new DateListWidget(this);
    m_dateListWidget->setFixedHeight(50);


    m_cardList = new QWidget(this);

    layout->addWidget(m_dateListWidget);
    layout->addWidget(m_cardList);
    layout->addStretch();

    setLayout(layout);

    m_dateListWidget->updateScrollArea();
}
