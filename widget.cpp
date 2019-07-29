#include "widget.h"
#include "ui_widget.h"
#include "chapterlistwidget.h"
#include "classlistwidget.h"
#include "datelistwidget.h"
#include "courselistwidget.h"

#include <QFile>
#include <QDebug>
#include <QDate>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    QFile f(":/qss/style.qss");
//    if (f.open(QFile::ReadOnly)) {
//        QByteArray a_qss(std::move(f.readAll()));
//        f.close();
//        this->setStyleSheet(a_qss);
//    }
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

//    qDebug()<<f.errorString();

//    w->setStyleSheet("QWidget#weeklist > QPushButton{\
//                     border: none;\
//                     background-color: #f3f8ff;\
//                 }\
//                 QWidget#weeklist > QPushButton:hover{\
//                     border: none;\
//                     background-color: #00f8ff;\
//                 }\
//                 QWidget#weeklist > QPushButton:pressed{\
//                     border: none;\
//                     background-color: #f300ff;\
//                 }\
//                 QWidget#weeklist > QPushButton:checked{\
//                     border: none;\
//                     background-color: #f3f800;\
//                 }");

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
