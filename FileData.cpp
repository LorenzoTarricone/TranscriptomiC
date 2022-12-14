#include "filedata.h"
#include <fstream>
#include <iostream>
#include <sstream>

FileData::FileData()
{

}

bool FileData::readData(std::string fileName){

    std::ifstream coordinates;
    coordinates.open(fileName);

    if(coordinates.fail()){return false;};

    std::string line = "";

    while(getline(coordinates, line)){
        std::stringstream s(line);

        getline(s, x, ',');
        getline(s, y);

        double xx = atof(x.c_str());
        double yy = atof(y.c_str());


        xCoordinates.push_back(xx);
        yCoordinates.push_back(yy);

        x="";
        y="";

        line="";
    }


    /*while(coordinates.peek() != EOF) {

        row.clear();
        std::stringstream s(row);

        getline(s, x, ',');
        getline(s, y, ',');

        xCoordinates.push_back(stod(x));
        yCoordinates.push_back(stod(y));

        x.clear();
        y.clear();



    }*/
    coordinates.close();

    return true;
}
