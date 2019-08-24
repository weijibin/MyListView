#ifndef STUDYFILEITEM_H
#define STUDYFILEITEM_H

#include <QObject>
#include <QWidget>
#include "common/common.h"
class QLabel;
class QHBoxLayout;
class StackDownload;
class FileNameWidget;

class StudyFileItem : public QWidget
{
    Q_OBJECT
public:
    explicit StudyFileItem(QWidget *parent = nullptr);

    void setStudyFileContent(MaterialInfo info, bool isDir = false);

signals:

public slots:
protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void initUi();

private:
    FileNameWidget   *m_fileNameWidget;
    StackDownload    *m_downloadWidget;
    QLabel           *m_dateLabel;
    QHBoxLayout      *m_hLayout;
    MaterialInfo      m_fileInfo;

};


class FileNameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileNameWidget(QWidget *parent = nullptr);
    ~FileNameWidget();

    void setDirFileNameContent(const QString &fileName);
    void setFileNameWidgetContent(const QString &fileName, bool isDir=false);
    void initUi();

signals:

public slots:

private:
    QLabel          *m_icon;
    QLabel          *m_fileNameLabel;
    QHBoxLayout     *m_hLayout;

};

#endif // STUDYFILEITEM_H
