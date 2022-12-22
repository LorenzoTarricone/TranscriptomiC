#ifndef READGENETXT_H
#define READGENETXT_H

#include <string>
#include <vector>
using namespace std;


class readgenetxt
{
private:
    vector<string> list;

public:
    readgenetxt();
    vector<string> listgene(string file_name);
};

#endif // READGENETXT_H
