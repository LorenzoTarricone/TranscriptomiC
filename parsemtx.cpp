#include "parsemtx.h"
#include <fstream>
#include <algorithm>
#include <Eigen/Sparse>
#include <stdio.h>


parsemtx::parsemtx()
{
//    Eigen::MatrixXd matrix;
}
void parsemtx::readFile(std::string filename){
    // from https://cplusplus.com/forum/general/65804/
    // an mtx file stores data from a sparse matrix in throuples (x,y,value)

    // initialize filestream
    std::ifstream fin(filename);

    // Declare variables:
    int M, N, L;

    // Ignore headers and comments:
    while (fin.peek() == '%') fin.ignore(2048, '\n');

    // Read defining parameters:
    fin >> M >> N >> L;

    // from https://eigen.tuxfamily.org/dox/group__TutorialSparse.html
    typedef Eigen::Triplet<double> T;
    std::vector<T> tripletList;
    int  estimation_of_entries = (int) ((1-0.98) * M * N);
    tripletList.reserve(estimation_of_entries);

    // Read the data
    for (int l = 0; l < L; l++)
    {
        int m, n;
        double data;
        fin >> m >> n >> data;
        tripletList.push_back(T(m,n,data));

    }

    // close file
    fin.close();

    // initialize sparse matrix object of the correct size
    Eigen::SparseMatrix<double> sparseMatrix(M,N);

    // fill sparse matrix object using the vector of triplets from the file reading
    sparseMatrix.setFromTriplets(tripletList.begin(), tripletList.end());

    // make the private member sparse of the object point to the sparse matrix we just created
    this->sparse = sparseMatrix;
}

void parsemtx::print(){
    // see https://eigen.tuxfamily.org/dox/group__TutorialSparse.html
    // this method prints the sparse matrix object

    for (int k=0; k<sparse.outerSize(); ++k)
            // using an iterator to go through the sparse matrix
          for (Eigen::SparseMatrix<double>::InnerIterator it(sparse,k); it; ++it)
          {
            std::cout << it.value() << " "
            << it.row() << " "   // row index
            << it.col() << " "   // col index (here it is equal to k)
            << it.index() << std::endl; // inner index, here it is equal to it.row()
          }
}

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

// function to read a txt file with gene names (row names) - use until parse_file branch is merged into main
// from https://github.com/LorenzoTarricone/TranscriptomiC/blob/parse_file/readgenetxt.cpp
std::vector<std::string> listgene(std::string txt_file){
    std::vector<std::string> list;
    std::ifstream file;
    std::string value;

    file.open(txt_file); //open file
    if ( file.is_open() ) {
        while (!file.eof()){ //check if there is still a line
        file>>value;
        list.push_back(value);
        value.clear();
    }}
    file.close();
    return list;
}


// filter function for the expression matrix, at the moment in sparse representation
// given a sparse matrix, filters it according to given arguments, converts it to dense and assigns to private member matrix

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
    int N = sparse.rows();
    int M = sparse.cols();

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
            removed ++;
        }
    }

    this->matrix = dense_matrix;
}

// this method will read the genenames from a file and create a map that stores the indicies as values and
// the genenames as key to a map
// TODO: determine whether a map of the opposite key-value relation or a list would be more beneficial

void parsemtx::getRowNamesFromFile(std::string filename){
    std::vector<std::string> string_list = listgene(filename);
    int index = 0;
    // https://stackoverflow.com/questions/31478897/how-to-iterate-over-a-vector
    for(typename std::vector<std::string>::iterator i = string_list.begin(); i != string_list.end(); i++){
        // from https://stackoverflow.com/questions/12652997/retrieving-the-first-element-in-c-vector
        this->geneIndex[*i] = index;
        // incremeent index
        index++;
    }
}

