#include "parsemtx.h"
#include <fstream>
#include <algorithm>
#include <Eigen/Sparse>
#include <stdio.h>



parsemtx::parsemtx()
{
    Eigen::MatrixXd matrix;
    removed=0;

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
    parsemtx::writeToFile(filename,matrix, getcurrentGenes());
}

void parsemtx::writeToFile(std::string filename, Eigen::MatrixXd matrix, std::vector<std::string> genes){
    // file stream
    std::ofstream fout(filename);

    // check if file was opened correctly
    if(!fout){
        std::cerr << "[ERROR] File " << filename << " could not be opened. Stopping program" << std::endl;
    }
    else{
        std::cout << "[SUCCESS] File " << filename << " opened successfully" << std::endl;
    }

    std::cout << "Dimensions of the final gene index = " << genes.size() << std::endl;
    std::cout << "Dimensions of the final expression matrix = " << matrix.rows() << " or " << matrix.cols() << std::endl;

    // this will be transposed, as the sparse matrix is stored in column major
    // TODO change to row wise iteration
    // add genes as first row
    fout << "\t,";
    for(int i = 0; i < genes.size()-1; i++){
        fout << genes[i] << ",";
    }
    fout << genes[genes.size()-1] << "\n";

    for (int i = 0; i < matrix.rows() ; i++){
        fout << genes[i] << ",";
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
            if(value!="" && value!= "\n"){
                list.push_back(value);
            }
            value.clear();
        }
    }
    file.close();
    return list;
}

// function to print a vector (solve with operator overloading?? - extend to generic
void printVector(std::vector<std::string> vec){
    for(typename std::vector<std::string>::iterator i = vec.begin(); i != vec.end(); i++){
        std::cout << *i << std::endl;
    }
}



// this method will read the genenames from a file and create a map that stores the indicies as values and
// the genenames as key to a map

void parsemtx::getRowNamesFromFile(std::string filename){
    all_names = listgene(filename);
    int index = 0;
    // https://stackoverflow.com/questions/31478897/how-to-iterate-over-a-vector
    for(typename std::vector<std::string>::iterator i = all_names.begin(); i != all_names.end(); i++){
        // from https://stackoverflow.com/questions/12652997/retrieving-the-first-element-in-c-vector
        this->geneIndex[*i] = index;
        // visualize
        std::cout << "Index: " << index << "\t Gene: "<< all_names[index] << std::endl;
        // incremeent index
        index++;
    }
}

// function to initiate geneIndex
void parsemtx::initiateGeneIndex(std::vector<std::string> geneList){
    currentGenes = geneList;
    int index = 0;
    // https://stackoverflow.com/questions/31478897/how-to-iterate-over-a-vector
    for(typename std::vector<std::string>::iterator i = currentGenes.begin(); i != currentGenes.end(); i++){
        // from https://stackoverflow.com/questions/12652997/retrieving-the-first-element-in-c-vector
        this->geneIndex[*i] = index;
        // visualize
        std::cout << "Index: " << index << "\t Gene: "<< currentGenes[index] << std::endl;
        // incremeent index
        index++;
    }
}

// function to initiate geneIndex when cropping matrix
void parsemtx::initiateGeneIndex_cropped(std::vector<std::string> geneList, int row_crop){
    all_names=geneList;
    currentGenes = std::vector<std::string>(all_names.begin(), all_names.begin()+row_crop);
    int index = 0;
    // https://stackoverflow.com/questions/31478897/how-to-iterate-over-a-vector
    for(typename std::vector<std::string>::iterator i = currentGenes.begin(); i != currentGenes.end(); i++){
        // from https://stackoverflow.com/questions/12652997/retrieving-the-first-element-in-c-vector
        this->geneIndex[*i] = index;
        // visualize
        std::cout << "Index: " << index << "\t Gene: "<< currentGenes[index] << std::endl;
        // incremeent index
        index++;
    }

    for(typename std::vector<std::string>::iterator i = all_names.begin()+row_crop+1; i != all_names.end(); i++){
        // from https://stackoverflow.com/questions/12652997/retrieving-the-first-element-in-c-vector
        this->geneIndex[*i] = -1;
        // visualize
        std::cout << "Index: -1 for cropped Gene: "<< *i << std::endl;
    }

    std::cout << "[Progress] Initiating gene index finished!" << std::endl;
}

// function to initiate geneSubset
void parsemtx::initiateGeneSubset(std::vector<std::string> geneListSubset){
    geneSubset = geneListSubset;
}


void parsemtx::printGeneIndex(int rows){
    int index = 0;
    for(typename std::vector<std::string>::iterator i = currentGenes.begin(); i != currentGenes.end(); i++){
        // only print entries in geneIndex that are relevant
        if(geneIndex[*i]!=-1 && geneIndex[*i] < rows){
            // from https://stackoverflow.com/questions/12652997/retrieving-the-first-element-in-c-vector
            std::cout << *i << std::endl;

            // incremeent index

         }
         index ++;
    }

    std::cout << "Total: " << rows << " genes left" << std::endl;
    std::cout << "Total: " << index << " genes iterated" << std::endl;
    return;
}



