#include "parsemtx.h"
#include <fstream>
#include <algorithm>
#include <Eigen/Sparse>

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

    matrix = Eigen::MatrixXd(M,N);
    Eigen::SparseMatrix<double> sparseMatrix = Eigen::SparseMatrix<double>(M,N);

    // Read the data
    for (int l = 0; l < L; l++)
    {
        int m, n;
        double data;
        fin >> m >> n >> data;
        matrix(m,n) = data;
//        matrix[(m-1) + (n-1)*M] = data;
    }

    fin.close();
}
