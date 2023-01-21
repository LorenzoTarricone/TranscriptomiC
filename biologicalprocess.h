#ifndef BIOLOGICALPROCESS_H
#define BIOLOGICALPROCESS_H

// TODO: Implement inheritance for biological process and colocalisation

#include "parsefile.h"
#include "computation.h"

class biologicalprocess : public computation
{
public:
    biologicalprocess(): computation(){};
    biologicalprocess(parsefile files,int rows = 0, int cols = 0) : computation(files,rows,cols){};
    double WassersteinDistance(const Eigen::MatrixXd& mat1, const Eigen::MatrixXd& mat2, const Eigen::MatrixXd& distance);
    std::vector<std::string> bioprocess_2(int n=5, int num_runs=5);
    void compute_tot_expr();
    std::vector<std::vector<std::string>> plottable(std::vector<std::string> cluster_dict);



    const Eigen::MatrixXd &getPerc_expression() const;

private:
    Eigen::MatrixXd total_expression;
    Eigen::MatrixXd perc_expression;

    Eigen::MatrixXd compute_total_expression(const Eigen::MatrixXd& expression, const Eigen::MatrixXd& spatial,bool perc=false);
    int findNearestMedoid(Eigen::MatrixXd distanceMatrix, std::vector<int> medoids, int point);
    std::vector<std::string> kMedoidsClustering(Eigen::MatrixXd distanceMatrix, int k=5, int num_runs=3);
    double Wass_distance(Eigen::MatrixXd& Coord_mat, Eigen::MatrixXd& Express_mat, int gene_1, int gene_2, int n_computations);
    Eigen::MatrixXd Wass_Matrix(Eigen::MatrixXd& Coord_mat, Eigen::MatrixXd& Express_mat, int n_compute=3);


};

#endif // BIOLOGICALPROCESS_H
