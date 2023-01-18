#ifndef BIOLOGICALPROCESS_H
#define BIOLOGICALPROCESS_H

// TODO: Implement inheritance for biological process and colocalisation

#include "parsefile.h"
#include "computation.h"

class biologicalprocess : public computation
{
public:
    biologicalprocess(parsefile files,int rows = 0, int cols = 0) : computation(files,rows,cols){};
//    void filter(bool zeroes = true, double min_expr_perc = 0.1);
//    void normalisation(std::string type_of_normal = "col_mean");

    double WassersteinDistance(const Eigen::MatrixXd& mat1, const Eigen::MatrixXd& mat2, const Eigen::MatrixXd& distance);
    void bioprocess_2(int n);
    void compute_tot_expr();


private:
//    parsemtx expression_raw;
//    parsing spatial;
//    std::vector<std::string> geneNames;
//    std::vector<std::string> geneSubset;

//    Eigen::MatrixXd A_spatial;
    Eigen::MatrixXd total_expression;
    Eigen::MatrixXd perc_expression;
//    Eigen::MatrixXd* expression;

    Eigen::MatrixXd EMD_Matrix(const Eigen::MatrixXd& expression, const Eigen::MatrixXd& spatial);
    std::map<int, std::vector<std::string>> Cluster(Eigen::MatrixXd& EMD, int n);
    Eigen::MatrixXd compute_total_expression(const Eigen::MatrixXd& expression, const Eigen::MatrixXd& spatial,bool perc=false);


};

#endif // BIOLOGICALPROCESS_H
