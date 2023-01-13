#ifndef MATRIXEIGEN_H
#define MATRIXEIGEN_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <fstream>
#include <vector>
#include <random>

using namespace std;
using namespace Eigen;

//It would be nice to create a tabular_matrixXd class that inherits from Eigen::Dense and does the following: upon initialization
//it is given a csv or txt file to read. This file should be in tabular format, having strings which identify columns and rows. For instance,
//the gene expression matrix has bead names as column IDs and gene names as row IDs (or viceversa, but hopefully you get the idea). Our class
//would return the regular matrix of doubles the added feature of having two vectors of strings, one with the column IDs and one with the row IDs.
//Given these vectors, we should be able to navigate the matrix using these string identifiers.



class MatrixEigen
{
public:
    MatrixEigen();
    void openData(string filename);
    void generateRandomCSV(int n, int m, int start, int end, string filename);
    void printMatrix();
private:
    MatrixXd matrix;
};

double index(vector<string> ID, string element);

class Tabular_MatrixXd : private MatrixXd{
public:
    Tabular_MatrixXd();
    Tabular_MatrixXd(MatrixXd other_matrix);
    Tabular_MatrixXd(string filename);
    void todense();
    void filter(Eigen::SparseMatrix<double> expression_matrix, bool zeroes = true, double min_expr_perc = 0.1,std::string type_of_transcriptome = NULL);
    void getRowNamesFromFile(std::string filename);
    void normalisation(std::string type_of_normal = "col_mean");

private:
    MatrixXd matrix;
    Eigen::SparseMatrix<double> sparse;
    vector<string> rowID;
    vector<string> columnID;
};

#endif // MATRIXEIGEN_H

