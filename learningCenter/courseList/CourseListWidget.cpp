#include "CourseListWidget.h"
#include <QPushButton>
#include "InterMediaCtrl.h"

CourseListWidget::CourseListWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    initUi();
}

void CourseListWidget::initUi()
{
    QPushButton * btn = new QPushButton(this);
    btn->move(100,100);

    btn->setText("CourseListWidget");

    connect(btn,&QPushButton::clicked,[=](){
        InterMediaCtrl::GetInstance().changeToChapterMode();
    });
}
