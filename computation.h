#ifndef COMPUTATION_H
#define COMPUTATION_H

#include "parsefile.h"


class computation
{
public:
    computation(parsefile files,int rows = 0, int cols = 0);
    void filter_simple(bool zeroes = true, double min_expr_perc = 0.1);
    void filter_genes();
    void normalisation(std::string type_of_normal = "col_mean");
    void addGeneList(std::string geneListPath);
    void addGeneList(std::vector<std::string> geneList);
    void saveToFile(std::string filename);
    std::vector<std::string> getcurrentGenes();

protected:
    parsemtx expression_raw;
    parsing spatial;
    std::vector<std::string> geneNames, geneSubset;

    Eigen::MatrixXd A_spatial;

    Eigen::MatrixXd* expression;

    // crop matrix
    void initialise(int rows, int cols);
    int block_rows_start,block_cols_start,block_rows,block_cols;
    bool def = true;

    // filter parameters
    bool filterGenes = false;



};

#endif // COMPUTATION_H
