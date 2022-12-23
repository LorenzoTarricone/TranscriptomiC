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
    // from https://www.educba.com/c-plus-plus-dictionary/
    // map containing the gene names and respective row index
    // TODO: check if this is the ideal data type for this
    std::map<std::string, int> geneIndex;
    std::vector<std::string> all_names;
    void shiftGeneIndex(int row, int removed);
};

#endif // PARSEMTX_H
