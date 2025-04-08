#include "mainwindow.h"
#include "cylesutils.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication* a = new QApplication(argc, argv);
    CylesUtils::SystemStyle = a->style()->name();
    MainWindow w;
    w.app = a;
    w.show();
    return a->exec();
    delete a;
}
