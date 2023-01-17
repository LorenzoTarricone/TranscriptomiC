#ifndef BIOLOGICALPROCESS_H
#define BIOLOGICALPROCESS_H

// TODO: Implement inheritance for biological process and colocalisation

#include "parsefile.h"
#include "computation.h"

class biologicalprocess : public computation
{
public:
    biologicalprocess(parsefile files,int rows = 0, int cols = 0) : computation(files,rows,cols){};
    void filter(bool zeroes = true, double min_expr_perc = 0.1);
    void normalisation(std::string type_of_normal = "col_mean");

    void compute_tot_expr();


private:
    parsemtx expression_raw;
    parsing spatial;
    std::vector<std::string> geneNames;
    std::vector<std::string> geneSubset;

    Eigen::MatrixXd A_spatial;
    Eigen::MatrixXd total_expression;
    Eigen::MatrixXd* expression;

    Eigen::MatrixXd compute_total_expression(const Eigen::MatrixXd& expression, const Eigen::MatrixXd& spatial);


};

#endif // BIOLOGICALPROCESS_H
