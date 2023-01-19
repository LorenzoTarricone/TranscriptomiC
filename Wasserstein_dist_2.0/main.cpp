#include <iostream>
#include <wasserstein.h>
#include <Eigen/Dense>
#include <time.h>
#include <cmath>


double Wass_distance (Eigen::MatrixXd& Coord_mat, Eigen::MatrixXd& Express_mat, int gene_1, int gene_2, int n_computations){


    std::vector<double> First_expr(Express_mat.cols());
    for(int i = 0; i < Express_mat.cols(); i++)
    {
       //this will put all the elements in the first column of Eigen::Matrix into the column3 vector
        First_expr.at(i) = Express_mat(gene_1, i);
    }



    std::vector<double> Second_expr(Express_mat.cols());
    for(int j = 0; j < Express_mat.cols(); j++)
    {
       //this will put all the elements in the first column of Eigen::Matrix into the column3 vector
        Second_expr.at(j) = Express_mat(gene_2, j);
    }

    srand( (unsigned)time( NULL ) );

    //Calculte random direction Wass dist

    std::vector<double> All_dists(n_computations);

    for(int timer = 0; timer < n_computations; timer ++){


        double value1 = (double) rand()/RAND_MAX;
        double value2 = sqrt(1 - (value1 * value1));


        std::vector<double> Proj_coord(Coord_mat.rows());

        for( int i = 0; i < Coord_mat.cols(); i++){
            Proj_coord.at(i) = Coord_mat(i, 0) * value1 + Coord_mat(i, 1) * value2;
        }

         double dist = wasserstein(Proj_coord,First_expr,Proj_coord,Second_expr);
         All_dists.push_back(dist);

    }

    double avg = std::reduce(All_dists.begin(), All_dists.end()) / n_computations;


    return avg;
}




Eigen::MatrixXd Wass_Matrix (Eigen::MatrixXd& Coord_mat, Eigen::MatrixXd& Express_mat, int n_comput){

    Eigen::MatrixXd EMD = Eigen::MatrixXd::Zero(Express_mat.rows(),Express_mat.rows());

    for (int gene_1 = 0; gene_1 < Express_mat.rows() - 1; gene_1++){
        for(int gene_2 = gene_1 + 1; gene_2 < Express_mat.rows(); gene_2++){

            double value=Wass_distance(Coord_mat, Express_mat, gene_1, gene_2, n_comput);
            std::cout << "Wass distance:"<< value <<std::endl;
            EMD(gene_1,gene_2)=value;
            EMD(gene_2,gene_1)=value;
        }
    }

    std::cout << "\n\n\nThe final matrix is\n\n" << EMD << std::endl;

    return EMD;
}


int main(){

    Eigen::MatrixXd Coord_mat(4, 2);
      Coord_mat   <<  1.1, 2,
                      2.2, 2,
                      3.1, 2,
                        3, 50;

      Eigen::MatrixXd Express_mat(5, 4);
      Express_mat   <<  1.1, 2, 3, 5,
                        2.2, 2, 1, 2.3,
                        3.1, 2, 3, 5.3,
                        3.1, 1, 2, 6,
                          4, 5, 2, 1;


     Wass_Matrix(Coord_mat, Express_mat, 5);


}
