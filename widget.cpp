#include "widget.h"
#include "ui_widget.h"
#include "chapterlist/ChapterListWidget.h"
#include "classlist/ClassListWidget.h"
#include "date/DateListWidget.h"
#include "courselist/CourseListWidget.h"

#include "title/TitleWidget.h"

#include "LearningCenterWidget.h"
#include "InterMediaCtrl.h"

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
    ClassListWidget *w = new ClassListWidget();
}

void Widget::on_courseBtn_clicked()
{

}

void Widget::on_chapterBtn_clicked()
{

}

void Widget::on_pushButton_clicked()
{
    if(m_center == nullptr)
    {
        m_center = new LearningCenterWidget;
        m_center->resize(900,600);
        InterMediaCtrl::GetInstance().setCenterWidget(m_center);

        QFile f(":/qss/style.qss");
        if (f.open(QFile::ReadOnly)) {
            QByteArray a_qss(std::move(f.readAll()));
            f.close();
            m_center->setStyleSheet(a_qss);
        }
    }
    m_center->show();
}
