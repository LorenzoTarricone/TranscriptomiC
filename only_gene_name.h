#ifndef ONLY_GENE_NAME_H
#define ONLY_GENE_NAME_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <set>


struct Info {
    int number_in_list;
    std::string id;
    std::string label;
    bool operator<(const Info& other) const { return id < other.id; }
};

class only_gene_name
{
private:
    std::string true_list;
    std::set<std::string> res;
public:
    only_gene_name();

    

    int isSubstring(std::string s1, std::string s2);
    std::set<std::string> listgene(std::string l, std::string search);
    std::set<Info> list_bio_process(std::string l, std::string search1, std::string search2, std::string search3);
    void printset(std::set<std::string> result);

};

#endif // ONLY_GENE_NAME_H
