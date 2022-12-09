#ifndef GENENAME_H
#define GENENAME_H
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

class Genename
{
private:
    string true_list;
public:
    Genename();
    int isSubstring(string s1, string s2);
    string listgene(string l, string search);
};

#endif // GENENAME_H
