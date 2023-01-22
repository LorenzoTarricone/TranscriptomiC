
//read tsv file that read the gene.tsv file and store them in a set

#include "read_tsv_set.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

read_tsv_set::read_tsv_set()
{

}

set<string> read_tsv_set::read_tsv(string file_path) {
    set<string> string_set;
    ifstream tsv_file(file_path);
    string line;
    while (getline(tsv_file, line)) {
        stringstream line_stream(line);
        string field;
        while (getline(line_stream, field, '\t')) {
            string_set.insert(field);
        }
    }

    tsv_file.close();

    //print the set
    for (string s : string_set) {
        cout << s << endl;
    }
    return string_set;
}




