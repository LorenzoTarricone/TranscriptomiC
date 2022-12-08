#include <QApplication>
#include "Visualize.hpp"
#include "mainwindow.h"
#include <Eigen/Dense>
#include <SparseMatrix.h>
#include <math.h>
#include <vector>


using namespace Eigen;
using namespace std;

int main(int argc, char *argv[])
{

    vector<string> columnID;
    vector<string> rowID;

    MatrixXd A = openData_strings("/Users/alanpicucci/Desktop/Projects/Transcriptomics/TranscriptomiC/small_matrix.csv", columnID, rowID);
   // cout << A;
    cout << "\n columnID test: ";
    for (vector<string>::const_iterator i = columnID.begin(); i != columnID.end(); ++i)
        cout << *i << ' '<<endl;

    cout << "\n rowID test: ";
    for (vector<string>::const_iterator i = rowID.begin(); i != rowID.end(); ++i)
        cout << *i << ' ';

    //MatrixXd A_linkage = matrix_linkage(A, 5000, 2);

    //cout << "\n Linkage matrix: " << A_linkage;

    //cout << "\n DIAGONAL value: " << A_linkage(2,2);

    //saveData("colocalization.csv", A_linkage);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}



