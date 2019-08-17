#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
class MainTitle;
class ClassListWidget;
class CourseListWidget;
class QStackedLayout;
class QPushButton;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

    enum Index{ Class, Course, TakeClass,NoClass, Retry };

    void initState();

    void changeToClassMode();
    void changeToCourseMode();

    void changeToTakeClassMode();
    void changeToNoClassMode();
    void changeToRetryMode();

    void setOuterWidget(QWidget*w);

signals:

public slots:
private:
    void initUI();

    void initAbnormalUi();
    void initTakeClassUi();
    void initNoClassUi();
    void initRetryClassUi();

    void initConnections();

private:

    MainTitle *m_title = nullptr;
    QStackedLayout * m_stackedLayout = nullptr;
    ClassListWidget *m_classList = nullptr;
    CourseListWidget *m_courseList = nullptr;


    QPushButton * m_retryBtn = nullptr;
    QPushButton * m_takeClassBtn = nullptr;

};

#endif // MAINWIDGET_H
