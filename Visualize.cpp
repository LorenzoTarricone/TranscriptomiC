#include <iostream>
#include <fstream>
#include <string>
#include "Visualize.hpp"

using namespace std;

//Sources:
//1. https://www.youtube.com/watch?v=TSRdO0AH9Gc
//2. https://www.geeksforgeeks.org/csv-file-management-using-c/

//Goal: Read a csv file and visualize the data
//Right know we can only read data from the file fake_coordinates. The data is not really visualized. Its just printed.
void CSV :: read_csv_file(string myFilePath){
    ifstream coordinates;

    coordinates.open(myFilePath); // Here we open the file

    if(coordinates.fail()){
        cerr << "Unable to open file" << myFilePath << endl;
    }
    while(coordinates.peek() != EOF){ //loop over the coordinates and print them BUT WE WANT TO STORE THEM OR VISUALIZE THEM DIRECTLY
        string coordinate;
        getline(coordinates,coordinate,',');
        cout <<coordinate<< endl;
    }

    coordinates.close(); // Here we close the file
}
//Goal: Visualize csv file data
void CSV :: visualize_csv(){

}
//Goal: Read a txt file and visualize the data
//Right know we can only read data from the file fake_coordinates.
void TXT :: read_csv_file(string myFilePath){
    ifstream coordinates;

    coordinates.open(myFilePath);

    if(coordinates.fail()){
        cerr << "Unable to open file" << myFilePath << endl;
    }
    while(coordinates.peek() != EOF){
        string coordinate;
        getline(coordinates,coordinate,',');
        cout <<coordinate<< endl;
    }

    coordinates.close();
}
//Goal: Visualize csv file data
void TXT :: visualize_csv(){

}

