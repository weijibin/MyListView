#include "CardWidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>;

CardWidget::CardWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);

    initUi();

//        QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect(this);
//        effect->setOffset(QPointF(5,5));
//        effect->setColor(Qt::black);
//        effect->setBlurRadius(2);
//        this->setGraphicsEffect(effect);
}

void CardWidget::initUi()
{
    QVBoxLayout * layout = new QVBoxLayout;

    m_card = new ClassCardWidget;

    {
        ClassTime time;
        time.day = QString::fromLocal8Bit("今日");
        time.startTime = "8:30";
        time.endTime = "18:30";
        time.index = 2;

        ClassCardInfo info;
        info.time = time;
        info.classStatusType = 1;
        info.classStatus = QString::fromLocal8Bit("直播进行中...");
        info.classTip = QString::fromLocal8Bit("记得去APP完成课清哦~");
        info.btnText = QString::fromLocal8Bit("去上课");
        info.chapterName = QString::fromLocal8Bit("第一讲 函数奇偶性与对称性");
        info.subjectName = QString::fromLocal8Bit("数学");
        info.courseName = QStringLiteral("【2019-暑】六年级初一数学直播菁英班（北京人教）");

        m_card->setClassInfo(info);
    }

    layout->addWidget(m_card);
    this->setLayout(layout);
}

void CardWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
