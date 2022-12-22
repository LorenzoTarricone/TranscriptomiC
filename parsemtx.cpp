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
