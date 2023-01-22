//read the input_gene.txt file and store names in a vector of strings 
//read the bio_pro_gene.txt file that the researcher will upload and only select the first x genes (x is a parameter) in the file and store them in a vector of strings

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

//read the input_gene.txt file and store names in a vector of strings 
std::vector<std::string> readgenetxt::listgene(std::string filename){
    std::vector<std::string> list;
    std::ifstream file;
    std::string line;

    file.open(filename); //open file
    if (file.peek() == std::ifstream::traits_type::eof()) {
        qDebug() << "Empty file!!";
    }
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
    } qDebug() << "reading txt file";
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string value;
        while (ss >> value) {
            list.push_back(value);
        }
    }
    file.close();
    return list;
}


//read the bio_pro_gene.txt file that the researcher will upload and only select the first x genes in the file and store them in a vector of strings
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



