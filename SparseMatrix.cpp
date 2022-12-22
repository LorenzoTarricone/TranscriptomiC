//From: https://aleksandarhaber.com/eigen-matrix-library-c-tutorial-saving-and-loading-data-in-from-a-csv-file/
//Right now we can convert csv files into dense Eigen matrices. Next step is to take txt files as input and to implement Sparse matrices too.

#include <Eigen/Dense>
#include <fstream>
#include <vector>
#include <SparseMatrix.h>

using namespace std;
using namespace Eigen;

//this function saves a matrix to a csv file
void saveData(string fileName, MatrixXd  matrix)
{
    //https://eigen.tuxfamily.org/dox/structEigen_1_1IOFormat.html
    const static IOFormat CSVFormat(FullPrecision, DontAlignCols, ", ", "\n");

    ofstream file(fileName);
    if (file.is_open())
    {
        file << matrix.format(CSVFormat);
        file.close();
    }
};

MatrixXd openData(string fileToOpen)
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
    return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);

}

MatrixXd openData_strings(string fileToOpen,vector<string>& columnID, vector<string>& rowID)
{
    // the input is the file: "fileToOpen.csv"
    // This function converts input file data into the Eigen matrix format

    // the matrix entries are stored in this variable row-wise. For example if we have the matrix:
    // M=[a b c
    //    d e f]
    // the entries are stored as matrixEntries=[a,b,c,d,e,f], that is the variable "matrixEntries" is a row vector

    // later on, this vector is mapped into the Eigen matrix format
    vector<double> matrixEntries;
    bool header=true;

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
        if(header){
            while (getline(matrixRowStringStream, matrixEntry, ',')) // here we read pieces of the stream matrixRowStringStream until every comma, and store the resulting character into the matrixEntry
            {
                cout<<"pushed into columnID: "<<matrixEntry<<"\n";
                columnID.push_back(matrixEntry); //we add the first row to the columnID vector
            }
            header=false;
        }else{
            bool id=true;
            while (getline(matrixRowStringStream, matrixEntry, ',')) // here we read pieces of the stream matrixRowStringStream until every comma, and store the resulting character into the matrixEntry
            {
                if(id){
                    rowID.push_back(matrixEntry); //we add the first element of each row to the rowID vector.
                    id=false;
                }else{
                    matrixEntries.push_back(stod(matrixEntry));   //here we convert the string to double and fill in the row vector storing all the matrix entries
                }
            }
        }
        matrixRowNumber++; //this line allows us to count the number of rows. This will allow us to initialize a matrix of the right dimensions.
    }

    // here we convert the vector variable into the dynamic matrix and return the resulting object,
    // note that matrixEntries.data() is the pointer to the first memory location at which the entries of the vector matrixEntries are stored;
    return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);

}

