#ifndef MATRIXEIGEN_H
#define MATRIXEIGEN_H

#include <Eigen/Dense>
#include <fstream>
#include <vector>
#include <random>

using namespace std;
using namespace Eigen;

class MatrixEigen
{
public:
    MatrixEigen();
    void openData(string fileToOpen);
    void generateRandomCSV(int n, int m, int start, int end, string filename);
    void printMatrix();
private:
    MatrixXd matrix;
};

#endif // MATRIXEIGEN_H


