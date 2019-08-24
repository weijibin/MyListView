#ifndef TEACHERHEADWIDGET_H
#define TEACHERHEADWIDGET_H

#include <QObject>
#include <QWidget>
#include "common.h"
class HeadItem;
class QHBoxLayout;
//typedef struct{
//    QString imgUrl;
//    int type;  // 主讲 辅导 外教
//    QString name;
//} TeacherInfo;

class TeacherHeadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TeacherHeadWidget(QWidget *parent = nullptr);

    ~TeacherHeadWidget();

    void clearContens();
    void  setTeacherHeadInfo(const QList<TeacherInfo> &info);

signals:

public slots:

private:
    QList<HeadItem*>   m_teacherHeadList;
    QHBoxLayout       *m_layout;
};

#endif // TEACHERHEADWIDGET_H
