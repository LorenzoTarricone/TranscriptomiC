

#include "colocalisation.h"
#include "biologicalprocess.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //std::string path = "/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_development/InputData/test_data_single_cell/";
    std::string path = "/Users/alanpicucci/Desktop/Projects/Transcriptomics/TranscriptomiC/InputData/test_data_single_cell/";
    // path to names file
    std::string geneNameFile = path+"MBASS_dd99_genes.tsv";
    //path to beams file
    std::string spatialFile = path+"MBASS_dd99_spatial.csv";
    // path to expression matrix
    std::string expressionFile = path+"MBASS_dd99_expression_matrix.mtx";
    // path to gene subset file
    std::string geneSubsetFile = path+"MBASS_dd99_genes_subset_3.tsv";

    // initialize parse file object
    //parsefile files = parsefile();

    //files.readFiles(expressionFile, spatialFile, geneNameFile);

    // create colocalisation object
    //colocalisation matrix = colocalisation(files,1000,10);
    // add gene subset file
    //matrix.addGeneList(geneSubsetFile);
    // TODO set linkage parameters!!!
    // filter
    //matrix.filter_simple(true,0.001);
    //matrix.filter_genes();

//    // normalise data
//    matrix.normalisation();
//    // compute colocalisation matrix
//    matrix.compute();
//    //matrix.saveToFile(path+"colocalisation_object.csv");



////    files.~parsefile();


//    parsefile bp_files = parsefile();
//    bp_files.readFiles(expressionFile, spatialFile, geneNameFile);
//    // create colocalisation object
//    colocalisation matrix2 = colocalisation(bp_files);
//    // add gene subset file
//    matrix2.addGeneList(geneSubsetFile);
//    // TODO set linkage parameters!!!
//    // filter
//    matrix2.filter_simple(true,0.001);
//    matrix2.filter_genes();

//    // normalise data
//    matrix2.normalisation();
//    // compute colocalisation matrix
//    matrix2.compute();
//    //matrix.saveToFile(path+"colocalisation_object.csv");

//    files.~parsefile();
//    matrix.~colocalisation();

    parsefile bp_files = parsefile();
    bp_files.readFiles(expressionFile, spatialFile, geneNameFile);

    biologicalprocess bp = biologicalprocess(bp_files,100);
    bp.addGeneList(geneSubsetFile);
    bp.filter_simple(true,0.001);
    bp.filter_genes();
    //bp.compute_tot_expr();
    //bp.bioprocess_2(3);


////    std::cout << "[Progress] Final gene count for bp: "

    std::cout << "[Progress] Everything done!" << std::endl;

    return 0;
//    QApplication a(argc, argv);
//    UploadWindow w;
//    w.show();

}
