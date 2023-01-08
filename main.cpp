#include "UploadWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UploadWindow w;
    w.show();
    return a.exec();

//    parsemtx mtxobject = parsemtx();
//    mtxobject.readFile("mtx_test.mtx");
//    mtxobject.print();
//    return 0;
}
