/*
 * #include "readgenetxt.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>;

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::istringstream;
using std::stringstream;

using namespace std;


int main(){
    string txt_gene="list_gene.txt";

    readgenetxt vec;
    vector<string> res;
    res=vec.listgene(txt_gene);
    cout<<"[";
    for (const string& i : res) {
        cout << i<<" ";
      }
    cout<<"]";
    return 0;}

*/

#include "readgenetxt.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>;

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::istringstream;
using std::stringstream;

using namespace std;

readgenetxt::readgenetxt()
{
    vector<string> list;
}


vector<string> readgenetxt::listgene(string txt_file){
    vector<string> list;
    ifstream file;
    string value;

    file.open(txt_file); //open file
    if ( file.is_open() ) {
        while (!file.eof()){ //check if there is still a line
        file>>value;
        list.push_back(value);
        value.clear();
    }}
    file.close();
    return list;
}



