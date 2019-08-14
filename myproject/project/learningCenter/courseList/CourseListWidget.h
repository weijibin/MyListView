#ifndef COURSELISTWIDGET_H
#define COURSELISTWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QFrame>
#include <QButtonGroup>
#include <QGridLayout>

class CourseListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CourseListWidget(QWidget *parent = 0);

signals:

public slots:
private:
    void initUi();
    void initTitle1();
    void initTitle2();

    void initArea();
private:
    QFrame* m_statusTitle = nullptr;
    QFrame* m_subTitle = nullptr;

    QScrollArea* m_area = nullptr;
    QWidget * m_scrolWidget = nullptr;
    QGridLayout * m_scrolLayout = nullptr;

    QButtonGroup * m_groupTitle1 = nullptr;
    QButtonGroup * m_groupTitle2 =nullptr;
};

#endif // COURSELISTWIDGET_H
