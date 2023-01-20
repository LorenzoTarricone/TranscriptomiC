#ifndef PARSEFILE_H
#define PARSEFILE_H

#include "parsemtx.h"
#include "parsing.h"

class parsefile
{
public:
    parsefile();
    int readFiles(std::string expressionFile, std::string spatialFile, std::string geneNameFile);
    parsemtx getExpression();
    parsing getSpatial();
    std::vector<std::string> getGenes();
    std::vector<double> getExprX();
    std::vector<double> getExprY();
    std::vector<double> getExprVals();

private:
    parsemtx expression_raw;
    parsing spatial;
    std::vector<std::string> geneNames;
};


#endif // PARSEFILE_H
