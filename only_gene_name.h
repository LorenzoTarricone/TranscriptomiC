#ifndef ONLY_GENE_NAME_H
#define ONLY_GENE_NAME_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <set>
using namespace std;

class only_gene_name
{
private:
    string true_list;
    set<string> res;
public:
    only_gene_name();
    int isSubstring(string s1, string s2);
    set<string> listgene(string l, string search);
    void printset(set<string> result);
};

#endif // ONLY_GENE_NAME_H
