#ifndef COLONALIZATION_MATRIX_H
#define COLONALIZATION_MATRIX_H

#include <iostream>
#include <Eigen/Dense>
#include <vector>

using namespace Eigen;
using namespace std;


// auxilary functions
double distance(double x1, double x2, double y1, double y2);
double max (double a, double b);
double linkage(double d, double m, double p);


//defining functions for colocalization matrix
MatrixXd matrix_distance(MatrixXd A);

MatrixXd matrix_linkage(const MatrixXd &A, double m, double p);

MatrixXd combine_linkage(const MatrixXd &A_linkage, const MatrixXd &A_expression);

MatrixXd comparison(const MatrixXd &expression, const MatrixXd &neighbors, double a=1, double b=0.5);

MatrixXd comparison_old(const MatrixXd &expression, const MatrixXd &neighbors, double a=1, double b=0.5);

MatrixXd enrichment(const MatrixXd &A);




#endif // COLONALIZATION_MATRIX_H
