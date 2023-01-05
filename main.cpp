#include "readgenetxt.h"
#include "only_gene_name.h"
#include "api.cpp"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include <QJsonDocument>

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::istringstream;
using std::stringstream;

using namespace std;


int main(){
    string txt_gene="/Users/nicolas/Documents/TranscriptomiC/list_gene.txt"; //txt file with gene names separated with spaces, tabs or lines
    string line;
    readgenetxt vec;
    vector<string> res;
    res=vec.listgene(txt_gene); //list of all the genes in the txt file
    cout<<"[";
    for (const string& i : res) {
        cout << i<<" ";
      }
    cout<<"]";

    set<string> final_set;
    for (unsigned int i=0; i<res.size();i++){
        string search=res[i];
        qDebug() << QString::fromStdString(search);
        string l;
        //API call

        QMap<QString, QString> params;
        params["terms"]= QString::fromStdString(search);
        qDebug() <<params;
        QJsonDocument doc = searchHGNC(params);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        l=strJson.toStdString();
        cout<<"THIS IS" << search<<l;

        only_gene_name test; //search other name of this specific gene in the string l
        set<string> small_set;
        small_set=test.listgene(l, search);
        test.printset(small_set);

        final_set.insert(small_set.begin(), small_set.end()); //add the set of the names of this gene in the set of all the genes

        cout<<'\n'<<"Set is: { "; //print final set
        for(auto& str: final_set)
          {
            std::cout << str << ' ';
          }
        cout<<"}";
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
