#include <QPainter>
#include <QMouseEvent>

#include "PixmapButton.h"
#include "mutility.h"

#define DEFAULT_FONT_COLOR      "#646464"
#define TEXT_POS_DEFAULT        (-1)
#define TEXT_

PixmapButton::PixmapButton(QWidget *parent)
    : QPushButton(parent)
    , m_normalColor(DEFAULT_FONT_COLOR)
    , m_textXPos(TEXT_POS_DEFAULT)
{
    setCursor(Qt::PointingHandCursor);
}

PixmapButton::~PixmapButton()
{

}

void PixmapButton::setPixmap(const QPixmap &pixmap)
{
    int nPixWidth = pixmap.width();
    int nPixHeight = pixmap.height();

    QPixmap normal = pixmap.copy( 0, 0, nPixWidth/4, nPixHeight);
    QPixmap hover = pixmap.copy( nPixWidth/4 , 0, nPixWidth/4, nPixHeight);
    QPixmap pressed = pixmap.copy( nPixWidth/4 * 2, 0, nPixWidth/4, nPixHeight);
    QPixmap disabled = pixmap.copy( nPixWidth/4 * 3, 0, nPixWidth/4, nPixHeight);

    setNormalPixmap(normal);
    setHoverPixmap(hover);
    setClickPixmap(pressed);
    setDisablePixmap(disabled);
}

void PixmapButton::setNormalPixmap(const QPixmap &pixmap)
{
    m_normalPixmap = pixmap;

    m_currentPixmap = pixmap;
    setFixedSize(pixmap.size());
    update();
}

void PixmapButton::setHoverPixmap(const QPixmap &pixmap)
{
    m_hoverPixmap = pixmap;
}

void PixmapButton::setClickPixmap(const QPixmap &pixmap)
{
    m_clickedPixmap = pixmap;
}

void PixmapButton::setDisablePixmap(const QPixmap &pixmap)
{
    m_disabledPixmap = pixmap;
}

void PixmapButton::setNormalTextColor(const QColor &color)
{
    m_normalColor = color;
    m_currentTextColor = m_normalColor;
    update();
}

void PixmapButton::setClickTextColor(const QColor &color)
{
    m_clickColor = color;
    update();
}

void PixmapButton::setTextXPos(int x, int flags)
{
    m_textXPos  = x;
    m_flags     = flags;
}

void PixmapButton::setEnabled(bool enabled)
{
    if (enabled) {
        m_currentPixmap = m_normalPixmap;
        m_currentTextColor = m_normalColor;
    } else {
        m_currentPixmap = m_disabledPixmap;
        m_currentTextColor = m_clickColor;
    }

    QPushButton::setEnabled(enabled);

    update();
}

void PixmapButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);

    if (!isEnabled()) {
        m_currentTextColor = QColor("#9b9a9a");
        m_currentPixmap = m_disabledPixmap;
    }

    p.drawPixmap(rect(), m_currentPixmap);

    if(!text().isEmpty())
    {
        QRect textRect;

        if (m_textXPos == TEXT_POS_DEFAULT) {
            textRect = rect();
            m_flags = Qt::AlignHCenter | Qt::AlignVCenter;
        } else {
            textRect = QRect(m_textXPos, 0, width() - m_textXPos, height());
        }

        p.setPen(m_currentTextColor);
        p.drawText(textRect, m_flags, text());
    }
}

void PixmapButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_currentPixmap = m_hoverPixmap;
    m_currentTextColor = m_normalColor;

    update();
    emit enter();

    QPushButton::enterEvent(event);
}

void PixmapButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_currentPixmap = m_normalPixmap;
    m_currentTextColor = m_normalColor;

    update();
    emit leave();

    QPushButton::leaveEvent(event);
}

void PixmapButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_currentPixmap = m_clickedPixmap;
    m_currentTextColor = m_clickColor;

    update();
    QPushButton::mousePressEvent(event);
}

void PixmapButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
#ifdef Q_OS_WIN
    m_currentPixmap = m_hoverPixmap;
    m_currentTextColor = m_normalColor;
#else
    m_currentPixmap = m_normalPixmap;
    m_currentTextColor = m_normalColor;
#endif
    update();
    QPushButton::mouseReleaseEvent(event);
}
