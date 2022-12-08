#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

//defining functions for colocalization matrix
double distance(double x1, double x2, double y1, double y2);
MatrixXd matrix_distance(MatrixXd A);
double max (double a, double b);
double linkage(double d, double m, double p);
MatrixXd matrix_linkage(MatrixXd A, double m, double p);

//function to read data
Eigen::MatrixXd openData(std::string fileToOpen);

#endif // SPARSEMATRIX_H
