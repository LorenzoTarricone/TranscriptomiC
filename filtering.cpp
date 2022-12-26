// this source file implements further methods of the parsemtx class
// the methods implemented here concern filtering of the data

#include "parsemtx.h"
#include <fstream>
#include <algorithm>
#include <Eigen/Sparse>
#include <stdio.h>

// declarations of functions to remove certain row or column from eigen dense matrix
void removeRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove)
{
    unsigned int numRows = matrix.rows()-1;
    unsigned int numCols = matrix.cols();

    if( rowToRemove < numRows )
        matrix.block(rowToRemove,0,numRows-rowToRemove,numCols) = matrix.block(rowToRemove+1,0,numRows-rowToRemove,numCols);

    matrix.conservativeResize(numRows,numCols);
}

void removeColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove)
{
    unsigned int numRows = matrix.rows();
    unsigned int numCols = matrix.cols()-1;

    if( colToRemove < numCols )
        matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.block(0,colToRemove+1,numRows,numCols-colToRemove);

    matrix.conservativeResize(numRows,numCols);
}


// filter function for the expression matrix, at the moment in sparse representation
// given a sparse matrix, filters it according to given arguments, converts it to dense and assigns to private member matrix
// initiates dense matrix representation of the expression matrix (call necessary before other action, e.g. normalisation)

// TODO: clear up use of argument type_of_transcriptom
// TODO: decide whether object should directly filter private member sparse

void parsemtx::filter(Eigen::SparseMatrix<double> expression_matrix, bool zeroes, double min_expr_perc,std::string type_of_transcriptome){
    // from https://www.geeksforgeeks.org/remove-all-zero-rows-and-all-zero-columns-from-a-matrix/

    // idea: count all non-zero entries per row and store them in a vector of size n (number of genes)
    // create a dense matrix from the sparse matrix
    // remove each row in the dense matrix where the corresponding element in the vector is zero
    // (or less than the minimum expression percentage)
    // complexity: O(n+k+r) where k is the number of non-zero entries and r is the complexity of building
    // a dense matrix from a sparse matrix in Eigen

    // sparse - dense conversion (if necessary):
    // https://stackoverflow.com/questions/15484622/how-to-convert-sparse-matrix-to-dense-matrix-in-eigen

    // get rows and columns
    // https://stackoverflow.com/questions/68877737/how-to-get-shape-dimensions-of-an-eigen-matrix
    N = sparse.rows();
    M = sparse.cols();

    // declare and initialize count array (not a vector, because we will index directly
    int count[N];
    for(int i = 0;i<N;i++){
        count[i] = 0;
    }


    // count non-zero entries, since matrix is represented in sparse, each tuple (row,column) represents
    // a non-zero element
    for (int k=0; k<sparse.outerSize(); ++k){
        for (Eigen::SparseMatrix<double>::InnerIterator it(sparse,k); it; ++it)
        {
                count[it.row()] += 1;
        }
    }

    // TODO: keep track of old row indicies

    // convert to dense matrix
    Eigen::MatrixXd dense_matrix = Eigen::MatrixXd(expression_matrix);


    // remove rows where expression percantage is less or equal to min_expr_per
    // keep count of rows that have been removed
    int removed = 0;
    for(int i = 0;i<N;i++){
        if((zeroes && count[i] == 0) || count[i]/M <= min_expr_perc){
            removeRow(dense_matrix, i-removed);
            // take care of gene name index when row is removed
             shiftGeneIndex(i,removed);
            removed ++;
        }
    }

    this->matrix = dense_matrix;
}


// this function updates the geneIndex map (dictonary) when a row is removed from the matrix
void parsemtx::shiftGeneIndex(int row, int removed){
    // TODO: decide how to deal with row deletion and mapping
    // deal with element of the row to remove
    std::string toRemove = all_names[row+removed];
    geneIndex[toRemove] = -1;

    // TODO: add error handeling
    // for each element after the removed row, decrement index by 1
    for(int i = row+removed+1; i < (int)all_names.size(); i++){
        geneIndex[all_names[i]] -= 1;
    }

    // since the all_names array is not changed by removing rows in the matrix,
    // the argument removed is necessary


}
