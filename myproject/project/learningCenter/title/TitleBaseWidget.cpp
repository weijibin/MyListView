#include "TitleBaseWidget.h"
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
#include "InterMediaCtrl.h"

TitleBaseWidget::TitleBaseWidget(QWidget *parent) : QWidget(parent)
{
    m_btnSize = QSize(20,20);

    setFixedHeight(56);
    initUI();
    initConnections();

//    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect(this);
//    blurEffect->setBlurRadius(3);
//    blurEffect->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
//    this->setGraphicsEffect(blurEffect);

}

void TitleBaseWidget::initUI()
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

void TitleBaseWidget::initConnections()
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

    connect(m_updateBtn,&QPushButton::clicked,[=](){
        InterMediaCtrl::GetInstance().refresh();
    });
}

void TitleBaseWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        m_isPressed = true;
        m_offset = event->globalPos() - m_outerWidget->frameGeometry().topLeft();
        event->accept();
    }
}

void TitleBaseWidget::mouseMoveEvent(QMouseEvent *event)
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

void TitleBaseWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
}

void TitleBaseWidget::paintEvent(QPaintEvent *)
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
