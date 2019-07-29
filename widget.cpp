#include "widget.h"
#include "ui_widget.h"
#include "chapterlist/chapterlistwidget.h"
#include "classlist/classlistwidget.h"
#include "date/DateListWidget.h"
#include "courselist/courselistwidget.h"

#include <QFile>
#include <QDebug>
#include <QDate>

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
    DateListWidget *w = new DateListWidget();

    QFile f(":/qss/style.qss");
    if (f.open(QFile::ReadOnly)) {
        QByteArray a_qss(std::move(f.readAll()));
        f.close();
        w->setStyleSheet(a_qss);
    }

    connect(w,&DateListWidget::sigSelectedDate,[=](const QDate&date){
        qDebug()<<"selected Date==========="<<date.toString();
    });

    w->show();
    w->updateScrollArea();
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
