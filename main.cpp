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

//returns the distance of coordinates x and y
double distance(double x, double y) {
    double x1, y1 = x; double x2, y2 = y;
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

//given an eigen matrix, returns an eigen matrix with the distance between points
MatrixXd matrix_distance(MatrixXd A){
    MatrixXd A_distance = A;
    for (int i = 0; i < sizeof(A) ; i++){
        for (int j = 0; j < sizeof(A); j++){
            A_distance[i][j] = distance(A[i], A[j]); //distance between coordinate i and j
        }
    }
    return A_distance;
}

//returns the max of two doubles
double max (double a, double b){
    if (a<b){return b;}
    return a;
}

//returns the linkage value of coordinates (x1,y1) and (x2,y2) given m and p
double linkage(double x, double y, double m, double p) {
    double x1, y1 = x; double x2, y2 = y;
    return pow((max(0,m-distance(x1,y1,x2,y2))/m), p)*100;
}

//given an eigen matrix of the distance between points and the values m and p, returns an eigen matrix with the linkage values
MatrixXd matrix_linkage(MatrixXd A_distance, double m, double p){
    MatrixXd A_linkage = A_distance;
    for (int i = 0; i < sizeof(A_distance); i++){
        for (int j = 0; j < sizeof(A_distance); j++){
            A_linkage[i][j] = linkage(A_distance[i], A_distance[j], m, p);
        }
    }
    return A_linkage;
}
