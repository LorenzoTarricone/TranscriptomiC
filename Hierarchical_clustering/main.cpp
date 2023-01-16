
#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

MatrixXd distanceMatrix; // Distance matrix
VectorXi clusters; // Cluster assignments for each data point

// Function to perform agglomerative hierarchical clustering
void hierarchicalClustering(int n) {
  int numPoints = distanceMatrix.rows();
  clusters = VectorXi::LinSpaced(numPoints, 0, numPoints-1); // Initialize each data point to its own cluster

  while (clusters.maxCoeff()+1 > n) { // Repeat until number of clusters is less than or equal to n
    // Find the two closest clusters
    int minRow, minCol;
    distanceMatrix.minCoeff(&minRow, &minCol);
    if (minRow > minCol) swap(minRow, minCol);

    // Merge the two closest clusters
    for (int i = 0; i < numPoints; i++) {
      if (clusters(i) == minCol) {
        clusters(i) = minRow;
      } else if (clusters(i) > minCol) {
        clusters(i)--;
      }
    }

    // Update the distance matrix
    distanceMatrix.block(minRow, minCol, 1, distanceMatrix.cols()-minCol) = distanceMatrix.block(minCol, minCol, 1, distanceMatrix.cols()-minCol);
    distanceMatrix.block(minRow, minCol+1, distanceMatrix.rows()-minCol-1, 1) = distanceMatrix.block(minCol+1, minCol, distanceMatrix.rows()-minCol-1, 1);
    distanceMatrix.conservativeResize(numPoints-1, numPoints-1);
  }
}

int main() {
  // Example usage:
  // Here the input is simply a distance matrix (that in our case will be built using the wasserstein distance)
  distanceMatrix = (MatrixXd(4,4) << 0, 2, 3, 5, 2, 0, 4, 6, 3, 4, 0, 2, 5, 6, 2, 0).finished();
  cout << "Distance matrix: " << endl << distanceMatrix << endl;
  hierarchicalClustering(2);
  cout << "Cluster assignments: " << endl << clusters.transpose() << endl;
  return 0;
}
