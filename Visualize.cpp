/*****************************************************************************************************************
 ** The goal is to read different files (txt or csv) and to visulize the data                                   **
 *****************************************************************************************************************
 ** Sources:                                                                                                    **
 ** 1. https://www.youtube.com/watch?v=TSRdO0AH9Gc                                                              **
 ** 2. https://www.geeksforgeeks.org/csv-file-management-using-c/                                               **
 ** 3. https://towardsdatascience.com/data-preprocessing-and-visualization-in-c-6d97ed236f3b                    **
 ****************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include "Visualize.hpp"
using namespace std;

//Right know we can only read data from the file fake_coordinates. The data is not really visualized. Its just printed.
void CSV :: read_csv_file(string myFilePath){
    ifstream coordinates;
    coordinates.open(myFilePath); // open a file to perform read operation

    if(coordinates.fail()){
        cerr << "Unable to open file" << myFilePath << endl; //checking whether the file is open
    }
    while(coordinates.peek() != EOF){ //loop over the coordinates and print them BUT WE WANT TO STORE THEM OR VISUALIZE THEM DIRECTLY
        string coordinate;
        getline(coordinates,coordinate,',');
        cout <<coordinate<< endl;
    }

    coordinates.close(); // Here we close the file
}

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

