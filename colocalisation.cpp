// this object will wrap all functionalities needed to compute the colocalisation matrix

#include "colocalisation.h"


colocalisation::colocalisation()
{
    geneNames = std::vector<std::string>();

    block_rows_start = 0;
    block_cols_start = 0;
    block_rows = 0;
    block_cols = 0;

}

colocalisation::~colocalisation(){
//    delete A_spatial;
    delete A_distance;
    delete A_linkage;
    delete A_combine;
    delete A_compare;
    delete A_colocalisation;
    delete expression;
}

void colocalisation::readFiles(std::string expressionFile, std::string spatialFile, std::string geneNameFile){
    // read beams and spatial information into parsing object
    spatial = parsing();
    std::cout << "[Progress] Reading spatial data ..." << std::endl;
    spatial.readBeamFileCSV(spatialFile);

    // convert object to eigen matrix
    std::cout << "[Progress] Converting spatial file to matrix ..." << std::endl;
    A_spatial = spatial.convertToMatrix();

    // read expression matrix
    expression_raw = parsemtx();
    std::cout << "[Progress] Reading expression matrix ..." << std::endl;
    expression_raw.readFile(expressionFile);
    std::cout << "[Progress] Finished reading expression matrix" << std::endl;

    // set default cropping to dimensions of the matrix
    if(def){
        block_rows = expression_raw.getRows();
        block_cols = expression_raw.getCols();
    }

    // read gene name file
    std::cout << "[Progress] Reading gene names file ..." << std::endl;
    geneNames = listgene(geneNameFile);
}


void colocalisation::setMatrixBlocks(int startRow, int startCol, int endRow, int endCol){
    block_rows_start = startRow;
    block_rows = endRow;
    block_cols_start = startCol;
    block_cols = endCol;

    def = false;
}

void colocalisation::setMatrixBlocks(int endRow, int endCol){
    setMatrixBlocks(0, 0, endRow, endCol);
}

void colocalisation::compute(std::string expressionFile, std::string spatialFile, std::string geneNameFile){
    // read files
    readFiles(expressionFile,spatialFile,geneNameFile);
    std::cout << "[Progress] File reading finished successfully ..." << std::endl;


    // compute colocalisation matrix
    step1();
    std::cout << "[Progress] Step 1 finished successfully ..." << std::endl;
    step2();
    std::cout << "[Progress] Step 2 finished successfully ..." << std::endl;
    step3();
    std::cout << "[Progress] Step 3 finished successfully ..." << std::endl;
    step4();
    std::cout << "[Progress] Step 4 finished successfully ..." << std::endl;
    step5();
    std::cout << "[Progress] Step 5 finished successfully ..." << std::endl;

}


void colocalisation::saveToFile(std::string filename){
    std::cout << "[Progress] Saving File ..." << std::endl;
    expression_raw.writeToFile(filename,*A_colocalisation);
}