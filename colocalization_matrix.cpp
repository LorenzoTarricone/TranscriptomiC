#include "colocalization_matrix.h"
#include <QApplication>
//#include "UploadWindow.h"
#include <Eigen/Dense>
#include <math.h>
#include <thread>





//given an eigen matrix, returns an eigen matrix with the distance between points
double distance(double x1, double x2, double y1, double y2) {
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
};

//STEP 1
//given an eigen matrix, returns an eigen matrix with the distance between points
Eigen::MatrixXd matrix_distance(Eigen::MatrixXd A){
    Eigen::MatrixXd A_distance(A.rows(),A.rows());
    for(int i=0;i<A.rows();i++){
        A_distance.col(i)=(A.rowwise() - A.row(i)).matrix().rowwise().norm();
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
Eigen::MatrixXd matrix_linkage(const Eigen::MatrixXd &A_distance, double m, double p){
    //MatrixXd A_distance = matrix_distance(A);
    Eigen::MatrixXd A_linkage(A_distance.rows(), A_distance.rows());
    for (int i = 0; i < A_distance.rows(); i++){
        for (int j = 0; j < A_distance.rows(); j++){
            A_linkage(i,j) = linkage(A_distance(i,j), m, p);
        }
    }
    return A_linkage;
}

//STEP 3

// given an eigen matrix containing the linkage values (kxk) and a eigen matrix containing the gene - beams values (nxk)
// returns an nxk matrix indicating average gene expression in neighbouring beams

Eigen::MatrixXd combine_linkage(const Eigen::MatrixXd &A_linkage, const Eigen::MatrixXd &A_expression){
    int k = A_linkage.rows();
    int n = A_expression.rows();
    Eigen::MatrixXd A_combine(n,k);

    // iterate through columns of A_combine
    for(int j = 0; j < k; j++){
        double row_total = A_linkage.row(j).sum();
        VectorXd dot_product_results = (A_linkage.row(j) * A_expression.transpose()).transpose();
        // Divide the dot product results by the row total
        dot_product_results /= row_total;
        // Assign the results to the corresponding row of A_combine
        A_combine.col(j) = dot_product_results;
     }

    return A_combine;
} // end method



//STEP 4

//given two eigen matrices, the expression matrix the neighboring expression matrix from step 3, compare the columns of these matrices
//by using a special functions with certain desirable characteristics to obtain a tensor. Both matrices have dimension n_genes*n_beams,
//while the tensor will have dimension n_beams*n_genes*n_genes.


double important_function(double x_i, double Y, double a=2, double b=0.5){
    return -a*abs(x_i-Y) + b*(x_i+Y);
}

Eigen::MatrixXd comparison_old(const Eigen::MatrixXd &expression, const Eigen::MatrixXd &neighbors, double a, double b){
    int n_beams=expression.cols();
    int n_genes=expression.rows();

    //taking the mean over the beams and returning the matrix


    Eigen::MatrixXd mat_new(n_genes,n_genes);

    for(int i=0;i<n_genes; i++){
        if(i%100==0){
         }
        for(int j=0;j<n_genes;j++){
            std::vector<double> vec_for_average;
            for (int beam=0;beam<n_beams;beam++){
                vec_for_average.push_back(important_function(expression(i,beam), neighbors(j,beam), a, b));
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
//this step currently crashes the program
// TODO: determine whether method should modify given matrix or create new matrix

Eigen::MatrixXd enrichment(const Eigen::MatrixXd &A){
    int N = A.rows();
    // array to store the row sums (N size of matrix)
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
    Eigen::MatrixXd A_enrichment(N,N);
    // iterate through matrix A columnwise (stored in col major)
    for(int j = 0; j < N; j++){
        for(int i = 0; i < N; i++){
            // add normalized value to row mean array
            A_enrichment(i,j) = log2(A(i,j)/S_A[i]+1);
         }// end for i
    }// end for j

    // return matrix containing enrichment score
    return A_enrichment;
}

