#ifndef COLONALIZATION_MATRIX_H
#define COLONALIZATION_MATRIX_H

#include <iostream>
#include <Eigen/Dense>
#include <vector>

using namespace Eigen;
using namespace std;

//defining functions for colocalization matrix
double distance(double x1, double x2, double y1, double y2);
MatrixXd matrix_distance(MatrixXd A);
double max (double a, double b);
double linkage(double d, double m, double p);
MatrixXd matrix_linkage(MatrixXd A, double m, double p);

MatrixXd combine_linkage(MatrixXd A_linkage, MatrixXd A_expression);

//function to read/save data
void saveData(string fileName, MatrixXd  matrix);
Eigen::MatrixXd openData(std::string fileToOpen);
Eigen::MatrixXd openData_strings(std::string fileToOpen,vector<string>& columnID, vector<string>& rowID);



#endif // COLONALIZATION_MATRIX_H
