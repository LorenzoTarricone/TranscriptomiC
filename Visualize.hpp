#ifndef VISUALIZE_H
#define VISUALIZE_H
#include <iostream>

using namespace std;

class CSV{
public:
    void read_csv_file(string myFilePath);
    void visualize_csv();
};
class TXT{
public:
    void read_txt_file(string myFilePath);
    void visualize_txt();
};


class SparseMatrix{
public:

    void sparse_Matrix_to_COO();

    typedef struct coo {
    size_t shape[2]; // number of row and columns
    size_t nnz; // number of nonzeros
    size_t capacity; // array capacity
    size_t *rowidx; // pointer to array of row indices
    size_t *colidx; // pointer to array of column indices
    double *val; // pointer to array of values
    } coo_t;

};
#endif // VISUALIZE_H
