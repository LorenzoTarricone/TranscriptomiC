#include "filedata.h"
#include <fstream>
#include <sstream>
using namespace std;
FileData::FileData()
{

}

bool FileData::readSpatial(string fileName){

    /*This function opens a file and reads it into three vectors for x, y, and p values.
     * It is used for the inital data upload, and then the data is used for plotting the scatterplot
     * and heatmaps.
     */
    string x;
    string y;
    string p;
    string row;

    //clears the three vectors in case they had been used before
    xCoordinates.clear();
    yCoordinates.clear();
    pValues.clear();

    //opens the file
    ifstream coordinates;
    coordinates.open(fileName);

    if(coordinates.fail()){return false;}; //in case the file is not found

    string line = "";

    //reads and parses the file datapoint by datapoint into the vectors
    while(getline(coordinates, line)){
        stringstream s(line);

        getline(s, x, ',');
        getline(s, y, ',');
        getline(s, p);

        double xx = atof(x.c_str());
        double yy = atof(y.c_str());
        double pp = atof(p.c_str());


        xCoordinates.push_back(xx);
        yCoordinates.push_back(yy);
        pValues.push_back(pp);

        x="";
        y="";
        p="";

        line="";
    }

    coordinates.close();

    return true;
}

bool FileData::readGenes(string fileName){

    /*This function opens a file and reads it into one vector with the names of the genes to analyze.
     * It is used in the colocalization window, because the user will upload a file with the genes
     * that they want to analyze. This function handles the parsing of that file.
     */
    string g;

    genesToAnalyze.clear();

    ifstream genes;
    genes.open(fileName);

    if(genes.fail()){return false;}; //in case the file is not found

    string line = "";

    //reads and parses the file gene by gene into the vector
    while(getline(genes, line)){
        std::stringstream s(line);

        getline(s, g, ',');

        genesToAnalyze.push_back(g);

        g="";


        line="";
    }

    genes.close();

    return true;
}

bool FileData::readMatrix(string fileName){

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
