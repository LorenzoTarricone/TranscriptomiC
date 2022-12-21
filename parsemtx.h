#ifndef PARSEMTX_H
#define PARSEMTX_H

#include <string>
#include <map>
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
    void getRowNamesFromFile(std::string filename);

private:
    Eigen::MatrixXd matrix;
    Eigen::SparseMatrix<double> sparse;
    // from https://www.educba.com/c-plus-plus-dictionary/
    // map containing the gene names and respective row index
    // TODO: check if this is the ideal data type for this
    std::map<std::string, int> geneIndex;
    std::vector<std::string> all_names;
};

#endif // PARSEMTX_H
