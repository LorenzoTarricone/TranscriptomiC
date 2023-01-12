#include "upload_matrix.h"
#include <fstream>
#include <sstream>


upload_matrix::upload_matrix()
{

}
bool upload_matrix::setData_Matrix(std::string fileName){
    std::ifstream coordinates;
    coordinates.open(fileName);

    if(coordinates.fail()){return false;};

    std::string line = "";

    int rows = 0;
    int col = 0;

    while(getline(coordinates, line)){
        std::stringstream s(line); // we get the whole line
        rows = rows + 1;
        while(getline(s,iterator)){
            col = col + 1;
            m.resize(rows,col); // change the dimension of the matrix
            getline(s, iterator, ',');
            double p = atof(iterator.c_str());
            m(rows,col) = p;


        }
        iterator="";
        line="";

    }

    coordinates.close();

}
