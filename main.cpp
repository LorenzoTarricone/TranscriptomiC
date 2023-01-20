
#include "UploadWindow.h"
#include "colocalisation.h"
#include "biologicalprocess.h"
#include <QApplication>
//#include "readgenetxt.h"
//#include "only_gene_name.h"
//#include "read_tsv_set.h"
//#include "intersection_sets.h"
//#include "api.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include <QJsonDocument>
#include <set>


int main(int argc, char *argv[])
{
    std::string path = "/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_development/InputData/test_data_single_cell/";
//    std::string path = "/Users/alanpicucci/Desktop/Projects/Transcriptomics/TranscriptomiC/InputData/test_data_single_cell/";
    // path to names file
    std::string geneNameFile = path+"MBASS_dd99_genes.tsv";
    //path to beams file
    std::string spatialFile = path+"MBASS_dd99_spatial.csv";
    // path to expression matrix
    std::string expressionFile = path+"MBASS_dd99_expression_matrix.mtx";
    // path to gene subset file
    std::string geneSubsetFile = path+"MBASS_dd99_genes_subset_2.tsv";

//    QApplication a(argc, argv);
//    UploadWindow w;
//    w.show();
//    return a.exec();

//     initialize parse file object
    parsefile files = parsefile();

    files.readFiles(expressionFile, spatialFile, geneNameFile);

//     create colocalisation object
    colocalisation matrix = colocalisation(files,200,200);
//     add gene subset file
    matrix.addGeneList(geneSubsetFile);
//     TODO set linkage parameters!!!
//     filter
    matrix.filter_genes();
    matrix.filter_simple(true,0.001);


    // normalise data
    matrix.normalisation();
    // compute colocalisation matrix
    matrix.compute();
    matrix.saveToFile(path+"colocalisation_object.csv");

    std::cout << "[Progress] Colocalisation done!" << std::endl;


//    parsefile bp_files = parsefile();
//    bp_files.readFiles(expressionFile, spatialFile, geneNameFile);

//    biologicalprocess bp = biologicalprocess(files,400);
//    bp.addGeneList(geneSubsetFile);
//    bp.filter_simple(true,0.001);
//    bp.filter_genes();
//    bp.compute_tot_expr();
////    bp.bioprocess_2(50);



    std::cout << "[Progress] Everything done!" << std::endl;

    return 0;


}



// main function for API

//int main(){
//    //First we read the txt file with the gene name for a particular biologicl process
//    //And we take all the name of these genes

//    std::string txt_gene="/Users/nicolas/Documents/TranscriptomiC/list_gene_bio_pro.txt"; //txt file with gene names separated with spaces, tabs or lines
//    std::string line;
//    readgenetxt vec;
//    std::vector<std::string> res;
//    res=vec.listgene_bio_pro(txt_gene,500); //list of all the genes in the txt file, here 500 bc I want to test with only 500 genes linked to the biological process
//    std::cout<<"[";
//    for (const std::string& i : res) {
//        std::cout << i<<" ";
//      }
//    std::cout<<"]";

//    std::set<std::string> final_set;
//    for (unsigned int i=0; i<res.size();i++){
//        std::string search=res[i];
//        qDebug() << QString::fromStdString(search);
//        std::string l;
//        //API call

//        QMap<QString, QString> params;
//        params["terms"]= QString::fromStdString(search);
//        qDebug() <<params;
//        QJsonDocument doc = searchHGNC(params);
//        QString strJson(doc.toJson(QJsonDocument::Compact));
//        l=strJson.toStdString();
//        std::cout<<"THIS IS" << search<<l;

//        only_gene_name test; //search other name of this specific gene in the string l
//        std::set<std::string> small_set;
//        small_set=test.listgene(l, search);
//        test.printset(small_set);

//        final_set.insert(small_set.begin(), small_set.end()); //add the set of the names of this gene in the set of all the genes

//        std::cout<<'\n'<<"Set is: { "; //print final set
//        for(auto& str: final_set)
//          {
//            std::cout << str << ' ';
//          }
//        std::cout<<"}";

//    }

//    //Now let us create the set of all the gene of the matrix file
//    read_tsv_set test2;
//    std::set<std::string> string_set_gene_matrix;
//    string_set_gene_matrix=test2.read_tsv("D:\\CLEMENCE\\C++ project\\build-transcriptomics_development-Desktop_Qt_6_2_4_MinGW_64_bit-Debug\\gene_tsv.tsv");

//    //Now we take the intersection of the 2 sets, to keep only the genes we are interrested in
//    intersection_sets test3;
//    std::set<std::string> intersection_set;
//    intersection_set = test3.set_intersection(final_set, string_set_gene_matrix);

//    for (std::string x : intersection_set) {
//        std::cout << x << " ";
//    }

//    return 0;}



//#include "mainwindow.h"
//#include <QApplication>
//#include "api.cpp"

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    printExample();
//    MainWindow w;
//    w.show();
//    return a.exec();

////    parsemtx mtxobject = parsemtx();
////    mtxobject.readFile("mtx_test.mtx");
////    mtxobject.print();
////    return 0;
//}

