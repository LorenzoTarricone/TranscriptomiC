#include <QApplication>
#include "mainwindow.h"
#include <Eigen/Dense>
#include <colocalization_matrix.h>
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
            A_distance(i,j) = distance(A(i,1), A(j,1), A(i, 2), A(j,2)); //distance between coordinate i and j
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


// given an eigen matrix containing the linkage values (kxk) and a eigen matrix containing the gene - beams values (nxn)
// returns an nxk matrix indicating average gene expression in neighbouring beams

MatrixXd combine_linkage(MatrixXd A_linkage, MatrixXd A_expression){
    int k = A_linkage.rows();
    int n = A_expression.rows();
    MatrixXd A_combine(n,k);
    // iterate through columns of A_combine
    for(int j = 0; j < k; j++){
        // since we're considering A_combine and A_expression column-wise, iterate through rows per column
        for(int i = 0; i < n; i++){
            // initialize each entry to simplify the sum
            A_combine(i,j) = 0;
            // compute the sum along row j of the linkage matrix, excluding entry
            for(int r = 0; r < k; r++){
                if(r != j){
                    A_combine(i,j) += A_linkage(j,r)*A_expression(i,r);
                }// end if
            }// end for r
         }// end for i
    }// end for j
    return A_combine;
} // end method


