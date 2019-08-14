#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QPushButton>

class QFont;

class ToolButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ToolButton(QWidget *parent = 0);
    void setDisplyText(const QString & str);

signals:

public slots:
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
private:
    QString m_name;
    QString m_icon;
    QString m_icon_hover;
    QString m_color;
    QString m_color_hover;
    QFont m_font;
    bool m_isHover = false;
};

#endif // TOOLBUTTON_H
