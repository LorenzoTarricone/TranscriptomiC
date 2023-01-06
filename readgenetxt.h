#ifndef READGENETXT_H
#define READGENETXT_H

#include <string>
#include <vector>



class readgenetxt
{
private:
    std::vector<std::string> list;

public:
    readgenetxt();
    std::vector<std::string> listgene(std::string txt_file);
};

#endif // READGENETXT_H
