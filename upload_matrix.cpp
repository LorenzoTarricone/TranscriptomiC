#include "upload_matrix.h"
#include <fstream>
#include <sstream>
using namespace std;

upload_matrix::upload_matrix()
{

}

bool upload_matrix::setData_Matrix(std::string fileName){

        // the input is the file: "filename.csv"
        // This function converts input file data into the Eigen matrix format

        // the matrix entries are stored in this variable row-wise. For example if we have the matrix:
        // M=[a b c
        //    d e f]
        // the entries are stored as matrixEntries=[a,b,c,d,e,f], that is the variable "matrixEntries" is a row vector
        // later on, this vector is mapped into the Eigen matrix format
        vector<double> matrixEntries;

        // in this object we store the data from the matrix
        ifstream matrixDataFile(fileName);

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

        m = Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);

        return true;
    }
