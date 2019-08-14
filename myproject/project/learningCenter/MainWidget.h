#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
class MainTitle;
class ClassListWidget;
class CourseListWidget;
class QStackedLayout;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

    enum Index{ Class, Course, Loading, Retry };

    void initState();

    void changeToClassMode();
    void changeToCourseMode();

    void setOuterWidget(QWidget*w);

signals:

public slots:
private:
    void initUI();

private:

    MainTitle *m_title = nullptr;
    QStackedLayout * m_stackedLayout = nullptr;
    ClassListWidget *m_classList = nullptr;
    CourseListWidget *m_courseList = nullptr;

};

#endif // MAINWIDGET_H
