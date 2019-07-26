#include "datewidget.h"
#include "ui_datewidget.h"

DateWidget::DateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateWidget)
{
    ui->setupUi(this);
    static int  num = 0;

    ui->pushButton->setText(QString::number(num++));
}

QString DateWidget::text()
{
    return ui->pushButton->text();
}

DateWidget::~DateWidget()
{
    delete ui;
}
