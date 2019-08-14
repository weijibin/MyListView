#ifndef COURSECARDWIDGET_H
#define COURSECARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "common/common.h"

class TeacherHeadWidget;

class CourseCardWidget : public QFrame
{
    Q_OBJECT
public:
    explicit CourseCardWidget(QWidget *parent = 0);

    const CourseCardInfo& getCourseInfo();
    void setCourseInfo(const CourseCardInfo& info);

signals:

public slots:
private:
    void initUi();
    void updateUiByInfo();
private:
    QLabel * m_subjectName = nullptr;
    QLabel * m_courseName = nullptr;
    QLabel * m_refundFlag = nullptr;

    TeacherHeadWidget * m_teachers = nullptr;

    CourseCardInfo m_info;
};

#endif // COURSECARDWIDGET_H
