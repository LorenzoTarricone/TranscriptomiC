#include "mainwindow.h"
#include <QApplication>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main(int argc, char *argv[])
{
    MatrixXd A = openData("/Users/alanpicucci/Desktop/Projects/Transcriptomics/TranscriptomiC/dummyData.csv");
    cout << A;

    cout << "\nRow 35, column 2 of matrix A: \n" <<A(34,1);

    cout << "Transpose: " << A.transpose();

    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
}
