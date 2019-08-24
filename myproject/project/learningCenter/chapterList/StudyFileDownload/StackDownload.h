#ifndef STACKDOWNLOAD_H
#define STACKDOWNLOAD_H

#include <QWidget>

namespace Ui {
class StackDownload;
}

class StackDownload : public QWidget
{
    Q_OBJECT

public:
    explicit StackDownload(QWidget *parent = nullptr);
    ~StackDownload();

    void initDownPage();
    void initProgressBarPage();
    void initOpenFilePage();
    void setProgressValue(int value);

signals:

    void fileDownload();
    void openFile();

private slots:
    void on_downBtn_clicked();
    void onProgressFinished();


    void on_openBtn_clicked();

private:
    Ui::StackDownload *ui;
};

#endif // STACKDOWNLOAD_H
