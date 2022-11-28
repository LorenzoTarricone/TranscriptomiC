#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Sources:
//1. https://www.youtube.com/watch?v=TSRdO0AH9Gc
//2. https://www.geeksforgeeks.org/csv-file-management-using-c/


void read_csv_file(){
    string myFilePath = "fake_coordinates.csv";

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
void visualize(){
    cout <<'Hello'<< endl;
}
