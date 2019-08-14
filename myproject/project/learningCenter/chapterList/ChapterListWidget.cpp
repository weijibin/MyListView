#include "ChapterListWidget.h"
#include <QPushButton>
#include "InterMediaCtrl.h"

ChapterListWidget::ChapterListWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    initUi();
    initConnections();
}

void ChapterListWidget::initUi()
{
    QPushButton * btn = new QPushButton(this);
    btn->move(100,100);

    btn->setText("ChapterListWidget");

    QPushButton * btn1 = new QPushButton(this);
    btn1->move(300,100);

    btn1->setText(QStringLiteral("编程课"));

    connect(btn1,&QPushButton::clicked,[=](){
        InterMediaCtrl::GetInstance().changeToCefModel();
    });

}

void ChapterListWidget::initConnections()
{

}
