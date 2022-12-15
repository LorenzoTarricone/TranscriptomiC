#ifndef PARSETXTBEAMS_H
#define PARSETXTBEAMS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>


class parseTxtBeams
{
public:
    parseTxtBeams();
    void readFile(std::string filename);
    void createDummyFile(unsigned int rows, std::string filename);

private:
    std::vector<std::string> beams;
    std::vector<int> x;
    std::vector<int> y;

};

#endif // PARSETXTBEAMS_H
