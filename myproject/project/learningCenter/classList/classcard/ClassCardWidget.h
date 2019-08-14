#ifndef CLASSCARDWIDGET_H
#define CLASSCARDWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include "common/common.h"

class TeacherHeadWidget;

class ClassCardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClassCardWidget(QWidget *parent = 0);

    const ClassCardInfo& getClassInfo();
    void setClassInfo(const ClassCardInfo& info);

signals:

public slots:
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    void initUi();
    void initEntrance();
    void initCourseInfo();
    void updateUiByInfo();
private:
    QVBoxLayout * m_layout;
    ClassCardInfo m_info;

    QFrame * m_widgetEntrance;
    QFrame * m_widgetCourseInfo;

    //entrance
    QLabel * m_classTime =nullptr;
    QLabel * m_classDescribe =nullptr;
    QLabel * m_classTip =nullptr;
    QPushButton * m_enterClassBtn = nullptr;

    //courseinfo
    QLabel * m_chaperName = nullptr;
    QLabel * m_courseName = nullptr;
    QLabel * m_subjectName = nullptr;
    TeacherHeadWidget * m_teachersInfo = nullptr;

};

#endif // CLASSCARDWIDGET_H
