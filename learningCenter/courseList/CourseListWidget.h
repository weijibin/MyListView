#ifndef COURSELISTWIDGET_H
#define COURSELISTWIDGET_H

#include <QWidget>

class CourseListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CourseListWidget(QWidget *parent = 0);

signals:

public slots:
private:
    void initUi();
};

#endif // COURSELISTWIDGET_H
