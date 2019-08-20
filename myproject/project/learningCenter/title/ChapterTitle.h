#ifndef CHAPTERTITLE_H
#define CHAPTERTITLE_H
#include "TitleBaseWidget.h"
#include <QPushButton>
#include <QLabel>

#include "ToolButton.h"
class ChapterTitle : public TitleBaseWidget
{
    Q_OBJECT
public:
    explicit ChapterTitle(QWidget *parent = 0);

    void setMaterialVisible(bool visible);
    void setCourseName(const QString& name);
protected:
    void initOtherUi();
    void initOtherConnections();
private:
    ToolButton *m_backHome = nullptr;
    QLabel * m_courseName = nullptr;
    QPushButton * m_material = nullptr;
};

#endif // COURSETITLE_H
