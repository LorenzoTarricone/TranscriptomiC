#include "mainwindow.h"
#include <QApplication>
#include "api.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    printExample();
    MainWindow w;
    w.show();
    return a.exec();

//    parsemtx mtxobject = parsemtx();
//    mtxobject.readFile("mtx_test.mtx");
//    mtxobject.print();
//    return 0;
}
