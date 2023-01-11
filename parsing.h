#ifndef PARSING_H
#define PARSING_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <Eigen/Dense>

class parsing
{
public:
    parsing();
    void readBeamFileCSV(std::string filename);
    std::vector<std::string> readNamesFileTSV(std::string filename);
    Eigen::MatrixXd convertToMatrix();
private:
    std::vector<std::string> beams;
    std::vector<double> x;
    std::vector<double> y;

};

#endif // PARSING_H
