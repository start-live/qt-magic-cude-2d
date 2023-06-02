#include "imainwidget.h"

#include "widget/iscenewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ISceneWidget w;
    w.show();
    return a.exec();
}
