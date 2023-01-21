#include "mainwindow.h"
#include <QApplication>
#include <Eigen/Dense>
#include <cmath>

using namespace Eigen;
using namespace std;

//This function takes as input an x vs y position of gene matrix and has functions to return the distance between two points, 
//the distance between every point in the matrix in a new eigen matrix, the linkage value between two genes and finally an 
//eigen matrix with all of the linkage values, so in other words, the colocalization matrix as an eigen matrix.

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
double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

//given an eigen matrix, returns an eigen matrix with the distance between points of the previous eigen matrix
MatrixXd matrix_distance(MatrixXd A){
    MatrixXd A_distance = A;
    for (int i = 0; i < A.rows(); i++){
        for (int j = 0; j < A.cols(); j++){
            if (i != j) { //skip the distance for a point and itself
                A_distance(i,j) = distance(A(i,0), A(i,1), A(j,0), A(j,1)); //get distance between two points
            }
        }
    }
    return A_distance;
}

//returns the max of two doubles
double max (double a, double b){
    if (a<b){return b;}
    return a;
}

//returns the linkage value of coordinates x=(x1,y1) and y=(x2,y2) given m and p
double linkage(double x1, double y1, double x2, double y2, double m, double p) {
    return pow((max(0,m-distance(x1,x2,y1,y2))/m), p)*100;
}

//given an eigen matrix of the distance between points and the values m and p, returns an eigen matrix with the linkage values
MatrixXd matrix_linkage(MatrixXd A, double m, double p){
    MatrixXd A_linkage = A;
    for (int i = 0; i < A.rows(); i++){
        for (int j = 0; j < A.cols(); j++){
            A_linkage(i,j) = linkage(A(i,0), A(i,1), A(j,0), A(j,1), m, p);
        }
    }
    return A_linkage;
}
