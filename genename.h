#ifndef GENENAME_H
#define GENENAME_H
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <set>
using namespace std;

class Genename
{
private:
    string true_list;
    set<string> res;
public:
    Genename();
    int isSubstring(string s1, string s2);
    set<string> listgene(string l, string search);
    void printset(set<string> result);
};

#endif // GENENAME_H
