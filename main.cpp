#include "mainwindow.h"
#include "parsemtx.h"
#include "parsetxtbeams.h"
#include "matrixeigen.h"


#include <QApplication>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

//    MatrixEigen matrix_eigen =  MatrixEigen();
//    matrix_eigen.generateRandomCSV(10,10,0,1,"csv_test.csv");
//    std::cout << "Program path : " << argv[0] << std::endl;

    //parseTxtBeams tsv_object = parseTxtBeams();
    //tsv_object.createDummyFile(10,"tsv_test_2.tsv");
    //tsv_object.readFile("tsv_test_2.tsv");

    parsemtx mtxobject = parsemtx();
    std::string expressionFile = "/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_development/InputData/filtered_feature_bc_matrix/matrix.mtx";
    std::string beamInputFile = "/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_development/InputData/filtered_feature_bc_matrix/barcodes.tsv";
    std::string beamOutputFile = "/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_development/InputData/filtered_feature_bc_matrix/beams.tsv";

    mtxobject.readFile(expressionFile);
//    mtxobject.readFile("/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_development/InputData/filtered_feature_bc_matrix/matrix.mtx");
//    mtxobject.print();
//    mtxobject.writeToFile("expression_1.csv");
    mtxobject.createBeamFile(beamOutputFile,beamInputFile);

//  read beam file
    parseTxtBeams parsetxt = parseTxtBeams();
    parsetxt.readFile(beamOutputFile);
//  convert beam file to eigen matrix for colocalization computation
    Eigen::MatrixXd beam_matrix = parsetxt.convertToMatrix();




    return 0;
}
