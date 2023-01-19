#include "parsemtx.h"
#include <fstream>
#include <algorithm>
#include <Eigen/Sparse>
#include <stdio.h>
#include "parsetxtbeams.h"


parsemtx::parsemtx()
{
    Eigen::MatrixXd matrix;

}
void parsemtx::readFile(std::string filename){
    // from https://cplusplus.com/forum/general/65804/
    // an mtx file stores data from a sparse matrix in throuples (x,y,value)

    // initialize filestream
    std::ifstream fin(filename);

    // Declare variables:
    int M, N, L;

    //check if file is opened
    if(!fin.is_open()){
        std::cerr << "[File " << filename << " could not be opened - aborting]" << std::endl;
        return;
    }

    // Ignore headers and comments:
    while (fin.peek() == '%') fin.ignore(2048, '\n');

    // Read defining parameters:
    fin >> M >> N >> L;
    std::cout<<"M: "<<M<<std::endl;
    std::cout<<"\nN: "<<N<<std::endl;
    std::cout<<"\nL: "<<L<<std::endl;


    // from https://eigen.tuxfamily.org/dox/group__TutorialSparse.html
    typedef Eigen::Triplet<double> T;
    std::vector<T> tripletList;
    int  estimation_of_entries = (int) (L); //(1-0.97) * M * N
    tripletList.reserve(estimation_of_entries);
    std::cout<<"\nEstimation of entries: "<<estimation_of_entries<<std::endl;

    // initialize max row and colun indices
    int max_m = 0;
    int max_n = 0;


    // initialize sparse matrix object of the correct size
    Eigen::SparseMatrix<double> sparseMatrix(M+1,N+1);

    // Read the data
    std::cout << "reading matrix with " << M << " rows and " << N << " columns" << std::endl;
    for (int l = 0; l < L; l++)
    {
        int m, n;
        double data;
        fin >> m >> n >> data;
        tripletList.push_back(T(m,n,data));
        // alternative approach --> directly insert to matrix
//        sparseMatrix.insert(m,n) = data;
//        std::cout << m << "\t" << n << "\t" << data << std::endl;
        // get max row and column indices
        if(max_m < m){max_m = m;}
        if(max_n < n){max_n = n;}


    }

    // check sparse matrix object
    std::cout << "Created sparse object with " << sparseMatrix.rows() << " rows, " << sparseMatrix.cols() << " columns and " << sparseMatrix.nonZeros() << " non-zero values" << std::endl;

    // store defining parameters in private members
    this->M = sparseMatrix.rows();
    this->N = sparseMatrix.cols();

    // close file
    fin.close();

    std::cout << "the maximum row index is "<< max_m << std::endl;
    std::cout << "the maximum column index is "<< max_n << std::endl;

    // fill sparse matrix object using the vector of triplets from the file reading
    sparseMatrix.setFromTriplets(tripletList.begin(), tripletList.end());

////     alternative approach
//    sparseMatrix.makeCompressed();

    // check sparse matrix object
    std::cout << "Created sparse object with " << sparseMatrix.rows() << " rows, " << sparseMatrix.cols() << " columns and " << sparseMatrix.nonZeros() << " non-zero values" << std::endl;


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


// overloaded version of writeToFile to write expression matrix to file
void parsemtx::writeToFile(std::string filename){
    // convert sparse representation to dense (check this!!)
    if (!matrix.rows()){
        matrix = Eigen::MatrixXd(sparse);
    }
    parsemtx::writeToFile(filename,matrix);
}

void parsemtx::writeToFile(std::string filename, Eigen::MatrixXd matrix){
    // file stream
    std::ofstream fout(filename);

    // check if file was opened correctly
    if(!fout){
        std::cerr << "[ERROR] File " << filename << " could not be opened. Stopping program" << std::endl;
    }
    else{
        std::cout << "[SUCCESS] File " << filename << " opened successfully" << std::endl;
    }

    // this will be transposed, as the sparse matrix is stored in column major
    // TODO change to row wise iteration
    for (int i = 0; i < matrix.rows() ; i++){
        for (int j = 0; j < matrix.rows()-1; j++){
            fout << matrix(i,j) << ","; //distance between coordinate i and j
        }
        fout << matrix(i,matrix.rows()-1) << "\n";
    }


    // close the file (stream)
    fout.close();
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

// function to print a vector (solve with operator overloading?? - extend to generic
void printVector(std::vector<std::string> vec){
    for(typename std::vector<std::string>::iterator i = vec.begin(); i != vec.end(); i++){
        std::cout << *i << std::endl;
    }
}



// this function updates the geneIndex map (dictonary) when a row is removed from the matrix
void parsemtx::shiftGeneIndex(int row, int removed){
    // TODO: decide how to deal with row deletion and mapping
    // deal with element of the row to remove
    std::string toRemove = all_names[row+removed];
    geneIndex[toRemove] = -1;

    // TODO: add error handeling
    // for each element after the removed row, decrement index by 1
    for(int i = row+removed+1; i < all_names.size(); i++){
        geneIndex[all_names[i]] -= 1;
    }

    // since the all_names array is not changed by removing rows in the matrix,
    // the argument removed is necessary


}


// this method will read the genenames from a file and create a map that stores the indicies as values and
// the genenames as key to a map
// TODO: determine whether a map of the opposite key-value relation or a list would be more beneficial

void parsemtx::getRowNamesFromFile(std::string filename){
    all_names = listgene(filename);
    int index = 0;
    // https://stackoverflow.com/questions/31478897/how-to-iterate-over-a-vector
    for(typename std::vector<std::string>::iterator i = all_names.begin(); i != all_names.end(); i++){
        // from https://stackoverflow.com/questions/12652997/retrieving-the-first-element-in-c-vector
        this->geneIndex[*i] = index;
        // incremeent index
        index++;
    }
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
        if((zeroes && (count[i] == 0)) || count[i]/M <= min_expr_perc){
            removeRow(dense_matrix, i-removed);
            // take care of gene name index when row is removed
             shiftGeneIndex(i,removed);
            removed ++;
        }
    }

    this->matrix = dense_matrix;
}

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

// this method will use the file containing beam names as well as the dimensions of the expression matrix
// and generate spatial data until we have actual data to analyse
// it will write said data to a tsv file that can later be used for filtering etc
void parsemtx::createBeamFile(std::string file_out, std::string file_in){
    // if no input filename is given, the file will be created entirely at random
    if(file_in == ""){
        parseTxtBeams::createDummyFile(N,file_out);
        return;
    }

    std::vector<std::string> list = listgene(file_in);
    int l = list.size();
    std::cout << "There are " << l << " beams and " << N << " columns in the expression matrix" << std::endl;

//    for(typename std::vector<std::string>::iterator i = list.begin(); i != list.end(); i++){
//        // from https://stackoverflow.com/questions/12652997/retrieving-the-first-element-in-c-vector
//        std::cout << *i << "," << std::endl;
//    }

    // this operation sets the seed for the randomization (generates different values for each iteration)
    srand(time(nullptr));

    // file stream
    std::ofstream fout;

    // open file
    fout.open(file_out);

    // check if file was opened correctly
    if(!fout){
        std::cerr << "[ERROR] File " << file_in << " could not be opened. Stopping program" << std::endl;
    }
    else{
        std::cout << "[SUCCESS] File " << file_in << " opened successfully" << std::endl;
    }


    // define maximum range for coordinates
    int MAX_COORD = 2000;

        for(typename std::vector<std::string>::iterator i = list.begin(); i != list.end(); i++){
            // from https://stackoverflow.com/questions/12652997/retrieving-the-first-element-in-c-vector
//            std::cout << *i << "," << std::endl;
            int x = rand()%MAX_COORD;
            int y = rand()%MAX_COORD;
            fout << *i << "\t" << x << "\t" << y << "\n";
//            std::cout << *i << "\t" << x << "\t" << y << "\n" << std::endl;
        }

    // close the file (stream)
    fout.close();
}


// method that returns the expression matrix in its current state as an Eigen object
Eigen::MatrixXd parsemtx::getExpressionDense(){
//    // check if something has been assigned to matrix
//    if(this->matrix == Eigen::MatrixXd{}){
//        this->matrix = Eigen::MatrixXd(sparse);
//    }
//    return matrix;
    return Eigen::MatrixXd(sparse);
}


// methods ot return dimensions of matrix wrappend in this object
int parsemtx::getRows(){
    return sparse.rows();
}
int parsemtx::getCols(){
    return sparse.cols();
}
