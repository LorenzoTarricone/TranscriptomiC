#include <QApplication>
#include "Visualize.hpp"
#include "mainwindow.h"
#include <Eigen/Dense>
#include <SparseMatrix.h>
#include <math.h>


using namespace Eigen;
using namespace std;

//given an eigen matrix, returns an eigen matrix with the distance between points
double distance(double x1, double x2, double y1, double y2) {
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
};

//given an eigen matrix, returns an eigen matrix with the distance between points
MatrixXd matrix_distance(MatrixXd A){
    MatrixXd A_distance(A.rows(),A.rows());
    for (int i = 0; i < A.rows() ; i++){
        for (int j = 0; j < A.rows(); j++){
            A_distance(i,j) = distance(A(i,1), A(j,1), A(i, 2), A(j,2)
                                       ); //distance between coordinate i and j
        }
    }
    return A_distance;
};

double max (double a, double b){
    if (a<b){return b;}
    return a;
};

//returns the linkage value of coordinates (x1,y1) and (x2,y2) given m and p
double linkage(double d, double m, double p) {
    return pow((max(0,m-d))/m, p);
}

//given an eigen matrix of the distance between points and the values m and p, returns an eigen matrix with the linkage values
MatrixXd matrix_linkage(MatrixXd A, double m, double p){
    MatrixXd A_distance = matrix_distance(A);
    MatrixXd A_linkage(A_distance.rows(), A_distance.rows());
    for (int i = 0; i < A_distance.rows(); i++){
        for (int j = 0; j < A_distance.rows(); j++){
            A_linkage(i,j) = linkage(A_distance(i,j), m, p);
        }
    }
    return A_linkage;
}
