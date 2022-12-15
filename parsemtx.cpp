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
    std::ifstream fin(filename);

    // Declare variables:
    int M, N, L;

    // Ignore headers and comments:
    while (fin.peek() == '%') fin.ignore(2048, '\n');

    // Read defining parameters:
    fin >> M >> N >> L;

//    // Create your matrix:
//    double* matrix;			     // Creates a pointer to the array
//    matrix = new double[M*N];	     // Creates the array of M*N size
//    std::fill(matrix, matrix + M*N, 0.); // From <algorithm>, zeros all entries.

//    Eigen::MatrixXd fullmatrix = Eigen::MatrixXd(M,N);
//    Eigen::SparseMatrix<double> sparseMatrix = Eigen::SparseMatrix<double>(M,N);

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
//        fullmatrix(m,n) = data;
//        matrix[(m-1) + (n-1)*M] = data;
    }

    fin.close();
    Eigen::SparseMatrix<double> sparseMatrix(M,N);
    sparseMatrix.setFromTriplets(tripletList.begin(), tripletList.end());

    this->sparse = sparseMatrix;
//    this->matrix =
}

void parsemtx::print(){
    for (int k=0; k<sparse.outerSize(); ++k)
      for (Eigen::SparseMatrix<double>::InnerIterator it(sparse,k); it; ++it)
      {
        std::cout << it.value() << " "
        << it.row() << " "   // row index
        << it.col() << " "   // col index (here it is equal to k)
        << it.index() << std::endl; // inner index, here it is equal to it.row()
      }
}
