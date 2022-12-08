#include <QApplication>
#include "Visualize.hpp"
#include "mainwindow.h"
#include <Eigen/Dense>
#include <SparseMatrix.h>
#include <math.h>


using namespace Eigen;
using namespace std;

int main(int argc, char *argv[])
{
    MatrixXd A = openData("/Users/alanpicucci/Desktop/Projects/Transcriptomics/TranscriptomiC/fake_coordinates.csv");
    cout << A;

    MatrixXd A_linkage = matrix_linkage(A, 5000, 2);

    cout << "\n Linkage matrix: " << A_linkage;

    cout << "\n DIAGONAL value: " << A_linkage(2,2);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}



