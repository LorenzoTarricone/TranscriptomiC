#ifndef BIOLOGICALPROCESS_H
#define BIOLOGICALPROCESS_H

// TODO: Implement inheritance for biological process and colocalisation

#include "parsefile.h"
#include "computation.h"

class biologicalprocess : public computation
{
public:
    biologicalprocess(parsefile files,int rows = 0, int cols = 0) : computation(files,rows,cols){};
    double WassersteinDistance(const Eigen::MatrixXd& mat1, const Eigen::MatrixXd& mat2, const Eigen::MatrixXd& distance);
    void bioprocess_2(int n);
    void compute_tot_expr();


private:
    Eigen::MatrixXd total_expression;
    Eigen::MatrixXd perc_expression;

    Eigen::MatrixXd EMD_Matrix(const Eigen::MatrixXd& expression, const Eigen::MatrixXd& spatial);
    std::map<int, std::vector<std::string>> Cluster(Eigen::MatrixXd& EMD, int n);
    Eigen::MatrixXd compute_total_expression(const Eigen::MatrixXd& expression, const Eigen::MatrixXd& spatial,bool perc=false);


};

#endif // BIOLOGICALPROCESS_H
