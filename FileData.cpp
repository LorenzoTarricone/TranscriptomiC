#include "filedata.h"
#include <fstream>
#include <sstream>

FileData::FileData()
{

}

bool FileData::readData(std::string fileName){

    /*This function opens a file and reads it into three vectors for x, y, and p values.
     * It is used for the inital data upload, and then the data is used for plotting the scatterplot
     * and heatmaps.
     */

    //clears the three vectors in case they had been used before
    xCoordinates.clear();
    yCoordinates.clear();
    pValues.clear();

    //opens the file
    std::ifstream coordinates;
    coordinates.open(fileName);

    if(coordinates.fail()){return false;}; //in case the file is not found

    std::string line = "";

    //reads and parses the file datapoint by datapoint into the vectors
    while(getline(coordinates, line)){
        std::stringstream s(line);

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

bool FileData::readGenes(std::string fileName){

    /*This function opens a file and reads it into one vector with the names of the genes to analyze.
     * It is used in the colocalization window, because the user will upload a file with the genes
     * that they want to analyze. This function handles the parsing of that file.
     */

    genesToAnalyze.clear();

    std::ifstream genes;
    genes.open(fileName);

    if(genes.fail()){return false;}; //in case the file is not found

    std::string line = "";

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
