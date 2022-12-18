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

private:
    Eigen::MatrixXd matrix;
    Eigen::SparseMatrix<double> sparse;
};

#endif // PARSEMTX_H
