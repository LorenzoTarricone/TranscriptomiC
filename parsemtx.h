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

    Eigen::MatrixXd filter_simple(Eigen::MatrixXd &expression,bool zeroes = true, double min_expr_perc = 0.05);
    Eigen::MatrixXd filterByGenes(const Eigen::MatrixXd &expression, std::vector<std::string> genes);

    void getRowNamesFromFile(std::string filename);

    void initiateGeneIndex(std::vector<std::string> geneList);
    void initiateGeneSubset(std::vector<std::string> geneListSubset);
    void printGeneIndex(int rows);

    Eigen::MatrixXd normalisation_simple(Eigen::MatrixXd expression,std::string type_of_normal = "col_mean");

    void writeToFile(std::string filename, bool names = true);
    void writeToFile(std::string filename,Eigen::MatrixXd matrix, std::vector<std::string> genes, bool names = true);

    bool geneIndexEmpty();
    void initiateGeneIndex_cropped(std::vector<std::string> geneList, int row_crop);
    Eigen::SparseMatrix<double> getSparse();
    std::vector<std::string> getcurrentGenes();


    int getRows();
    int getCols();

    Eigen::MatrixXd getExpressionDense();


private:
    Eigen::MatrixXd matrix;
    Eigen::SparseMatrix<double> sparse;
    std::map<std::string, int> geneIndex;
    std::vector<std::string> all_names;
    std::vector<std::string> currentGenes;
    std::vector<std::string> geneSubset;
    void shiftGeneIndex(int row);
    int N,M,removed;

};

std::vector<std::string> listgene(std::string txt_file);

void printVector(std::vector<std::string> vec);

#endif // PARSEMTX_H
