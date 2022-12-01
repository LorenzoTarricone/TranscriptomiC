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

#include "Visualize.hpp" // We could also create a new header

// COO Representation
void SparseMatrix :: sparse_Matrix_to_COO(){

    //To allocate coo
    coo_t *coo_alloc(const size_t shape[2], const size_t capacity) {
    coo_t *sp = malloc(sizeof(*sp));
    if (sp == NULL) { return NULL; }
    sp->shape[0] = shape[0]; sp->shape[1] = shape[1];
    sp->nnz = 0; sp->capacity = capacity;
    sp->rowidx = malloc(capacity * sizeof(*sp->rowidx));
    sp->colidx = malloc(capacity * sizeof(*sp->colidx));
    sp->val = malloc(capacity * sizeof(*sp->val));
    if (sp->rowidx == NULL || sp->colidx == NULL || sp->val == NULL)
    { coo_dealloc(sp); return NULL; }
    return sp;
    }


}
