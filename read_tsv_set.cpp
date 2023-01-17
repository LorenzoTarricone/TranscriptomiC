<<<<<<< Updated upstream
/*
 * #include "read_tsv_set.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>



int main() {
    read_tsv_set test;
    std::set<std::string> string_set;
    string_set=test.read_tsv("D:\\CLEMENCE\\C++ project\\build-transcriptomics_development-Desktop_Qt_6_2_4_MinGW_64_bit-Debug\\gene_tsv.tsv");
    return 0;
}

*/

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





=======
/*
 * #include "read_tsv_set.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>



int main() {
    read_tsv_set test;
    std::set<std::string> string_set;
    string_set=test.read_tsv("D:\\CLEMENCE\\C++ project\\build-transcriptomics_development-Desktop_Qt_6_2_4_MinGW_64_bit-Debug\\gene_tsv.tsv");
    return 0;
}

*/

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





>>>>>>> Stashed changes
