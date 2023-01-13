
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
    QApplication a(argc, argv);
    UploadWindow w;
    w.show();

    // Test Eigen library and to plot a heatmap using a fake-colcalization matrix
        //Fake Colocalization Matrix
        /*MatrixXd m(5,5);
          m(0,0) = 0.3;
          m(0,1) = 0.5;
          m(0,2) = -1;
          m(0,3) = 0.6;
          m(0,4) = 0;
          m(1,0) = 1,
          m(1,1) = 0.7;
          m(1,2) = 0.2;
          m(1,3) = 0.4;
          m(1,4) = -0.7;
          m(2,0) = -1;
          m(2,1) = 1;
          m(2,2) = 0.5;
          m(2,3) = 0.8;
          m(2,4) = -0.9;
          m(3,0) = -1;
          m(3,1) = 1;
          m(3,2) = 0.5;
          m(3,3) = 0.8;
          m(3,4) = -0.9;
          m(4,0) = -1;
          m(4,1) = 1;
          m(4,2) = 0.5;
          m(4,3) = 0.8;
          m(4,4) = -0.9;
          fake_colocalization_matrix fake = fake_colocalization_matrix(m);
          fake.setdata();
          SecondWindow s;
          s.setX(fake.getX());
          s.setY(fake.getY());
          s.setP(fake.getP());
          s.makePlot();
          s.show();
          */



    return a.exec();

//    // path to data
////    std::string path = "/Users/alanpicucci/Desktop/Projects/Transcriptomics/TranscriptomiC/InputData/filtered_feature_bc_matrix/";
//    std::string path = "/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_development/InputData/test_data_single_cell/";

//    // path to names file
//    std::string geneNameFile = path+"MBASS_dd99_genes.tsv";

//    //path to beams file
//    std::string spatialFile = path+"MBASS_dd99_spatial.csv";

    // path to expression matrix
//    std::string expressionFile = path+"MBASS_dd99_expression_matrix.mtx";


//    // create parsing object
//    parsing beams = parsing();

//    // read beam file
//    std::cout << "[Progress] Reading beam file ..." << std::endl;
//    beams.readBeamFileCSV(spatialFile);

//    // convert object to eigen matrix
//    std::cout << "[Progress] Converting beams file to matrix ..." << std::endl;
//    Eigen::MatrixXd beam_matrix = beams.convertToMatrix();


//    // create colocalisation object
//    colocalisation matrix = colocalisation();

//    //crop data
//    matrix.setMatrixBlocks(10,10);

//    // read files
//    matrix.compute(expressionFile,spatialFile,geneNameFile);

    //std::cout << "[Progress] Reading gene names file ..." << std::endl;
    // read geneNames file
    //std::vector<std::string> geneNames = listgene(geneNamesFile);

    //std::cout << "[Progress] Reading gene names file finished. Contents: " << std::endl;
    //printVector(geneNames);


//    //read beam file
//    parseTxtBeams parsetxt = parseTxtBeams();
//    parsetxt.readFile(beamFile);
//    //convert beam file to eigen matrix for colocalization computation
//    Eigen::MatrixXd beam_matrix = parsetxt.convertToMatrix();

//    // create parsing object
//    parsing beams = parsing();

//    // read beam file
//    std::cout << "[Progress] Reading beam file ..." << std::endl;
//    beams.readBeamFileCSV(beamFile);

//    // convert object to eigen matrix
//    std::cout << "[Progress] Converting beams file to matrix ..." << std::endl;
//    Eigen::MatrixXd beam_matrix = beams.convertToMatrix();




//    // paths to expression matrix
//    parsemtx mtxobject = parsemtx();

//    mtxobject.readFile("mtx_test.mtx");
//    mtxobject.print();
//    return 0;
//    std::string expressionFile = path+"matrix.mtx";
//    std::cout << "[Progress] Reading expression matrix ..." << std::endl;
//    mtxobject.readFile(expressionFile);
//    std::cout << "[Progress] Finished reading expression matrix" << std::endl;
////    mtxobject.print();

////    return construct_colocalisation_matrix();
//    //  step 1 - create distance matrix
//    std::cout << "[Progress] Running step 1 ..." << std::endl;
//    Eigen::MatrixXd* A_distance = new Eigen::MatrixXd;
//    // now this is 10x10 matrix
//    *A_distance = matrix_distance(beam_matrix.block(0,0,10,2));



//    // step 2 - linkage matrix with parameters m and p
//    double m = 5000;
//    double p = 2;
//    std::cout << "[Progress] Running step 2 ..." << std::endl;
//    Eigen::MatrixXd* A_linkage = new Eigen::MatrixXd;
//    *A_linkage = matrix_linkage(*A_distance, m, p);

//    delete A_distance;

//    std::cout<<(*A_linkage).block(0,0,10,10)<<std::endl;
//    std::cout<<"\nLinkage matrix shape: (" << (*A_linkage).rows() << ", " << (*A_linkage).cols() << ")"<<std::endl;


//    //  step 3 - apply linkage to expression matrix -> neighbouring matrix
//    Eigen::MatrixXd expression =  mtxobject.getExpressionDense().block(0,0,10,10);


//    std::cout<<expression.block(0,0,10,10)<<std::endl;
//    std::cout<<"Expression matrix shape: (" << expression.rows() << ", " << expression.cols() << ")\n"<<std::endl;

//    std::cout << "[Progress] Running step 3 ..." << std::endl;
//    Eigen::MatrixXd* A_combine = new Eigen::MatrixXd;
//    *A_combine = combine_linkage(*A_linkage,(expression));

//    delete A_linkage;

//    std::cout<<(*A_combine).block(0,0,10,10)<<std::endl;
//    std::cout<<"\nCombine matrix shape: (" << (*A_combine).rows() << ", " << (*A_combine).cols() << ")"<<std::endl;

//    //  step 4 - compare expression and neighbouring matrices (with default parameters
//    std::cout << "[Progress] Running step 4 ..." << std::endl;
//    Eigen::MatrixXd A_compare = comparison(expression, *A_combine);

//    delete A_combine;

//    std::cout<<A_compare.block(0,0,10,10)<<std::endl;
//    std::cout<<"\n Comparison matrix shape: (" << A_compare.rows() << ", " << A_compare.cols() << ")"<<std::endl;

//    // step 5 and 6 - generate colocalisation matrix containing enrichement scores
//    std::cout << "[Progress] Running step 5 ..." << std::endl;
//    Eigen::MatrixXd A_colocalisation = enrichment(A_compare);

//    std::cout<<A_colocalisation.block(0,0,10,10)<<std::endl;
//    std::cout<<"\n Colocalisation matrix shape: (" << A_colocalisation.rows() << ", " << A_colocalisation.cols() << ")"<<std::endl;

//    //  save colocalisation matrix

//    std::cout << "[Progress] Saving File ..." << std::endl;
//    std::string colocalisationFile = path + "colocalisation.csv";
//    mtxobject.writeToFile(colocalisationFile,A_colocalisation);


//    return 0;
}
