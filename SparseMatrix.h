#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

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

//function to read/save data
void saveData(string fileName, MatrixXd  matrix);
Eigen::MatrixXd openData(std::string fileToOpen);
Eigen::MatrixXd openData_strings(std::string fileToOpen,vector<string>& columnID, vector<string>& rowID);


//It would be nice to create a tabular_matrixXd class that inherits from Eigen::Dense and does the following: upon initialization
//it is given a csv or txt file to read. This file should be in tabular format, having strings which identify columns and rows. For instance,
//the gene expression matrix has bead names as column IDs and gene names as row IDs (or viceversa, but hopefully you get the idea). Our class
//would return the regular matrix of doubles the added feature of having two vectors of strings, one with the column IDs and one with the row IDs.
//Given these vectors, we should be able to navigate the matrix using these string identifiers.

//class Tabular_MatrixXd : public MatrixXd{
//public:
//    Tabular_MatrixXd(string fileToOpen){
 //       MatrixXd
 //   }

//}

#endif // SPARSEMATRIX_H
