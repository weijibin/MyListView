#ifndef HEADITEM_H
#define HEADITEM_H

#include <QWidget>

class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class RoundMovieWidget;
class HeadItem : public QWidget
{
    Q_OBJECT

public:
    explicit HeadItem(QWidget *parent = nullptr);
    ~HeadItem();

    void initUi();

public:
    void setHeadInfo(const QString &pixPath,  int type,  const QString &teacherName);
    void setHeadPixmap(const QString &pixPath, int radius = 32);
    void setHeadText(const QString &type, const QString &teacherName);


private:
   QLabel              *m_typeLabel;
   QLabel              *m_nameLabel;
   QHBoxLayout         *m_hLayout;
   QVBoxLayout         *m_vLayout;
   RoundMovieWidget    *m_roundWidget;

};

#endif // HEADITEM_H
