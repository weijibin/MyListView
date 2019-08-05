#include "widget.h"
#include <QApplication>
#include <QLockFile>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Widget w;
    w.show();
//    QLockFile file("122");
//    file.tryLock(500);

    return a.exec();
}
