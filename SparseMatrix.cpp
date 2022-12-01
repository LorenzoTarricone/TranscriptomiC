/*****************************************************************************************************************
 ** The coordinate representation (often abbreviated “COO”) of a sparse matrix A stores the nonzero             **
 ** entries of A as a list T of triplets of the form (i, j, Aij) along with a tuple S = (m, n) that represents  **
 ** the shape of the matrix. Each triplet consists of a row index, a column index, and a value, and             **
 ** the shape consists of the number of rows and columns                                                        **
 *****************************************************************************************************************
 ** We can also compressed sparse column or compressed sparse row represenation                                 **
 ** Source: https://trello.com/1/cards/637b7f725cc197003c25476b/attachments                                     **
 ** /637b8085ba208500dc550438/download/sparse.pdf                                                               **
 ****************************************************************************************************************/

// COO Representation

typedef struct coo {
size_t shape[2]; // number of row and columns
size_t nnz; // number of nonzeros
size_t capacity; // array capacity
size_t *rowidx; // pointer to array of row indices
size_t *colidx; // pointer to array of column indices
double *val; // pointer to array of values
} coo_t;

void sparse_Matrix_to_COO(){


}
