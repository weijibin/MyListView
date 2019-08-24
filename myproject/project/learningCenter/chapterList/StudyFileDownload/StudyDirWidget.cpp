#include "StudyDirWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include "StudyFileItem.h"

StudyDirWidget::StudyDirWidget(QWidget *parent)
    : QWidget(parent)
    , m_dirFile(nullptr)
    , m_dateLabel(nullptr)
    , m_foldButton(nullptr)
    , m_hLayout(nullptr)
    , m_unfold(false)
{

    initUi();
}

void StudyDirWidget::clearContents()
{
    while (m_fileList.size() > 0) {
        StudyFileItem *f = m_fileList.takeFirst();
        m_vLayout->removeWidget(f);
        delete f;
        f = nullptr;
    }
    m_fileList.clear();

}

void StudyDirWidget::setStuDirContents(MaterialUnit unit)
{
    m_dirFile->setDirFileNameContent(unit.title);
    m_dateLabel->setText(unit.uploadTime);

    for (int i = 0; i < unit.lst.size(); i++) {
        StudyFileItem *item = new StudyFileItem();
        item->setStudyFileContent(unit.lst.at(i), true);
        m_fileList.append(item);
        m_vLayout->addWidget(item);
        item->setVisible(false);
    }
    adjustSize();
}

void StudyDirWidget::initUi()
{
    setFixedWidth(564);

    m_dirWidget = new QWidget(this);
//    m_dirWidget->setStyleSheet("box-shadow:0px -1px 0px 0px rgba(0,0,0,1);");
    m_dirWidget->setFixedSize(544, 56);

    m_dirFile = new FileNameWidget(this);
    m_dirFile->setFixedSize(346, 56);

    m_dateLabel = new QLabel(this);
    m_dateLabel->setStyleSheet("font-size:12px; font-family:Microsoft YaHei; color:rgba(133,140,150);");
    m_dateLabel->setFixedSize(114, 15);

    m_hLayout = new QHBoxLayout();

    m_btnWidget = new QWidget();
    m_btnWidget->setFixedSize(56, 56);
    m_foldButton = new QPushButton(m_btnWidget);
    connect(m_foldButton, SIGNAL(clicked()), this, SLOT(onFoldButtonClicked()));
    m_foldButton->setFixedSize(20, 20);
    m_foldButton->setText("");
    m_foldButton->setStyleSheet("QPushButton{border-image:url(:/res/icon_arrow_up.png);}"
                                  "QPushButton:hover {border-image:url(:/res/icon_arrow_up.png);}");

    if (m_unfold) {
        m_foldButton->setStyleSheet("QPushButton{border-image:url(:/res/icon_arrow_down.png);}"
                                      "QPushButton:hover {border-image:url(:/res/icon_arrow_down_hover.png);}");
    }
    QHBoxLayout *hLayout = new QHBoxLayout();

    hLayout->addWidget(m_foldButton);
    hLayout->setContentsMargins(0,0,0,0);
    hLayout->setSpacing(0);
    m_btnWidget->setLayout(hLayout);

    m_hLayout->addWidget(m_dirFile);
    m_hLayout->addWidget(m_dateLabel);
    m_hLayout->addWidget(m_btnWidget);


    m_hLayout->setContentsMargins(0,0,0,0);
    m_hLayout->setSpacing(24);
    m_dirWidget->setLayout(m_hLayout);

    m_vLayout = new QVBoxLayout();
    m_vLayout->addWidget(m_dirWidget);
    m_vLayout->setContentsMargins(0,0,0,0);
    m_vLayout->setSpacing(0);
    setLayout(m_vLayout);
    adjustSize();
}

void StudyDirWidget::onFoldButtonClicked()
{
    m_unfold = !m_unfold;

    if (m_unfold) {
        for (int i = 0; i < m_fileList.size(); i++) {
            m_fileList.at(i)->setVisible(true);
        }
        m_foldButton->setStyleSheet("QPushButton{border-image:url(:/res/icon_arrow_down.png);}"
                                      "QPushButton:hover {border-image:url(:/res/icon_arrow_down_hover.png);}");
    } else {
        for (int i = 0; i < m_fileList.size(); i++) {
            m_fileList.at(i)->setVisible(false);
        }
        m_foldButton->setStyleSheet("QPushButton{border-image:url(:/res/icon_arrow_up.png);}"
                                      "QPushButton:hover {border-image:url(:/res/icon_arrow_up_hover.png);}");

    }
    adjustSize();
    update();
}
