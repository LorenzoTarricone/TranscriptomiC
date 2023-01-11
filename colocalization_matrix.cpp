#include <QApplication>
#include "mainwindow.h"
#include <Eigen/Dense>
#include <colocalization_matrix.h>
#include <math.h>
#include "parsetxtbeams.h"
#include "parsemtx.h"


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
            A_distance(i,j) = distance(A(i,0), A(j,0), A(i, 1), A(j,1)); //distance between coordinate i and j
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
MatrixXd matrix_linkage(MatrixXd &A_distance, double m, double p){
    //MatrixXd A_distance = matrix_distance(A);
    MatrixXd A_linkage(A_distance.rows(), A_distance.rows());
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

MatrixXd combine_linkage(MatrixXd &A_linkage, MatrixXd &A_expression){
    int k = A_linkage.rows();
    int n = A_expression.rows();
    MatrixXd A_combine(n,k);
    std::cout<<"\n Combine matrix shape: (" << A_combine.rows() << ", " << A_combine.cols() << ")"<<std::endl;
    // iterate through columns of A_combine
    for(int j = 0; j < k; j++){
        std::cout<<"\n Beam n: " << j <<std::endl;
        double row_total = A_linkage.block(j,0,1,k).sum();
        //std::cout<<"row "<<j<<" total: "<<row_total<<std::endl;
        // since we're considering A_combine and A_expression column-wise, iterate through rows per column
        for(int i = 0; i < n; i++){
            // initialize each entry to simplify the sum
            A_combine(i,j) = 0;
            // compute the weighted sum along row j of the linkage matrix, excluding entry
            for(int r = 0; r < k; r++){
                if(r != j){
                    A_combine(i,j) += (A_linkage(j,r)/row_total)*A_expression(i,r);
                }// end if
            }// end for r
         }// end for i
//        VectorXd dot_product_results = (A_linkage.row(j) * A_expression.transpose()).transpose();
//        // Divide the dot product results by the row total
//        dot_product_results /= row_total;
 //       // Assign the results to the corresponding row of A_combine
 //       for(int i = 0; i < n; i++){
 //           A_combine(i,j) = dot_product_results(i);
  //      }
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

MatrixXd comparison(MatrixXd &expression, MatrixXd &neighbors, double a, double b){
    int n_beams=expression.cols();
    int n_genes=expression.rows();

    //taking the mean over the beams and returning the matrix
    //TODO: make it more efficient?

    MatrixXd mat_new(n_genes,n_genes);

    for(int i=0;i<n_genes; i++){
        if(i%100==0){
            std::cout<<"\n iterating through column " << i <<std::endl;
         }
        for(int j=0;j<n_genes;j++){
            vector<double> vec_for_average;
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

MatrixXd enrichment(MatrixXd &A){
    int N = A.rows();
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
            A_enrichment(i,j) = log2(A(i,j)/S_A[i]+1);
         }// end for i
    }// end for j

    // return matrix containing enrichment score
    return A_enrichment;
}

// Construct colocalisation matrix
//

int construct_colocalisation_matrix(){
    parsemtx mtxobject = parsemtx();
    std::string expressionFile = "/Users/alanpicucci/Desktop/Projects/Transcriptomics/TranscriptomiC/InputData/filtered_feature_bc_matrix/matrix.mtx";
//  std::string beamInputFile = "/Users/alanpicucci/Desktop/Projects/Transcriptomics/TranscriptomiC/InputData/filtered_feature_bc_matrix/barcodes.tsv";
    std::string beamOutputFile = "/Users/alanpicucci/Desktop/Projects/Transcriptomics/TranscriptomiC/InputData/filtered_feature_bc_matrix/beams.tsv";

    mtxobject.readFile(expressionFile);
//  mtxobject.readFile("/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_development/InputData/filtered_feature_bc_matrix/matrix.mtx");
//  mtxobject.print();
//  mtxobject.writeToFile("expression_1.csv");
//  mtxobject.createBeamFile(beamOutputFile,beamInputFile);

//  read beam file
    parseTxtBeams parsetxt = parseTxtBeams();
    parsetxt.readFile(beamOutputFile);
//  convert beam file to eigen matrix for colocalization computation
    Eigen::MatrixXd beam_matrix = parsetxt.convertToMatrix();

//  step 1 - create distance matrix
    std::cout << "[Progress] Running step 1 ..." << std::endl;
    Eigen::MatrixXd* A_distance = new Eigen::MatrixXd;
    *A_distance = matrix_distance(beam_matrix);


// step 2 - linkage matrix with parameters m and p
    double m = 5000;
    double p = 2;
    std::cout << "[Progress] Running step 2 ..." << std::endl;
    Eigen::MatrixXd* A_linkage = new Eigen::MatrixXd;
    *A_linkage = matrix_linkage(*A_distance, m, p);

    delete A_distance;

    std::cout<<(*A_linkage).block(0,0,10,10)<<std::endl;
    std::cout<<"\nLinkage matrix shape: (" << (*A_linkage).rows() << ", " << (*A_linkage).cols() << ")"<<std::endl;


//  step 3 - apply linkage to expression matrix -> neighbouring matrix
    Eigen::MatrixXd expression =  mtxobject.getExpressionDense();

    std::cout<<expression.block(0,0,10,10)<<std::endl;
    std::cout<<"\nExpression matrix shape: (" << expression.rows() << ", " << expression.cols() << ")"<<std::endl;

    std::cout << "[Progress] Running step 3 ..." << std::endl;
    Eigen::MatrixXd* A_combine = new Eigen::MatrixXd;
    *A_combine = combine_linkage(*A_linkage,expression);

    delete A_linkage;

    std::cout<<(*A_combine).block(0,0,10,10)<<std::endl;
    std::cout<<"\nCombine matrix shape: (" << (*A_combine).rows() << ", " << (*A_combine).cols() << ")"<<std::endl;

//  step 4 - compare expression and neighbouring matrices (with default parameters
    std::cout << "[Progress] Running step 4 ..." << std::endl;
    Eigen::MatrixXd A_compare = comparison(expression, *A_combine);

    delete A_combine;

    std::cout<<A_compare.block(0,0,10,10)<<std::endl;
    std::cout<<"\n Comparison matrix shape: (" << A_compare.rows() << ", " << A_compare.cols() << ")"<<std::endl;

// step 5 and 6 - generate colocalisation matrix containing enrichement scores
    std::cout << "[Progress] Running step 5 ..." << std::endl;
    Eigen::MatrixXd A_colocalisation = enrichment(A_compare);

    std::cout<<A_colocalisation.block(0,0,10,10)<<std::endl;
    std::cout<<"\n Colocalisation matrix shape: (" << A_colocalisation.rows() << ", " << A_colocalisation.cols() << ")"<<std::endl;

//  save colocalisation matrix

    std::cout << "[Progress] Saving File ..." << std::endl;
    std::string colocalisationFile = "/Users/alanpicucci/Desktop/Projects/Transcriptomics/TranscriptomiC/InputData/filtered_feature_bc_matrix";
    mtxobject.writeToFile(colocalisationFile,A_colocalisation);

    return 0;

}
