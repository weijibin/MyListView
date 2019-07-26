#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPushButton>
#include "datewidget.h"

class DateDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    DateDelegate(QObject *parent = 0);

protected:
    virtual void paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const override;
    virtual bool editorEvent(QEvent *event,
                                         QAbstractItemModel *model,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) override;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    void DateDelegate::paintWidget(QPainter *painter,
            const QRect &rect, const QString &cacheKey,
            QWidget *widget) const;

private:

    DateWidget * m_widget;

    QPushButton * m_btn;

};

#endif // DATEDELEGATE_H

