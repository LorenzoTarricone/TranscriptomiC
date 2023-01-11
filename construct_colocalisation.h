#ifndef CONSTRUCT_COLOCALISATION_H
#define CONSTRUCT_COLOCALISATION_H

#include <iostream>
#include <Eigen/Dense>
#include <vector>

class construct_colocalisation
{
public:
    construct_colocalisation();
    //defining functions for colocalization matrix
    static Eigen::MatrixXd matrix_distance(Eigen::MatrixXd A);

    static Eigen::MatrixXd matrix_linkage(Eigen::MatrixXd &A, double m, double p);

    static Eigen::MatrixXd combine_linkage(Eigen::MatrixXd &A_linkage, Eigen::MatrixXd &A_expression);

    static Eigen::MatrixXd comparison(Eigen::MatrixXd &expression, Eigen::MatrixXd &neighbors, double a=1, double b=0.5);

    static Eigen::MatrixXd enrichment(Eigen::MatrixXd &A);


private:
    double distance(double x1, double x2, double y1, double y2);
    double max (double a, double b);
    double linkage(double d, double m, double p);
};

#endif // CONSTRUCT_COLOCALISATION_H
