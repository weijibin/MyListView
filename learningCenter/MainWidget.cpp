#include "MainWidget.h"

#include "title/MainTitle.h"
#include "classlist/ClassListWidget.h"
#include "courselist/CourseListWidget.h"
#include "InterMediaCtrl.h"
#include <QStackedLayout>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void MainWidget::initUI()
{
    m_title = new MainTitle(this);
    m_title->setObjectName("centerTitle");
    m_classList = new ClassListWidget(this);
    m_courseList = new CourseListWidget(this);


    m_stackedLayout = new QStackedLayout;
    m_stackedLayout->addWidget(m_classList);
    m_stackedLayout->addWidget(m_courseList);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_title);
    mainLayout->addLayout(m_stackedLayout);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    this->setContentsMargins(0,0,0,0);
    mainLayout->setContentsMargins(0,0,0,0);

    m_stackedLayout->setCurrentIndex(Class);

}

void MainWidget::setOuterWidget(QWidget *w)
{
    m_title->setOuterWidget(w);
}

void MainWidget::initState()
{
    m_stackedLayout->setCurrentIndex(Class);
    m_title->initState();
}

void MainWidget::changeToClassMode()
{
    m_stackedLayout->setCurrentIndex(Class);
}

void MainWidget::changeToCourseMode()
{
    m_stackedLayout->setCurrentIndex(Course);
}
