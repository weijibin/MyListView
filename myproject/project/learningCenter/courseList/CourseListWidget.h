#ifndef COURSELISTWIDGET_H
#define COURSELISTWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QFrame>
#include <QButtonGroup>
#include <QGridLayout>
#include <QLabel>
#include <QStackedLayout>

class CourseCardWidget;
class CourseListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CourseListWidget(QWidget *parent = 0);

    enum Index{ Course, NoCourse};

    void changeToNoCourseMode();
    void changeToCourseListMode();

signals:

public slots:
protected:
    virtual bool eventFilter(QObject *obj, QEvent *ev) override;
private:
    void initUi();
    void initTitle1();
    void initTitle2();

    void initArea();
    void initNoCourseUi();

    void initConnections();

    void updateScrollArea(const QSize &size);
    void updateUiByColumn();
private:
    QFrame* m_statusTitle = nullptr;
    QFrame* m_subTitle = nullptr;

    QStackedLayout * m_stackedLayout = nullptr;
    QWidget * m_noCourseWidget = nullptr;

    QScrollArea* m_area = nullptr;
    QWidget * m_scrolWidget = nullptr;
    QGridLayout * m_scrolLayout = nullptr;

    QLabel *m_tip = nullptr;

    QButtonGroup * m_groupTitle1 = nullptr;
    QButtonGroup * m_groupTitle2 =nullptr;

    QList<CourseCardWidget*> m_cardList;

    int m_columnCount;
};

#endif // COURSELISTWIDGET_H
