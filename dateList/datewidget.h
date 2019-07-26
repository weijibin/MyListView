#ifndef DATEWIDGET_H
#define DATEWIDGET_H

#include <QWidget>

namespace Ui {
class DateWidget;
}

class DateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DateWidget(QWidget *parent = 0);
    ~DateWidget();
    QString text();

private:
    Ui::DateWidget *ui;
};

#endif // DATEWIDGET_H
