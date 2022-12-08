/*****************************************************************************************************************
 ** The goal is to read different files (txt or csv) and to visulize the data                                   **
 *****************************************************************************************************************
 ** Sources:                                                                                                    **
 ** 1. https://www.youtube.com/watch?v=TSRdO0AH9Gc                                                              **
 ** 2. https://www.geeksforgeeks.org/csv-file-management-using-c/                                               **
 ** 3. https://towardsdatascience.com/data-preprocessing-and-visualization-in-c-6d97ed236f3b                    **
 ** 4. https://stackoverflow.com/questions/5449407/calculating-sums-of-columns-in-csv-file-using-c              **
 ** 5. https://stackoverflow.com/questions/34218040/how-to-read-a-csv-file-data-into-an-array                   **
 ****************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include "Visualize.hpp"
using namespace std;

void CSV :: visualize_csv(){

}

//Right know we can only read data from the file fake_coordinates.
void TXT :: read_txt_file(string myFilePath){
    ifstream coordinates;
    coordinates.open(myFilePath); //open a file to perform read operation

    if(coordinates.fail()){
        cerr << "Unable to open file" << myFilePath << endl; //checking whether the file is open
    }

    string coordinate;
    while(getline(coordinates, coordinate)){ //read data from file object and put it into string.
         cout << coordinate << endl; // prints the data
    }
    coordinates.close(); //close the file object.
}

void TXT :: visualize_txt(){

}

void CSV :: read_corr_file(){
    std::ifstream data("fake-corr-chart");
    std::string line;
    std::vector<std::vector<std::string> > read_corr_file;
    while(std::getline(data,line))
    {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<std::string> corrRow;
        while(std::getline(lineStream,cell,','))
        {
            corrRow.push_back(cell);
        }

        read_corr_file.push_back(corrRow);
    }
};


