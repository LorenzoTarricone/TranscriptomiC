#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>

using namespace Eigen;

double WassersteinDistance(const MatrixXd& mat1, const MatrixXd& mat2) {
  // Number of points in each matrix
  int n1 = mat1.rows();
  int n2 = mat2.rows();

  // Create sparse matrix for each matrix
  SparseMatrix<double> A(n1, n2);
  SparseMatrix<double> B(n1, n2);

  // Fill sparse matrices with weights
  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < n2; j++) {
      double weight = sqrt(pow(mat1(i, 0) - mat2(j, 0), 2) + pow(mat1(i, 1) - mat2(j, 1), 2));
      A.insert(i, j) = weight * mat1(i, 2);
      B.insert(i, j) = weight * mat2(j, 2);
    }
  }

  // Solve linear program to find optimal transport plan
  VectorXd x(n1 + n2);
  VectorXd b(n1 + n2);
  b.head(n1) = VectorXd::Ones(n1);
  b.tail(n2) = VectorXd::Ones(n2);
  SparseMatrix<double> G(n1 + n2, n1 + n2);
  for(int i = 0; i < n1; i++)
    G.insert(i,i) = 1;
  for(int i = n1; i < n1 + n2; i++)
    G.insert(i,i) = -1;
  VectorXd c(n1 + n2);
  c.head(n1) = A * VectorXd::Ones(n2);
  c.tail(n2) = B.transpose() * VectorXd::Ones(n1);
  Eigen::SimplicialLDLT<SparseMatrix<double>> solver;
  solver.compute(G.transpose() * G);
  x = solver.solve(G.transpose() * c);

  // Compute Wasserstein distance
  return x.dot(c);
}

int main() {
  // Example usage:
  // Here you have two matrices made each of three columns
  // The first two columns correspond respectively to the
  // x and the y coordinateds, while the last column is the weight
  // (that is the expression count for that specific bead in position
  // x, y)

  MatrixXd mat1(3, 3);
  mat1 << 1, 2, 3,
          4, 5, 6,
          7, 8, 9;
  MatrixXd mat2(3, 3);
  mat2 << 9, 8, 7,
          6, 5, 4,
          3, 2, 1;
  double distance = WassersteinDistance(mat1, mat2);
  std::cout << "Wasserstein Distance: " << distance << std::endl;
  return 0;
}
