#include "TitleWidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPushButton>
#include <QGraphicsBlurEffect>

TitleWidget::TitleWidget(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(56);
    initUI();
    initConnections();

//    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect(this);
//    blurEffect->setBlurRadius(3);
//    blurEffect->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
//    this->setGraphicsEffect(blurEffect);

}

void TitleWidget::initUI()
{
    m_layout = new QHBoxLayout(this);

    m_menu = new QPushButton(this);
    m_minBtn = new QPushButton(this);
    m_norBtn = new QPushButton(this);
    m_closeBtn = new QPushButton(this);

    m_layout->addStretch();

    m_layout->addWidget(m_menu);
    m_layout->addWidget(m_minBtn);
    m_layout->addWidget(m_norBtn);
    m_layout->addWidget(m_closeBtn);


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
        m_offset = event->globalPos() - m_outerWidget->frameGeometry().topLeft();
        event->accept();
    }
}

void TitleWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        m_outerWidget->move(event->globalPos() - m_offset);
        event->accept();
    }
}

void TitleWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
