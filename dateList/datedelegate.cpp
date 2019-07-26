#include "datedelegate.h"
#include <QPixmap>
#include <QPixmapCache>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

DateDelegate::DateDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    m_widget  = new DateWidget;
    m_widget->setFixedSize(200,50);

    m_btn = new QPushButton;
    m_btn->setText("Hello world");
    m_btn->setFixedSize(100,30);
}

void DateDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,const QModelIndex& index)const
{
    painter->setRenderHints(QPainter::Antialiasing);
    bool selected = option.state & QStyle::State_Selected;

    QPalette palette(option.palette);
    palette.setColor(QPalette::Active, QPalette::Window,
                     selected ? option.palette.highlight().color()
                              : option.palette.base().color());
    palette.setColor(QPalette::Active, QPalette::WindowText,
                     selected
                     ? option.palette.highlightedText().color()
                     : option.palette.text().color());

    m_btn->setPalette(palette);

    m_btn->setText(index.data(Qt::UserRole).toString());



    QRect wect = QRect(option.rect.topLeft(),m_btn->size());
    QPixmap pixmap(m_btn->size());
    m_btn->render(&pixmap);
    painter->setRenderHints(QPainter::Antialiasing);
    painter->drawPixmap(wect, pixmap);


//    paintWidget(painter, wect, "123333", m_widget);


//    QStyledItemDelegate::paint(painter,option,index);
}

bool DateDelegate::editorEvent(QEvent *event,
                               QAbstractItemModel *model,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) {



    if((event->type() == QEvent::MouseButtonRelease))
    {
        QRect rect(option.rect.topLeft(),m_btn->size());
        QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
        qDebug()<<mouse_event->pos();
        qDebug()<<rect;
        if(rect.contains(mouse_event->pos()))
        {
            qDebug()<<"clickBtn";
        }
    }

    return QStyledItemDelegate::editorEvent(event,model,option,index);
}


QSize DateDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    return QSize(100,40);
}

void DateDelegate::paintWidget(QPainter *painter,
        const QRect &rect, const QString &cacheKey,
        QWidget *widget) const
{
    QPixmap pixmap(widget->size());
    if (!QPixmapCache::find(cacheKey, &pixmap)) {
        widget->render(&pixmap);
        QPixmapCache::insert(cacheKey, pixmap);
    }

    painter->setRenderHints(QPainter::Antialiasing);
    painter->drawPixmap(rect, pixmap);
}
