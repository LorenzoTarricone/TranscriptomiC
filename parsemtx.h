#ifndef PARSEMTX_H
#define PARSEMTX_H

#include <string>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>

class parsemtx
{
public:
    parsemtx();
    void readFile(std::string filename);
    void print();
    void filter(Eigen::SparseMatrix<double> expression_matrix, bool zeroes = true, double min_expr_perc = 0.1,std::string type_of_transcriptome = NULL);

private:
    Eigen::MatrixXd matrix;
    Eigen::SparseMatrix<double> sparse;
};

#endif // PARSEMTX_H
