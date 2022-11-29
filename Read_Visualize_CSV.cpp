#include <iostream>
#include <fstream>
#include <string>


using namespace std;

//Sources:
//1. https://www.youtube.com/watch?v=TSRdO0AH9Gc
//2. https://www.geeksforgeeks.org/csv-file-management-using-c/

//read a csv file called fake_coordinates (2D)
void read_csv_file(){
    string myFilePath = "fake_coordinates.csv";
    ifstream coordinates;

    coordinates.open(myFilePath);

    if(coordinates.fail()){
        cerr << "Unable to open file" << myFilePath << endl;
    }
    while(coordinates.peek() != EOF){ //loop over the coordinates and print them
        string coordinate;
        getline(coordinates,coordinate,',');
        cout <<coordinate<< endl;
    }

    coordinates.close();
}
// how do we want to visualize it ?
void visualize_csv(){

}
