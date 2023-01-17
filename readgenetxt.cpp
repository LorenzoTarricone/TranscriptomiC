<<<<<<< Updated upstream
/*
 * #include "readgenetxt.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

//read gene txt
int main(){
    string txt_gene="list_gene.txt";

    readgenetxt vec;
    vector<string> res;
    res=vec.listgene(txt_gene);
    cout<<"[";
    for (const string& i : res) {
        cout << i<<" ";
      }
    cout<<"]";
    return 0;}

//read gene of bio process

int main(){
    string txt_gene="D:\\CLEMENCE\\C++ project\\build-transcriptomics_development-Desktop_Qt_6_2_4_MinGW_64_bit-Debug\\list_gene_bio_process_mitochondrion_inheritance.txt";

    readgenetxt vec;
    vector<string> res;
    int nb_gene=100; //normally the right value will be 500
    res=vec.listgene_bio_pro(txt_gene,nb_gene);
    cout<<"[";
    for (const string& i : res) {
        cout << i<<" ";
      }
    cout<<"]";
    return 0;}

*/

#include "readgenetxt.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include <QDebug>


readgenetxt::readgenetxt()
{
    std::vector<std::string> list;
}


std::vector<std::string> readgenetxt::listgene(std::string filename){
    std::vector<std::string> list;
    std::ifstream file;
    std::string line;
    std::cout<<"code";
    file.open(filename); //open file
    if (file.peek() == std::ifstream::traits_type::eof()) {
        qDebug() << "Empty file!!";
    }
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
    } qDebug() << "reading txt file";
    while (getline(file, line)) {
        qDebug() << "got line!";
        qDebug() << QString::fromStdString(line);
        std::stringstream ss(line);
        std::string value;
        while (ss >> value) {
            list.push_back(value);
        }
    }

    file.close();
    return list;
}



std::vector<std::string> readgenetxt::listgene_bio_pro(std::string filename, int nb_gene){
    std::vector<std::string> list;
    std::ifstream file;
    std::string line;
    int i=0;
    file.open(filename); //open file
    if (file.peek() == std::ifstream::traits_type::eof()) {
        qDebug() << "Empty file!!";
    }
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
    }
    while (getline(file, line)) {

        std::stringstream ss(line);
        std::string value;
        while (ss >> value) {
            if (i<nb_gene){
                value.pop_back();
                list.push_back(value);
                i+=1;
            }
            else{
                file.close();
                return list;
            }

        }
    }

    file.close();
    return list;
}




=======
/*
 * #include "readgenetxt.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

//read gene txt
int main(){
    string txt_gene="list_gene.txt";

    readgenetxt vec;
    vector<string> res;
    res=vec.listgene(txt_gene);
    cout<<"[";
    for (const string& i : res) {
        cout << i<<" ";
      }
    cout<<"]";
    return 0;}

//read gene of bio process

int main(){
    string txt_gene="D:\\CLEMENCE\\C++ project\\build-transcriptomics_development-Desktop_Qt_6_2_4_MinGW_64_bit-Debug\\list_gene_bio_process_mitochondrion_inheritance.txt";

    readgenetxt vec;
    vector<string> res;
    int nb_gene=100; //normally the right value will be 500
    res=vec.listgene_bio_pro(txt_gene,nb_gene);
    cout<<"[";
    for (const string& i : res) {
        cout << i<<" ";
      }
    cout<<"]";
    return 0;}

*/

#include "readgenetxt.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include <QDebug>


readgenetxt::readgenetxt()
{
    std::vector<std::string> list;
}


std::vector<std::string> readgenetxt::listgene(std::string filename){
    std::vector<std::string> list;
    std::ifstream file;
    std::string line;
    std::cout<<"code";
    file.open(filename); //open file
    if (file.peek() == std::ifstream::traits_type::eof()) {
        qDebug() << "Empty file!!";
    }
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
    } qDebug() << "reading txt file";
    while (getline(file, line)) {
        qDebug() << "got line!";
        qDebug() << QString::fromStdString(line);
        std::stringstream ss(line);
        std::string value;
        while (ss >> value) {
            list.push_back(value);
        }
    }

    file.close();
    return list;
}



std::vector<std::string> readgenetxt::listgene_bio_pro(std::string filename, int nb_gene){
    std::vector<std::string> list;
    std::ifstream file;
    std::string line;
    int i=0;
    file.open(filename); //open file
    if (file.peek() == std::ifstream::traits_type::eof()) {
        qDebug() << "Empty file!!";
    }
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
    }
    while (getline(file, line)) {

        std::stringstream ss(line);
        std::string value;
        while (ss >> value) {
            if (i<nb_gene){
                value.pop_back();
                list.push_back(value);
                i+=1;
            }
            else{
                file.close();
                return list;
            }

        }
    }

    file.close();
    return list;
}




>>>>>>> Stashed changes
