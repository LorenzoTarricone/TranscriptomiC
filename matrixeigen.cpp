#include "matrixeigen.h"
#include <Eigen/Dense>
#include <fstream>
#include <iomanip>
#include <vector>
#include <random>
#include <iostream>

using namespace std;
using namespace Eigen;

MatrixEigen::MatrixEigen()
{
    MatrixXd matrix;
}



void MatrixEigen::openData(string filename)
{
    // the input is the file: "filename.csv"
    // This function converts input file data into the Eigen matrix format

    // the matrix entries are stored in this variable row-wise. For example if we have the matrix:
    // M=[a b c
    //    d e f]
    // the entries are stored as matrixEntries=[a,b,c,d,e,f], that is the variable "matrixEntries" is a row vector
    // later on, this vector is mapped into the Eigen matrix format
    vector<double> matrixEntries;

    // in this object we store the data from the matrix
    ifstream matrixDataFile(filename);

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
            fout << std::setprecision(3) << start + (double)(rand()) / ((double)(RAND_MAX/(end - start))) << ",";
        }
        // end each line with a last random value followed by a new line character \n
        fout << std::setprecision(3) << start + (double)(rand()) / ((double)(RAND_MAX/(end - start))) << "\n";
    }
    // close the file (stream)
    fout.close();

}

void MatrixEigen::printMatrix(){
//    cout << "matrix[0][0] = " << matrix(1,1) << endl;
    cout << "matrix = " << endl;
    cout << matrix << endl;
}

Tabular_MatrixXd::Tabular_MatrixXd(){
    MatrixXd matrix;
}

Tabular_MatrixXd::Tabular_MatrixXd(MatrixXd other_matrix){
    matrix=other_matrix;
}

//Initialize the table class by reading from a file: depending on the format, different approaches are used.
Tabular_MatrixXd::Tabular_MatrixXd(string filename){
    if(filename.substr(filename.find_last_of(".") + 1) == "mtx"){
        // from https://cplusplus.com/forum/general/65804/
        // an mtx file stores data from a sparse matrix in throuples (x,y,value)

        // initialize filestream
        std::ifstream fin(filename);

        // Declare variables:
        int M, N, L;

        // Ignore headers and comments:
        while (fin.peek() == '%') fin.ignore(2048, '\n');

        // Read defining parameters:
        fin >> M >> N >> L;

        // from https://eigen.tuxfamily.org/dox/group__TutorialSparse.html
        typedef Eigen::Triplet<double> T;
        std::vector<T> tripletList;
        int  estimation_of_entries = (int) ((1-0.98) * M * N);
        tripletList.reserve(estimation_of_entries);

        // Read the data
        for (int l = 0; l < L; l++)
        {
            int m, n;
            double data;
            fin >> m >> n >> data;
            tripletList.push_back(T(m,n,data));

        }

        // close file
        fin.close();

        // initialize sparse matrix object of the correct size
        Eigen::SparseMatrix<double> sparseMatrix(M,N);

        // fill sparse matrix object using the vector of triplets from the file reading
        sparseMatrix.setFromTriplets(tripletList.begin(), tripletList.end());

        // make the private member sparse of the object point to the sparse matrix we just created
        this->sparse = sparseMatrix;
    }else if (filename.substr(filename.find_last_of(".") + 1) == "csv"){
        // the input is the file: "filename.csv"
        // This function converts input file data into the Eigen matrix format

        // the matrix entries are stored in this variable row-wise. For example if we have the matrix:
        // M=[a b c
        //    d e f]
        // the entries are stored as matrixEntries=[a,b,c,d,e,f], that is the variable "matrixEntries" is a row vector

        // later on, this vector is mapped into the Eigen matrix format
        vector<double> matrixEntries;
        bool header=true;

        // in this object we store the data from the matrix
        ifstream matrixDataFile(filename);

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
                    this->columnID.push_back(matrixEntry); //we add the first row to the columnID vector
                }
                header=false;
            }else{
                bool id=true;
                while (getline(matrixRowStringStream, matrixEntry, ',')) // here we read pieces of the stream matrixRowStringStream until every comma, and store the resulting character into the matrixEntry
                {
                    if(id){
                        this->rowID.push_back(matrixEntry); //we add the first element of each row to the rowID vector.
                        id=false;
                    }else{
                        matrixEntries.push_back(stod(matrixEntry));   //here we convert the string to double and fill in the row vector storing all the matrix entries
                    }
                }
                matrixRowNumber++; //this line allows us to count the number of rows. This will allow us to initialize a matrix of the right dimensions.
            }

        }

        // here we convert the vector variable into the dynamic matrix and return the resulting object,
        // note that matrixEntries.data() is the pointer to the first memory location at which the entries of the vector matrixEntries are stored;
        this->matrix = Eigen::Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);
    }else{
        cout<<" \n not implemented \n" <<endl;
    }
}

void Tabular_MatrixXd::todense(){
    matrix=MatrixXd(sparse);
}

//This function returns the index of "element" in the vector "ID", which can be either the rowID or columnID.
double index(vector<string> ID, string element){
    return (find(ID.begin(), ID.end(), element) - ID.begin());
}

