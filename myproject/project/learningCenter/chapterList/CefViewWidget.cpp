#include "CefViewWidget.h"

#include <QPushButton>
#include <QLabel>
#include "InterMediaCtrl.h"


CefViewWidget::CefViewWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);

    QLabel* label = new QLabel(this);
    label->setText("Ceffffff VVVView  Window");

    label->move(100,100);

    QPushButton * btn = new QPushButton(this);
    btn->setText("BackToChapterList");
    btn->move(300,200);

    connect(btn,&QPushButton::clicked,[=](){
        InterMediaCtrl::GetInstance().changeToChapterModeFromCef();
    });
}
