#include <QApplication>
#include "mainwindow.h"
#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>
#include <colocalization_matrix.h>
#include <math.h>


using namespace Eigen;
using namespace std;

//given an eigen matrix, returns an eigen matrix with the distance between points
double distance(double x1, double x2, double y1, double y2) {
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
};

//STEP 1
//given an eigen matrix, returns an eigen matrix with the distance between points
MatrixXd matrix_distance(MatrixXd A){
    MatrixXd A_distance(A.rows(),A.rows());
    for (int i = 0; i < A.rows() ; i++){
        for (int j = 0; j < A.rows(); j++){
            A_distance(i,j) = distance(A(i,1), A(j,1), A(i, 2), A(j,2)); //distance between coordinate i and j
        }
    }
    return A_distance;
};

double max (double a, double b){
    if (a<b){return b;}
    return a;
};

//returns the linkage value of coordinates (x1,y1) and (x2,y2) given m and p
double linkage(double d, double m, double p) {
    return pow((max(0,m-d))/m, p);
}

//STEP 2
//given an eigen matrix of the distance between points and the values m and p, returns an eigen matrix with the linkage values
MatrixXd matrix_linkage(MatrixXd A, double m, double p){
    MatrixXd A_distance = matrix_distance(A);
    MatrixXd A_linkage(A_distance.rows(), A_distance.rows());
    for (int i = 0; i < A_distance.rows(); i++){
        for (int j = 0; j < A_distance.rows(); j++){
            A_linkage(i,j) = linkage(A_distance(i,j), m, p);
        }
    }
    return A_linkage;
}

//STEP 3

// given an eigen matrix containing the linkage values (kxk) and a eigen matrix containing the gene - beams values (nxn)
// returns an nxk matrix indicating average gene expression in neighbouring beams

MatrixXd combine_linkage(MatrixXd A_linkage, MatrixXd A_expression){
    int k = A_linkage.rows();
    int n = A_expression.rows();
    MatrixXd A_combine(n,k);
    // iterate through columns of A_combine
    for(int j = 0; j < k; j++){
        // since we're considering A_combine and A_expression column-wise, iterate through rows per column
        for(int i = 0; i < n; i++){
            // initialize each entry to simplify the sum
            A_combine(i,j) = 0;
            // compute the sum along row j of the linkage matrix, excluding entry
            for(int r = 0; r < k; r++){
                if(r != j){
                    A_combine(i,j) += A_linkage(j,r)*A_expression(i,r);
                }// end if
            }// end for r
         }// end for i
    }// end for j
    return A_combine;
} // end method



//STEP 4

//given two eigen matrices, the expression matrix the neighboring expression matrix from step 3, compare the columns of these matrices
//by using a special functions with certain desirable characteristics to obtain a tensor. Both matrices have dimension n_genes*n_beams,
//while the tensor will have dimension n_beams*n_genes*n_genes.

double important_function(double x_i, double Y, double a=2, double b=0.5){
    return -a*abs(x_i-Y) + b*(x_i+Y);
}

MatrixXd comparison(MatrixXd expression, MatrixXd neighbors, double a=1, double b=0.5){
    int n_beams=expression.cols();
    int n_genes=expression.rows();

    //initialize 3d tensor array
    Tensor<double, 3> Final_tensor(n_beams, n_genes, n_genes);


    //building the tensor
    for(int beam=0; beam<n_beams; beam++){
        for(int i=0; i<n_genes; i++){
            for(int j=0; j<n_genes;j++){
                Final_tensor(beam, i, j) = important_function(expression(i,beam), neighbors(j,beam), a, b);
            }
        }
    }

    //taking the mean over the beams and returning the matrix
    //TODO: make it more efficient?

    MatrixXd mat_new(n_genes,n_genes);

    for(int i=0;i<n_genes; i++){
        for(int j=0;j<n_genes;j++){
            vector<double> vec_for_average;
            for (int beam=0;beam<n_beams;beam++){
                vec_for_average.push_back(Final_tensor(beam,i,j));
            }
            mat_new(i,j)=reduce(vec_for_average.begin(), vec_for_average.end()) / n_beams;
        }
    }

    return mat_new;
}

//STEP 5


// given a matrix that is built from the expression and the linkage (neighbourig) matrix in step 4
// normalize with row mean and 2-base logarithm and returns nxn enrichement score matrix
// ignore zero values to avoid neg infinity
// TODO: determine whether method should modify given matrix or create new matrix

MatrixXd enrichment(MatrixXd A){
    int N = A.size();
    // array to store the row sums (N size of matrix)
    // TODO: add this function to the object that stores the colocalisation matrix, use private member N
    double S_A[N];
    // initialize array
    for(int i = 0; i < N; i++){
        S_A[i] = 0;
     }// end for i
    // iterate through matrix A columnwise (stored in col major)
    for(int j = 0; j < N; j++){
        for(int i = 0; i < N; i++){
            // add normalized value to row mean array
            S_A[i] += A(i,j)/N;
         }// end for i
    }// end for j

    // initialize enrichment score matrix
    MatrixXd A_enrichment(N,N);
    // iterate through matrix A columnwise (stored in col major)
    for(int j = 0; j < N; j++){
        for(int i = 0; i < N; i++){
            // add normalized value to row mean array
            A_enrichment(i,j) = log(A(i,j)/S_A[i])/log(2);
         }// end for i
    }// end for j

    // return matrix containing enrichment score
    return A_enrichment;
}

