#include "matrixeigen.h"
#include <Eigen/Dense>
#include <fstream>
#include <vector>
#include <random>
#include <iostream>

using namespace std;
using namespace Eigen;

MatrixEigen::MatrixEigen()
{
    MatrixXd matrix;
}



void MatrixEigen::openData(string fileToOpen)
{
    // the input is the file: "fileToOpen.csv"
    // This function converts input file data into the Eigen matrix format

    // the matrix entries are stored in this variable row-wise. For example if we have the matrix:
    // M=[a b c
    //    d e f]
    // the entries are stored as matrixEntries=[a,b,c,d,e,f], that is the variable "matrixEntries" is a row vector
    // later on, this vector is mapped into the Eigen matrix format
    vector<double> matrixEntries;

    // in this object we store the data from the matrix
    ifstream matrixDataFile(fileToOpen);

    // this variable is used to store the row of the matrix that contains commas
    string matrixRowString;

    // this variable is used to store the matrix entry;
    string matrixEntry;

    // this variable is used to track the number of rows
    int matrixRowNumber = 0;


    while (getline(matrixDataFile, matrixRowString)) // here we read a row by row of matrixDataFile and store every line into the string variable matrixRowString
    {
        stringstream matrixRowStringStream(matrixRowString); //convert matrixRowString that is a string to a stream variable.
        while (getline(matrixRowStringStream, matrixEntry, ',')) // here we read pieces of the stream matrixRowStringStream until every comma, and store the resulting character into the matrixEntry
        {
            matrixEntries.push_back(stod(matrixEntry));   //here we convert the string to double and fill in the row vector storing all the matrix entries
        }
        matrixRowNumber++; //this line allows us to count the number of rows. This will allow us to initialize a matrix of the right dimensions.
    }

    // here we convert the vector variable into the dynamic matrix and return the resulting object,
    // note that matrixEntries.data() is the pointer to the first memory location at which the entries of the vector matrixEntries are stored;
//    return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);

    matrix = Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);


}

void MatrixEigen::generateRandomCSV(int n, int m, int start, int end, string filename){
    // this method generates a csv file with m rows and n columns with doubles between start and end
    // the resulting csv is stored as a file with name filename

    // this operation sets the seed for the randomization (generates different values for each iteration)
    srand(time(nullptr));

    // file stream
    ofstream fout;

    // open file
    fout.open(filename);


    for(int i = 0; i < m; i++){ //for each row i

        for(int j = 0; j < n-1; j++){ // add n-1 random floating point values, separated by a comma
            fout << setprecision(3) << start + (double)(rand()) / ((double)(RAND_MAX/(end - start))) << ",";
        }
        // end each line with a last random value followed by a new line character \n
        fout << setprecision(3) << start + (double)(rand()) / ((double)(RAND_MAX/(end - start))) << "\n";
    }
    // close the file (stream)
    fout.close();

}

void MatrixEigen::printMatrix(){
//    cout << "matrix[0][0] = " << matrix(1,1) << endl;
    cout << "matrix = " << endl;
    cout << matrix << endl;
}
