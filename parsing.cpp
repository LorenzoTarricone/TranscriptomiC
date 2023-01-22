#include "parsing.h"


parsing::parsing(){
    std::vector<std::string> beams =  std::vector<std::string>();

}


void parsing::readBeamFileCSV(std::string filename){
    // from https://techoverflow.net/2020/01/30/how-to-read-tsv-tab-separated-values-in-c/

    std::ifstream fin(filename,std::ios::in);
    std::string beam,x,y;


    if(!fin){
        std::cerr << "[ERROR] File " << filename << " could not be opened. Stopping program" << std::endl;
        return;
    }
    else{
        std::cout << "[SUCCESS] File " << filename << " opened successfully" << std::endl;
    }

    int count = 0;

    // this method relies on the fact that all rows are filled and columns are in order "beam" "x coordinate" "y coordinate"

    // take care of the first two rows
    std::string line;
    for(int i = 0;i < 2; i++){
        getline(fin, line, ',');
        std::getline(fin,line,',');
        std::getline(fin,line,'\n');
    }

    // get beam name
    while (getline(fin, beam, ',')) {

        // get x coordinate as string
        std::getline(fin,x,',');

        // get y coordinate as string
        std::getline(fin,y,'\n');

        // add columns to respective private vectors
        this->beams.push_back(beam);
        this->x.push_back(stod(x));
        this->y.push_back(stod(y));


        count++;
    }
    // close file
    fin.close();


}

Eigen::MatrixXd parsing::convertToMatrix(){
    int m = y.size();
    Eigen::MatrixXd coords = Eigen::MatrixXd(m,2);
    int j = 0;
    for(typename std::vector<double>::iterator i = x.begin(); i != x.end(); i++){
        coords(j,0) = *i;
        j++;
    }
    j = 0;
    for(typename std::vector<double>::iterator i = y.begin(); i != y.end(); i++){
        coords(j,1) = *i;
        j++;
    }
    return coords;
}



