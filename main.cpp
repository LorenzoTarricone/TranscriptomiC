
#include "UploadWindow.h"
//#include "mainwindow.h"
#include "parsemtx.h"
#include "parsetxtbeams.h"
#include "matrixeigen.h"
#include "colocalization_matrix.h"
#include "parsing.h"
#include "colocalisation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    std::string path = "/Users/alanpicucci/Desktop/Projects/Transcriptomics/TranscriptomiC/InputData/test_data_single_cell/";
    // path to names file
    std::string geneNameFile = path+"MBASS_dd99_genes.tsv";
    //path to beams file
    std::string spatialFile = path+"MBASS_dd99_spatial.csv";
    // path to expression matrix
    std::string expressionFile = path+"MBASS_dd99_expression_matrix.mtx";
    // path to gene subset file
    std::string geneSubsetFile = path+"MBASS_dd99_genes_subset_2.tsv";

    // create colocalisation object
    colocalisation matrix = colocalisation();
    //crop data
    matrix.setMatrixBlocks(100,1000);

    // read files
    matrix.readFiles(expressionFile,spatialFile,geneNameFile, geneSubsetFile);


    // filter
    matrix.filter(true,0.001);


    // normalise data
    //matrix.normalisation();

    // compute colocalisation matrix
    //matrix.compute();

    //matrix.saveToFile(path+"colocalisation_object.csv");


    return 0;
//    QApplication a(argc, argv);
//    UploadWindow w;
//    w.show();

}
