#ifndef CHAPTERTITLE_H
#define CHAPTERTITLE_H
#include "TitleWidget.h"
#include <QPushButton>
class ChapterTitle : public TitleWidget
{
    Q_OBJECT
public:
    explicit ChapterTitle(QWidget *parent = 0);
protected:
    void initOtherUi();
private:
    QPushButton *m_backHome = nullptr;
};

#endif // COURSETITLE_H