//faster implementation of simple filtering with respect to filter_simple_old.
//filter_simple will filter out rows of the expression matrix whose expression percentage is below
//the threshold min_expr_perc
Eigen::MatrixXd parsemtx::filter_simple(Eigen::MatrixXd &expression,bool zeroes, double min_expr_perc){
    std::cout << "[Progress] Function filter_simple_test called ..." << std::endl;
    int s = expression.rows();
    int c = expression.cols();

    // to avoid double filtering in bp
    if(!zeroes){
        return expression;
    }


    //count the number of non-zero entries in each row
    int count[s];
    for(int i = 0;i<s;i++){
        count[i] = 0;
    }

    // dense matrix stored in column major
    for(int j = 0; j < expression.cols();j++){
        for(int i = 0; i<expression.rows();i++){
            count[i] += (expression(i,j)>0);
        }
    }

    int nonzeros = 0;
    for(int i = 0; i < expression.rows();i++){
        nonzeros += ((double)count[i]/expression.cols() > min_expr_perc);
    }


    Eigen::MatrixXd filtered_expression(nonzeros, c);
    std::vector<std::string> temp;
    int index=0;
    std::cout << "[Progress] Initialization in filter_simple finished ..." << std::endl;


    for(int i = 0;i<s;i++){
        if((zeroes && (count[i] == 0)) || ((double) count[i]/c <= min_expr_perc)){
            std::cout << "Remove row " << i << " or index "<<geneIndex[currentGenes[i]] <<" corresponding to gene "<< currentGenes[i]<<" with number of non-zero entries " << count[i] << " and expression percentage " << (double) count[i]/c << std::endl;
            this->geneIndex[currentGenes[i]]=-1;
            removed ++;
            std::cout<<"removed: "<< removed<<std::endl;
        }else{
            filtered_expression.row(index)=expression.row(i);
            this->geneIndex[currentGenes[i]]=index;
            temp.push_back(currentGenes[i]);
            index++;
        }
    }

    //update currentGenes to keep track of what genes we're keeping
    currentGenes=temp;

    return filtered_expression;
}

//given the dense expression matrix and a vector of strings containing all the genes we want to keep
//initialize a new dense filtered_expression matrix which only keeps the rows of the original matrix
//corresponding to the genes in the "genes" vector, if they haven't been filtered previously. We also update geneIndex to keep track of which
//index each gene corresponds to.
Eigen::MatrixXd parsemtx::filterByGenes(const Eigen::MatrixXd &expression, std::vector<std::string> genes){
    std::cout << "[Progress] Function filterByGenes called ..." << std::endl;

    Eigen::MatrixXd filtered_expression(genes.size(), expression.cols());
    std::vector<std::string> temp;


    int index=0;
    int row;
    try {
        for(typename std::vector<std::string>::iterator i = genes.begin(); i != genes.end(); i++){
            row = geneIndex[*i];
            std::cout << "[Progress] Inside loop: gene " <<*i<<" with row number "<<row<< std::endl;
            //check if gene was filtered out previously: if not, include it
            if(row==-1){
                std::cout << "Removing gene "<<*i << std::endl;
                //resize array if one of the genes was filtered out previously
                Eigen::MatrixXd temp_matrix =filtered_expression.topRows(filtered_expression.rows()-1);
                filtered_expression=temp_matrix;
                std::cout << "Removed "<<*i << std::endl;
            }else{
                std::cout << "Keeping gene"<<*i << std::endl;
                filtered_expression.row(index)=expression.row(row);
                this->geneIndex[*i]=index;
                temp.push_back(*i);
                index++;
            }
        }
    } catch (...) {
        std::cerr << "[Error] filterByGenes failed at index "<< index << " and row " << row << std::endl;
    }

    //update currentGenes to keep track of the genes remaining in rows of the expression matrix
    currentGenes=temp;
    return filtered_expression;
}


Eigen::MatrixXd parsemtx::normalisation_simple(Eigen::MatrixXd expression, std::string type_of_normal){
    // extendable for different types of normalisation
    if(type_of_normal != "col_mean"){
        return expression;
    }

    int rows = expression.rows();
    int cols = expression.cols();

    // initiate array that will store the column sums
    int col_sum[cols];
    for(int i = 0;i<cols;i++){
        col_sum[i] = 0;
    }

    // iterate through expression matrix to compute column sums
    for(int j = 0; j < cols; j++){
        for(int i = 0; i < rows; i++){
            col_sum[j] += expression(i,j);
        }
    }


    // divide each entry in the dense matrix
    // iterate through the dense matrix in storage order, default for Eigen --> col Major
    // reference: https://stackoverflow.com/questions/16283000/most-efficient-way-to-loop-through-an-eigen-matrix
    for (size_t j = 0, nRows = expression.rows(), nCols = expression.cols(); j < nCols; ++j){
        for (size_t i = 0; i < nRows; ++i){
            // this works since we are not eliminating columns, only rows
            // only execute for non-zero columns
            if(col_sum[j] != 0){
                expression(i,j) = expression(i,j)*cols/col_sum[j];
            }

        }
    }

    return expression;


}
// this function applies different types of normalisation to the dense expression matrix
// the sparse representation of the same inital matrix remains the same




// method that returns the expression matrix in its current state as an Eigen object
Eigen::MatrixXd parsemtx::getExpressionDense(){
    // check if something has been assigned to matrix
    if(this->matrix == Eigen::MatrixXd{}){
        this->matrix = Eigen::MatrixXd(sparse);
    }
    return matrix;
//    return Eigen::MatrixXd(sparse);
}

Eigen::SparseMatrix<double> parsemtx::getSparse(){
    return sparse;
}


// methods ot return dimensions of matrix wrappend in this object
int parsemtx::getRows(){
    return sparse.rows();
}
int parsemtx::getCols(){
    return sparse.cols();
}

// function to verify if we've already initated the geneIndex (useful during filtering)
bool parsemtx::geneIndexEmpty(){
    return geneIndex.empty();
}

std::vector<std::string> parsemtx::getcurrentGenes(){
    return currentGenes;
}



