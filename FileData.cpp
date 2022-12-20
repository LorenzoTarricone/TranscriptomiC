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
