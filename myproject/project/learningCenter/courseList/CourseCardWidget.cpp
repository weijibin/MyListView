#include "CourseCardWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include "common/TeacherHeadWidget.h"
#include "InterMediaCtrl.h"

CourseCardWidget::CourseCardWidget(QWidget *parent) : QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    setAttribute(Qt::WA_TranslucentBackground);

    initUi();

    m_shadowX = m_shadowY = 3;
    setFixedSize(384+m_shadowY*2,174+m_shadowY*2);

    connect(this,SIGNAL(clicked()),this,SLOT(sltMouseClicked()));
}

void CourseCardWidget::initUi()
{
//    setContentsMargins((24+m_shadowY),(18+m_shadowY),(24+m_shadowY),(18+m_shadowY));
    setContentsMargins(27,21,27,21);

    QVBoxLayout * layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);

    QHBoxLayout * h_layout1 = new QHBoxLayout;
    h_layout1->setContentsMargins(0,0,0,0);

    m_subjectName = new QLabel(this);
    m_subjectName->setFixedHeight(16);
    m_subjectName->setObjectName("course_sub");
    m_subjectName->setContentsMargins(2,0,2,0);

    m_courseName = new QLabel(this);
    m_courseName->setObjectName("course_crs");
    m_courseName->setWordWrap(true);
    m_courseName->setAlignment(Qt::AlignTop);

    QVBoxLayout *v_1 = new QVBoxLayout;
    v_1->setContentsMargins(0,0,0,0);
    v_1->addSpacing(3);
    v_1->addWidget(m_subjectName);
    v_1->addStretch();
    QVBoxLayout *v_2 = new QVBoxLayout;
    v_2->setContentsMargins(0,0,0,0);
    v_2->addWidget(m_courseName);
//    v_2->addStretch();
    h_layout1->addLayout(v_1);
    h_layout1->addLayout(v_2);


//    h_layout1->addWidget(m_subjectName);
//    h_layout1->addWidget(m_courseName);


    QHBoxLayout * h_layout2 = new QHBoxLayout;
    h_layout2->setContentsMargins(0,0,0,0);
    m_teachers = new TeacherHeadWidget(this);
    m_refundFlag = new QLabel(this);
    m_refundFlag->setFixedSize(78,78);
    m_refundFlag->setObjectName("course_refund");
    h_layout2->addWidget(m_teachers);
    h_layout2->addStretch();
    h_layout2->addWidget(m_refundFlag);


    layout->addLayout(h_layout1);
    layout->addStretch();
    layout->addSpacing(20);
    layout->addLayout(h_layout2);
    this->setLayout(layout);
}

void CourseCardWidget::setCourseInfo(const CourseCardInfo &info)
{
    m_info = info;
    updateUiByInfo();
}

const CourseCardInfo& CourseCardWidget::getCourseInfo()
{
    return m_info;
}

void CourseCardWidget::updateUiByInfo()
{
    m_subjectName->setText(m_info.subjectName);
    m_courseName->setText(m_info.courseName);
    m_refundFlag->setVisible(m_info.isRefund);
    m_teachers->setTeacherHeadInfo(m_info.teachers);
}

void CourseCardWidget::sltMouseClicked()
{
//    qDebug()<<"CourseCardWidget::sltMouseClicked()";
    CourseToChapterPar par;
    par.courseName = m_info.courseName;
    par.courseType = 1;
    par.stuCouID = 12212121;
    InterMediaCtrl::GetInstance().changeToChapterMode(par);
}


void CourseCardWidget::mousePressEvent(QMouseEvent *event)
{
    m_mousePos = event->pos();
}

void CourseCardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    if((m_mousePos-pos).manhattanLength()<2)
    {
        emit clicked();
    }
}

void CourseCardWidget::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    QRect rect = this->rect().adjusted(m_shadowY,+m_shadowY,-1*m_shadowY,-1*m_shadowY);
    QColor color(92, 93, 95, 50);
    int arr[10] = {30, 20, 10, 5, 5};
    for (int i = 0; i < m_shadowX; i++) {
        QRect r1 = rect.adjusted(-1*i,-1*i,1*i,1*i);
        color.setAlpha(arr[i]);
        painter.setPen(color);
        painter.drawRoundedRect(QRectF(r1),8,8);
    }
    painter.restore();
}
