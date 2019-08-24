#include "StackDownload.h"
#include "ui_StackDownload.h"
#include "RoundProgressBar.h"
StackDownload::StackDownload(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackDownload)
{
#ifdef Q_OS_MAC
    setWindowFlag(Qt::NoDropShadowWindowHint);
#endif
    setAttribute(Qt::WA_TranslucentBackground);

    ui->setupUi(this);
    initDownPage();
    initProgressBarPage();
    initOpenFilePage();
}

StackDownload::~StackDownload()
{
    delete ui;
}

void StackDownload::initDownPage()
{
    ui->downBtn->setStyleSheet("QPushButton{border-image:url(:/res/icon_arrow_download.png);}"
                                "QPushButton:hover {border-image:url(:/res/icon_arrow_download_hover.png);}");

    ui->downBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->stackedWidget->setCurrentIndex(0);
    update();
}

void StackDownload::initProgressBarPage()
{
    ui->progressBar->setPresent(0);
}

void StackDownload::initOpenFilePage()
{
    ui->openBtn->setText(QString::fromLocal8Bit("打开"));
    ui->openBtn->setFixedSize(56, 24);
    ui->openBtn->setStyleSheet("border-radius:12px; border:1px solid rgba(255,94,80,1); font-size:12px; color:rgba(255,94,80,1);");
    ui->openBtn->setCursor(QCursor(Qt::PointingHandCursor));
    update();
}

void StackDownload::setProgressValue(int value)
{
    ui->progressBar->setPresent(value);
    if (value == 100) {
        ui->stackedWidget->setCurrentIndex(1);
    }
    update();
}

void StackDownload::on_downBtn_clicked()
{
    // 进度条页面
    ui->stackedWidget->setCurrentIndex(2);

    emit fileDownload();
}

void StackDownload::onProgressFinished()
{
    initOpenFilePage();
    ui->stackedWidget->setCurrentIndex(1);
    update();
}

void StackDownload::on_openBtn_clicked()
{
    emit openFile();
}
