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
    std::vector<std::string> listgene_bio_pro(std::string txt_file, int nb_gene);
};

#endif // READGENETXT_H
