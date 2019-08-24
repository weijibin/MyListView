#ifndef PIXMAPBUTTON_H
#define PIXMAPBUTTON_H

#include <QPushButton>

class PixmapButton : public QPushButton
{
  Q_OBJECT

public:
    explicit PixmapButton(QWidget * parent=0);
    ~PixmapButton();

    // 使用四态图
    void setPixmap(const QPixmap &pixmap);

    void setNormalPixmap(const QPixmap &pixmap);
    void setHoverPixmap(const QPixmap &pixmap);
    void setClickPixmap(const QPixmap &pixmap);
    void setDisablePixmap(const QPixmap &pixmap);

    void setNormalTextColor(const QColor& color);
    void setClickTextColor(const QColor& color);

    void setTextXPos(int x, int flags = Qt::AlignHCenter | Qt::AlignVCenter);
    void setEnabled(bool enabled);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void enter();
    void leave();

private:
    QPixmap m_normalPixmap;
    QPixmap m_hoverPixmap;
    QPixmap m_clickedPixmap;
    QPixmap m_disabledPixmap;

    QPixmap m_currentPixmap;
    QColor m_currentTextColor;

    QColor m_normalColor;
    QColor m_clickColor;

    int m_textXPos;
    int m_flags;
};

#endif // PIXMAPBUTTON_H
