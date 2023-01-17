#ifndef GENENAME_H
#define GENENAME_H
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <set>


class Genename
{
private:
    std::string true_list;
    std::set<std::string> res;
public:
    Genename();
    int isSubstring(std::string s1, std::string s2);
    std::set<std::string> listgene(std::string l, std::string search);
    void printset(std::set<std::string> result);
};

#endif // GENENAME_H
