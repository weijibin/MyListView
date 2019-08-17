#include "LoadingDlg.h"
#include <QVBoxLayout>

LoadingDlg::LoadingDlg(QWidget *parent) :QDialog(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    initUi();
}

LoadingDlg::~LoadingDlg()
{

}

void LoadingDlg::initUi()
{
    this->setContentsMargins(0,0,0,0);
    QVBoxLayout * layout = new QVBoxLayout(this);
    m_label = new QLabel(this);
    layout->addWidget(m_label);

    this->setLayout(layout);

    QMovie *movie = new QMovie(":/res/loading1.gif");
    movie->setScaledSize(QSize(100,100));
    m_label->setMovie(movie);
    movie->start();

//    int frmX = width();
//    int frmY = height();

//    QDesktopWidget w;
//    int deskWidth = w.width();
//    int deskHeight = w.height();

//    QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
//    move(movePoint);

}
