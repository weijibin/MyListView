#include "TeacherHeadWidget.h"
#include "HeadItem.h"

#include <QHBoxLayout>

TeacherHeadWidget::TeacherHeadWidget(QWidget *parent) : QWidget(parent)
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
}

TeacherHeadWidget::~TeacherHeadWidget()
{

}

void TeacherHeadWidget::setTeacherHeadInfo(QList<TeacherInfo> info)
{
    for(int i = 0;  i < info.size(); i++) {
        HeadItem * item = new HeadItem(this);
        item->setHeadInfo(info.at(i).imgUrl, info.at(i).type, info.at(i).name);
        m_layout->addWidget(item);
        m_teacherHeadList.append(item);
    }

    adjustSize();
}
