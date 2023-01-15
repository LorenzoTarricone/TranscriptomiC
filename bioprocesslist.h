#ifndef BIOPROCESSLIST_H
#define BIOPROCESSLIST_H

#include <string>
#include <fstream>
#include <vector>

class bioprocesslist
{
public:
    bioprocesslist();
    void makelist(std::string filename); //converts the list of biological processes provided in filename to a vector of IDs, names, and synonyms

private:
    std::ifstream inFile; //'inFile' is the file containing the list of biological processes (.txt in this case)
    std::vector<std::string> BPlist; //a vector of biological process IDs, names, and synonyms (in no particular order)
    std::string str; //a placeholder for each line of the biological processes file
    std::string str2; //a placeholder for a process ID or name
    std::string str3; //a placeholder for a process synonym
    size_t start; //the first index of the ID/name/synonym of interest
    size_t end; //the last index of the ID/name/synonym of interest
};

#endif // BIOPROCESSLIST_H
