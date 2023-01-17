// this object will wrap all functionalities needed to compute the colocalisation matrix

#ifndef COLOCALISATION_H
#define COLOCALISATION_H


#include "parsemtx.h"
#include "parsing.h"
#include "parsefile.h"
#include "computation.h"


class colocalisation : public computation
{
public:
    colocalisation(parsefile files, int rows = 0, int cols = 0) : computation(files,rows,cols){};
    ~colocalisation();
//    void filter(bool zeroes = true, double min_expr_perc = 0.1);
//    void normalisation(std::string type_of_normal = "col_mean");
//    void addGeneList(std::string geneListPath);
//    void test(bool def = true);
//    void readFiles(std::string expressionFile, std::string spatialFile, std::string geneNameFile, std::string geneSubsetFile);
    void compute();
    void saveToFile(std::string filename);
//    void setMatrixBlocks(int startRow, int startCol, int endRow, int endCol);
//    void setMatrixBlocks(int endRow, int endCol);

private:
//    parsemtx expression_raw;
//    parsing spatial;
//    std::vector<std::string> geneNames;



//    Eigen::MatrixXd A_spatial;
    Eigen::MatrixXd* A_distance;
    Eigen::MatrixXd* A_linkage;
    Eigen::MatrixXd* A_combine;
    Eigen::MatrixXd* A_compare;
    Eigen::MatrixXd* A_colocalisation;
//    Eigen::MatrixXd* expression;
    std::string geneNamesFile, spatialFile, expressionFile;

//    // crop matrix
//    void initialise(int rows, int cols);
//    int block_rows_start,block_cols_start,block_rows,block_cols;
//    bool def = true;

    // linkage parameters
    double m = 5000;
    double p = 2;

//    // filter parameters
//    std::vector<std::string> geneSubset;
//    bool filterGenes = false;

    // private methods
    void step1();
    void step2();
    void step3();
    void step4();
    void step5();


};

#endif // COLOCALISATION_H
