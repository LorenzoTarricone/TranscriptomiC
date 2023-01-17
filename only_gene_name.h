#ifndef ONLY_GENE_NAME_H
#define ONLY_GENE_NAME_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <set>

using namespace std;

struct Info {
    int number_in_list;
    string id;
    string label;
    bool operator<(const Info& other) const { return id < other.id; }
};

class only_gene_name
{
private:
    std::string true_list;
    std::set<std::string> res;
public:
    only_gene_name();

    

    int isSubstring(string s1, string s2);
    set<string> listgene(string l, string search);
    set<Info> list_bio_process(string l, string search1, string search2, string search3);
    void printset(set<string> result);

};

#endif // ONLY_GENE_NAME_H
