#include "TitleWidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPushButton>
#include <QGraphicsBlurEffect>
#include <QLibrary>
#include <QPalette>
#include <QtWin>

#include <dwmapi.h>
// WARNING: disable -O2, or application will CRASH at startup!!
void setGlassEffect(QWidget *w)
{
    typedef HRESULT (STDAPICALLTYPE *enableBlurBehindWindow)(HWND, const DWM_BLURBEHIND *);
    typedef HRESULT (STDAPICALLTYPE *extendFrameIntoClientArea)(HWND, MARGINS *);
    enableBlurBehindWindow f1 =
        (enableBlurBehindWindow)QLibrary::resolve("dwmapi", "DwmEnableBlurBehindWindow");
    extendFrameIntoClientArea f2 =
        (extendFrameIntoClientArea)QLibrary::resolve("dwmapi", "DwmExtendFrameIntoClientArea");

    DWM_BLURBEHIND bb = {0};
//    MARGINS margins = {-1};
    MARGINS margins = {50,50,50,50};
    bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
    if(f1)f1(HWND(w->winId()), &bb);
    if(f2)f2(HWND(w->winId()), &margins);
}


//// 获取最终的模糊图像
//QImage getBlurImage()
//{
//    // 原图为 originImg
//    QImage originImg;
//    // 第一个方向处理的图像为tmpImg
//    QImage tmpImg;
//    // 经过第二次处理的最终结果newImg
//    QImage newImg;

//    // 在横向进行一次相加
//    for(int y=0;y<originImg.height();y++)
//    {
//        for(int x=0;x<originImg.width();x++)
//        {
//            double red=0,green=0,blue=0;
//            for(int i=-r; i<=r; i++)
//            {
//                // 边界处理后的对应的权值矩阵实际值
//                int inx = edge(x,i,width());

//                QColor rgb = QColor(originImgpixel(inx,y));
//                red+=rgb.red()*weight[r+i];
//                green+=rgb.green()*weight[r+i];
//                blue+=rgb.blue()*weight[r+i];
//            }
//            tmpImg.setPixel(x,y,qRgb(red,green,blue));
//        }
//    }
//    // 在纵方向对第一次的结果重新进行一次
//    for(int y=0;y<tmpImg.height();y++)
//    {
//        for(int x=0;x<tmpImg.width();x++)
//        {
//            double red=0,green=0,blue=0;
//            for(int i=-r; i<=r; i++)
//            {
//                int iny = edge(y,i,height());

//                QColor rgb = QColor(tmpImg.pixel(x,iny));
//                red+=rgb.red()*weight[r+i];
//                green+=rgb.green()*weight[r+i];
//                blue+=rgb.blue()*weight[r+i];
//            }
//            newImg.setPixel(x,y,qRgb(red,green,blue));
//        }
//    }
//    return newImg;
//}

TitleWidget::TitleWidget(QWidget *parent) : QWidget(parent)
{
    m_btnSize = QSize(20,20);

    setFixedHeight(56);
    initUI();
    initConnections();

//    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect(this);
//    blurEffect->setBlurRadius(3);
//    blurEffect->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
//    this->setGraphicsEffect(blurEffect);

//    setGlassEffect(this);

}

void TitleWidget::initUI()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setSpacing(5);
    m_minBtn = new QPushButton(this);
    m_minBtn->setObjectName("l_min");
    m_norBtn = new QPushButton(this);
    m_norBtn->setObjectName("l_nor");
    m_closeBtn = new QPushButton(this);
    m_closeBtn->setObjectName("l_close");
    m_updateBtn = new QPushButton(this);
    m_updateBtn->setObjectName("l_update");

    m_minBtn->setFixedSize(m_btnSize);
    m_norBtn->setFixedSize(m_btnSize);
    m_closeBtn->setFixedSize(m_btnSize);
    m_updateBtn->setFixedSize(m_btnSize);

#if defined(Q_OS_WIN)
    m_layout->addWidget(m_updateBtn);
    m_layout->addWidget(m_minBtn);
    m_layout->addWidget(m_norBtn);
    m_layout->addWidget(m_closeBtn);
#else
    m_layout->addWidget(m_closeBtn);
    m_layout->addWidget(m_minBtn);
    m_layout->addWidget(m_norBtn);
#endif
    setLayout(m_layout);
}

void TitleWidget::initConnections()
{
    connect(m_minBtn,&QPushButton::clicked,[=](){
        if(m_outerWidget != nullptr)
        {
            m_outerWidget->showMinimized();
        }
    });
    connect(m_norBtn,&QPushButton::clicked,[=](){
        if(m_outerWidget != nullptr)
        {
            if(m_outerWidget->isMaximized())
            {
                m_outerWidget->showNormal();
            }
            else
            {
                m_outerWidget->showMaximized();
            }
        }
    });
    connect(m_closeBtn,&QPushButton::clicked,[=](){
        if(m_outerWidget != nullptr)
        {
            m_outerWidget->close();
        }
    });
}

void TitleWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        m_isPressed = true;
        m_offset = event->globalPos() - m_outerWidget->frameGeometry().topLeft();
        event->accept();
    }
}

void TitleWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        if(m_isPressed)
        {
            m_outerWidget->move(event->globalPos() - m_offset);
            event->accept();
        }
    }
}

void TitleWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
}

void TitleWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

//    p.drawPixmap(this->rect(),QPixmap());

//    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
//    p.fillRect(rect(), QColor(0, 0, 0, 0));

//    QPainter p(this);
//    p.setCompositionMode(QPainter::CompositionMode_DestinationIn); //it's necessary!
//    QColor backgroundColor = palette().light().color();
//    backgroundColor.setAlpha(0.8);
//    p.fillRect(this->rect(), backgroundColor); //the RGB color is not the point, the alpha value is.
}
