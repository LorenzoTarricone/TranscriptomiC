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
    void filter(bool zeroes, double min_expr_perc);
    void filter_simple(Eigen::MatrixXd &expression,bool zeroes = true, double min_expr_perc = 0.05);
    Eigen::MatrixXd filterByGenes(const Eigen::MatrixXd &expression, std::vector<std::string> genes);
    void getRowNamesFromFile(std::string filename);
    void initiateGeneIndex(std::vector<std::string> geneList, std::vector<std::string> geneListSubset);
    void printGeneIndex(int rows);
    void normalisation(std::string type_of_normal = "col_mean");
    Eigen::MatrixXd normalisation_simple(Eigen::MatrixXd expression,std::string type_of_normal = "col_mean");
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
    std::map<std::string, int> geneIndexFinal;
    std::vector<std::string> all_names;
    std::vector<std::string> geneSubset;
    void shiftGeneIndex(int row, int removed);
    int N,M,removed;
};

// declarations of functions to remove certain row or column from eigen dense matrix
void removeRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove);

void removeColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove);

std::vector<std::string> listgene(std::string txt_file);

void printVector(std::vector<std::string> vec);

#endif // PARSEMTX_H
