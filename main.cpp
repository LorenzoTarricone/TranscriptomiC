#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    // Test Eigen library and to plot a heatmap using a fake-colcalization matrix
    fake_colocalization_matrix fake = fake_colocalization_matrix();
    fake.make_heat_plot();


    return a.exec();

//    parsemtx mtxobject = parsemtx();
//    mtxobject.readFile("mtx_test.mtx");
//    mtxobject.print();
//    return 0;
}
