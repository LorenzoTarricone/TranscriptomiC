/*
 * #include "readgenetxt.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>

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
#include <fstream>
#include <QDebug>

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::istringstream;
using std::stringstream;

using namespace std;

readgenetxt::readgenetxt()
{
    vector<string> list;
}


vector<string> readgenetxt::listgene(string filename){
    vector<string> list;
    ifstream file;
    string line;
    cout<<"code";
    file.open(filename); //open file
    if (file.peek() == std::ifstream::traits_type::eof()) {
        qDebug() << "Empty file!!";
    }
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
    } qDebug() << "reading txt file";
    while (getline(file, line)) {
        qDebug() << "got line!";
        qDebug() << QString::fromStdString(line);
        stringstream ss(line);
        string value;
        while (ss >> value) {
            list.push_back(value);
        }
    }

    file.close();
    return list;
}







