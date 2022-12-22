#include "mainwindow.h"
#include "parsemtx.h"
#include "parsetxtbeams.h"
#include "matrixeigen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

//    MatrixEigen matrix_eigen =  MatrixEigen();
//    matrix_eigen.generateRandomCSV(10,10,0,1,"csv_test.csv");
//    std::cout << "Program path : " << argv[0] << std::endl;

    parseTxtBeams tsv_object = parseTxtBeams();
    tsv_object.createDummyFile(10,"tsv_test_2.tsv");
    tsv_object.readFile("tsv_test_2.tsv");

//    parsemtx mtxobject = parsemtx();
//    mtxobject.readFile("mtx_test.mtx");
//    mtxobject.print();
    return 0;
}
