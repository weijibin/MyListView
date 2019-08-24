#include "TeacherHeadWidget.h"
#include "HeadItem.h"
#include <QDebug>
#include <QHBoxLayout>

TeacherHeadWidget::TeacherHeadWidget(QWidget *parent)
    : QWidget(parent)
    , m_layout(nullptr)
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0,32,0,32);
}

TeacherHeadWidget::~TeacherHeadWidget()
{

}

void TeacherHeadWidget::clearContens()
{
    while (m_teacherHeadList.size() >0) {
        m_layout->removeWidget(m_teacherHeadList.first());
        m_teacherHeadList.removeFirst();
    }

    m_teacherHeadList.clear();
}

void TeacherHeadWidget::setTeacherHeadInfo(const QList<TeacherInfo> &info)
{
    clearContens();

    for(int i = 0;  i < info.size(); i++) {
        HeadItem * item = new HeadItem(this);
        qDebug() << "---->" << info.at(i).imgUrl << info.at(i).type << info.at(i).name;

        item->setHeadInfo(info.at(i).imgUrl, info.at(i).type, info.at(i).name);
        m_layout->addWidget(item);
        m_teacherHeadList.append(item);
        qDebug() << "TeacherHeadWidget::setTeacherHeadInfo--i " << i
                 << info.at(i).imgUrl << info.at(i).name << info.at(i).type;
    }

    adjustSize();
    qDebug() << "TeacherHeadWidget::setTeacherHeadInfo OK";
}
