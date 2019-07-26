#include "widget.h"
#include "ui_widget.h"
#include "chapterlistwidget.h"
#include "classlistwidget.h"
#include "datelistwidget.h"
#include "courselistwidget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_dateBtn_clicked()
{
    QWidget *w = new DateListWidget();
    w->show();
}

void Widget::on_classBtn_clicked()
{

}

void Widget::on_courseBtn_clicked()
{

}

void Widget::on_chapterBtn_clicked()
{

}
