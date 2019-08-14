#include "CourseCardWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "common/TeacherHeadWidget.h"

CourseCardWidget::CourseCardWidget(QWidget *parent) : QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    initUi();
    setFixedSize(384,174);
}

void CourseCardWidget::initUi()
{
    setContentsMargins(24,18,24,18);

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
