#ifndef ONLY_GENE_NAME_H
#define ONLY_GENE_NAME_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <set>


class only_gene_name
{
private:
    std::string true_list;
    std::set<std::string> res;
public:
    only_gene_name();
    int isSubstring(std::string s1, std::string s2);
    std::set<std::string> listgene(std::string l, std::string search);
    void printset(std::set<std::string> result);
};

#endif // ONLY_GENE_NAME_H
