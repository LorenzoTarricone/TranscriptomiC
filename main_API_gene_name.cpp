/* Take a file.txt (list of specific gene he wants to study from a researcher) and a file.tsv (gene present in the matrix table)
 * and returns a set with all the different possible names of these genes that are also present in the matrix table
 *
 * #include "readgenetxt.h"
#include "only_gene_name.h"
#include "read_tsv_set.h"
#include "intersection_sets.h"
#include "api.cpp"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include <QJsonDocument>



int main(){
    std::string txt_gene="/Users/nicolas/Documents/TranscriptomiC/list_gene.txt"; //txt file with gene names separated with spaces, tabs or lines
    std::string line;
    readgenetxt vec;
    std::vector<std::string> res;
    res=vec.listgene(txt_gene); //list of all the genes in the txt file
    std::cout<<"[";
    for (const std::string& i : res) {
        std::cout << i<<" ";
      }
    std::cout<<"]";

    std::set<std::string> final_set;
    for (unsigned int i=0; i<res.size();i++){
        std::string search=res[i];
        qDebug() << QString::fromStdString(search);
        std::string l;
        //API call

        QMap<QString, QString> params;
        params["terms"]= QString::fromStdString(search);
        qDebug() <<params;
        QJsonDocument doc = searchHGNC(params);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        l=strJson.toStdString();
        std::cout<<"THIS IS" << search<<l;

        only_gene_name test; //search other name of this specific gene in the string l
        std::set<std::string> small_set;
        small_set=test.listgene(l, search);
        test.printset(small_set);

        final_set.insert(small_set.begin(), small_set.end()); //add the set of the names of this gene in the set of all the genes

        std::cout<<'\n'<<"Set is: { "; //print final set
        for(auto& str: final_set)
          {
            std::cout << str << ' ';
          }
        std::cout<<"}";
    }

    //Now let us create the set of all the gene of the matrix file
    read_tsv_set test2;
    std::set<std::string> string_set_gene_matrix;
    string_set_gene_matrix=test2.read_tsv("D:\\CLEMENCE\\C++ project\\build-transcriptomics_development-Desktop_Qt_6_2_4_MinGW_64_bit-Debug\\gene_tsv.tsv");

    //Now we take the intersection of the 2 sets, to keep only the genes we are interrested in
    intersection_sets test3;
    std::set<std::string> intersection_set;
    intersection_set = test3.set_intersection(final_set, string_set_gene_matrix);

    small_set.~set();
    res.~vector();
    final_set.~set();
    string_set_gene_matrix.~set();

    for (std::string x : intersection_set) {
        std::cout << x << " ";
    }

    return 0;}



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

*/