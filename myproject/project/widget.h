#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class LearningCenterWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_dateBtn_clicked();

    void on_classBtn_clicked();

    void on_courseBtn_clicked();

    void on_chapterBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    LearningCenterWidget * m_center = nullptr;
};

#endif // WIDGET_H
