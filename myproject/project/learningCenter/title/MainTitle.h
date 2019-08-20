#ifndef MAINTITLE_H
#define MAINTITLE_H
#include "TitleBaseWidget.h"

class HeadImg;
class QLabel;
class QPushButton;
class QButtonGroup;

class MainTitle : public TitleBaseWidget
{
    Q_OBJECT
public:
    explicit MainTitle(QWidget *parent = 0);

    void initState();

protected:
    void initOtherUi();
    void initOtherConnections();

private:

    QLabel *m_icon = nullptr;

    QButtonGroup * m_group = nullptr;
    QPushButton *m_class = nullptr;
    QPushButton *m_course = nullptr;

    HeadImg * m_img =nullptr;
    QLabel * m_name = nullptr;

    QPushButton * m_menu = nullptr;

};

#endif // MAINTITLE_H
