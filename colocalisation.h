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
    colocalisation(): computation(){};
    colocalisation(parsefile files, int rows = 0, int cols = 0) : computation(files,rows,cols){};
    ~colocalisation();
    void compute();
    void saveToFile(std::string filename);
    void setM(double m){this->m = m;};
    void setP(double p){this->p = p;};

    Eigen::MatrixXd getColocalisationMatrix(){return *A_colocalisation;};


private:
    Eigen::MatrixXd* A_distance;
    Eigen::MatrixXd* A_linkage;
    Eigen::MatrixXd* A_combine;
    Eigen::MatrixXd* A_compare;
    Eigen::MatrixXd* A_colocalisation;
    std::string geneNamesFile, spatialFile, expressionFile;

    // linkage parameters
    double m = 5000;
    double p = 2;

    // private methods
    void step1();
    void step2();
    void step3();
    void step4();
    void step5();


};

#endif // COLOCALISATION_H
