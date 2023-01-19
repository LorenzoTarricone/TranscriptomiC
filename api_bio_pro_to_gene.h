#ifndef API_BIO_PRO_TO_GENE_H
#define API_BIO_PRO_TO_GENE_H

#include <stdlib.h>
#include <vector>
#include <string.h>


class api_bio_pro_to_gene
{
public:
    api_bio_pro_to_gene();
    std::vector<std::string> api_bio_pro_to_gene_function(std::string geneNameFile, std::string geneBioProFile, int nb_study);

};

#endif // API_BIO_PRO_TO_GENE_H
