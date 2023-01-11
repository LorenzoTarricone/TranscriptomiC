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
    void normalisation(std::string type_of_normal = "col_mean");
    void writeToFile(std::string filename);
    void writeToFile(std::string filename,Eigen::MatrixXd matrix);
    void createBeamFile(std::string file_out, std::string file_in = "");

    int getRows();
    int getCols();

    Eigen::MatrixXd getExpressionDense();


private:
    Eigen::MatrixXd matrix;
    Eigen::SparseMatrix<double> sparse;
    // from https://www.educba.com/c-plus-plus-dictionary/
    // map containing the gene names and respective row index
    // TODO: check if this is the ideal data type for this
    std::map<std::string, int> geneIndex;
    std::vector<std::string> all_names;
    void shiftGeneIndex(int row, int removed);
    int N,M;
};

// declarations of functions to remove certain row or column from eigen dense matrix
void removeRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove);

void removeColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove);

std::vector<std::string> listgene(std::string txt_file);

void printVector(std::vector<std::string> vec);

#endif // PARSEMTX_H
