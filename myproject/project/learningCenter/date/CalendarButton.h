#ifndef CALENDARBUTTON_H
#define CALENDARBUTTON_H

#include <QPushButton>

class QFont;
class CalendarButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CalendarButton(QWidget *parent = 0);
    void setDisplyText(const QString & str);

signals:

public slots:
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    QString m_name;
    QString m_icon;
    QFont m_font;
};

#endif // CALENDARBUTTON_H
