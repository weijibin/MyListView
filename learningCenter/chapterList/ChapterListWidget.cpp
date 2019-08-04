#include "ChapterListWidget.h"
#include <QPushButton>
#include "InterMediaCtrl.h"

ChapterListWidget::ChapterListWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    initUi();
}

void ChapterListWidget::initUi()
{
    QPushButton * btn = new QPushButton(this);
    btn->move(100,100);

    btn->setText("ChapterListWidget");

}
