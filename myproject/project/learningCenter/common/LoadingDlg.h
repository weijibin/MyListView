#ifndef LOADINGDLG_H
#define LOADINGDLG_H

#include <QDialog>
#include <QDesktopWidget>
#include <QMovie>
#include <QLabel>

class LoadingDlg : public QDialog
{
    Q_OBJECT
public:
    explicit LoadingDlg(QWidget *parent = nullptr);
    ~LoadingDlg();
private:
    void initUi();
private:
    QLabel * m_label = nullptr;
};

#endif // LOADINGDLG_H
