// this object will wrap all functionalities needed to compute the colocalisation matrix

#ifndef COLOCALISATION_H
#define COLOCALISATION_H


#include "parsemtx.h"
#include "parsing.h"
class colocalisation
{
public:
    colocalisation();
    ~colocalisation();
    void compute(std::string expressionFile, std::string spatialFile, std::string geneNameFile);
    void saveToFile(std::string filename);
    void setMatrixBlocks(int startRow, int startCol, int endRow, int endCol);
    void setMatrixBlocks(int endRow, int endCol);

private:
    parsemtx expression_raw;
    parsing spatial;
    std::vector<std::string> geneNames;
    Eigen::MatrixXd A_spatial;
    Eigen::MatrixXd* A_distance;
    Eigen::MatrixXd* A_linkage;
    Eigen::MatrixXd* A_combine;
    Eigen::MatrixXd* A_compare;
    Eigen::MatrixXd* A_colocalisation;
    Eigen::MatrixXd* expression;
    std::string geneNamesFile, spatialFile, expressionFile;

    // crop matrix
    int block_rows_start,block_cols_start,block_rows,block_cols;
    bool def = true;

    // linkage parameters
    double m = 5000;
    double p = 2;

    // private methods
    void readFiles(std::string expressionFile, std::string spatialFile, std::string geneNameFile);
    void step1();
    void step2();
    void step3();
    void step4();
    void step5();


};

#endif // COLOCALISATION_H
