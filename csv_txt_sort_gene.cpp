#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>

int sort_gene_txt_or_csv(std::set<std::string> set_names,std::string file_file_name) {
    std::set<std::string> names;  //create a set of names to test the code but will be the set that the final set the API function will return
    names.insert("name1");
    names.insert("name2");
    names.insert("name3");
    std::string file_name="file.csv"; //matrix file (txt or csv)

    std::string str_txt ("txt");
    std::string str_csv("csv");
    if (file_name.find(str_txt) != std::string::npos) {
        std::ifstream file(file_name); //open matrix txt file
        std::string line;

        std::ofstream outfile("txt_gene.txt", std::ios::app); // open a txt file in append mode

        while (std::getline(file, line)) {
            std::stringstream lineStream(line);
            std::string cell;
            std::getline(lineStream, cell, ' ');
            std::string name = cell;

            if (names.count(name) > 0) { // if name is in set, print the line
                std::cout << line << std::endl;
                //Write line to file
                outfile << line << std::endl;
            }
        }
    }
    //else if csv file
    else if(file_name.find(str_csv) != std::string::npos){
        std::ifstream file(file_name); //open matrix csv file
        std::string line;

        std::ofstream outfile("csv_gene.csv", std::ios::app); // open a csv file in append mode

        while (std::getline(file, line)) {
            std::stringstream lineStream(line);
            std::string cell;
            std::getline(lineStream, cell, ',');
            std::string name = cell;
            if (names.count(name) > 0) {
                std::cout << line << std::endl; // if name is in set, print the line
                // Write line to file
                outfile << line << std::endl;
            }

            else{
                std::cout<<"File is not valid, need to be either .txt or .csv";
            }
        }}


    return 0;
}
