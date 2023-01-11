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

private:
    parsemtx* expression_raw;
    parsing* spatial;
    std::vector<std::string> geneNames;
    Eigen::MatrixXd* A_distance;
    Eigen::MatrixXd* A_linkage;
    Eigen::MatrixXd* A_combine;
    Eigen::MatrixXd* A_compare;
    Eigen::MatrixXd* A_colocalisation;
    std::string geneNamesFile, spatialFile, expressionFile;
    int matrix_block = 0;
    // linkage parameters
    double m = 5000;
    double p = 2;

    // private methods
    void readFiles(std::string expressionFile, std::string spatialFile, std::string geneNameFile);
};

#endif // COLOCALISATION_H
