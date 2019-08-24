#ifndef STUDYDIRWIDGET_H
#define STUDYDIRWIDGET_H

#include <QObject>
#include <QWidget>
#include "common/common.h"

class QLabel;
class QPushButton;
class QHBoxLayout;
class StackDownload;
class FileNameWidget;
class StudyFileItem;
class QVBoxLayout;
class StudyDirWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StudyDirWidget(QWidget *parent = nullptr);

    void setStuDirContents(MaterialUnit unit);

signals:

public slots:
    void onFoldButtonClicked();

private:
    void clearContents();
    void initUi();

private:
    FileNameWidget          *m_dirFile;
    QLabel                  *m_dateLabel;
    QPushButton             *m_foldButton;
    bool                     m_unfold;
    QList<StudyFileItem*>   m_fileList;
    QVBoxLayout             *m_vLayout;
    QHBoxLayout             *m_hLayout;
    QWidget                 *m_btnWidget;
    QWidget                 *m_dirWidget;

};

#endif // STUDYDIRWIDGET_H
