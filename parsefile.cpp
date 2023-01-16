#include "parsefile.h"

parsefile::parsefile()
{

}

int parsefile::readFiles(std::string expressionFile, std::string spatialFile, std::string geneNameFile){
    // read beams and spatial information into parsing object
    spatial = parsing();
    try {
        std::cout << "[Progress] Reading spatial data ..." << std::endl;
        spatial.readBeamFileCSV(spatialFile);
    } catch(...) {
        std::cerr << "[Error] Reading spatial data failed ..." << std::endl;
      return 1;
    }

    // read expression matrix
    expression_raw = parsemtx();
    try {
        std::cout << "[Progress] Reading expression matrix ..." << std::endl;
        expression_raw.readFile(expressionFile);
        std::cout << "[Progress] Finished reading expression matrix" << std::endl;
    } catch(...) {
        std::cerr << "[Error] Reading expression matrix failed ..." << std::endl;
        return 2;
    }


    // read gene name file
    try {
        std::cout << "[Progress] Reading gene names file ..." << std::endl;
        geneNames = listgene(geneNameFile);
    } catch(...) {
        std::cerr << "[Error] Reading gene names file failed ..." << std::endl;
        return 3;
    }

    std::cout << "[Progress] File reading finished successfully ..." << std::endl;
    return 0;

}
parsemtx parsefile::getExpression(){
    return expression_raw;
}
parsing parsefile::getSpatial(){
    return spatial;
}
std::vector<std::string> parsefile::getGenes(){
    return geneNames;
}
