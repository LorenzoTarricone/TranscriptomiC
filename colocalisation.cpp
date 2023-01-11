// this object will wrap all functionalities needed to compute the colocalisation matrix

#include "colocalisation.h"

colocalisation::colocalisation()
{
    expression_raw = new parsemtx();
    spatial = new parsing;
    geneNames = std::vector<std::string>();

}

colocalisation::~colocalisation(){
    delete A_distance;
    delete A_linkage;
    delete A_combine;
    delete A_compare;
    delete A_colocalisation;
}

void colocalisation::readFiles(std::string expressionFile, std::string spatialFile, std::string geneNameFile){
    // read beams and spatial information into parsing object
    *(spatial) = (parsing());
    spatial->readBeamFileCSV(spatialFile);

    //
}

void colocalisation::compute(std::string expressionFile, std::string spatialFile, std::string geneNameFile){

}
