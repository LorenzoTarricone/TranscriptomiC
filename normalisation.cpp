// this source file implements further methods of the parsemtx class
// the methods implemented here concern normalisation of the data

#include "parsemtx.h"
#include <fstream>
#include <algorithm>
#include <Eigen/Sparse>
#include <stdio.h>


// this function applies different types of normalisation to the dense expression matrix
// the sparse representation of the same inital matrix remains the same

void parsemtx::normalisation(std::string type_of_normal){
    // extendable for different types of normalisation
    if(type_of_normal != "col_mean"){
        return;
    }

    // initiate array that will store the column sums
    int col_sum[M];
    for(int i = 0;i<M;i++){
        col_sum[i] = 0;
    }


    // iterate through expression matrix in sparse representation to compute column sums
    for (int k=0; k<sparse.outerSize(); ++k){
        for (Eigen::SparseMatrix<double>::InnerIterator it(sparse,k); it; ++it)
        {
                col_sum[it.col()] += it.value();
        }
    }

    // divide each entry in the dense matrix
    // iterate through the dense matrix in storage order, default for Eigen --> col Major
    // reference: https://stackoverflow.com/questions/16283000/most-efficient-way-to-loop-through-an-eigen-matrix
    for (size_t j = 0, nRows = matrix.rows(), nCols = matrix.cols(); j < nCols; ++j){
        for (size_t i = 0; i < nRows; ++i){
            // this works since we are not eliminating columns, only rows
            matrix(i,j) /= col_sum[j];
        }
    }

}
