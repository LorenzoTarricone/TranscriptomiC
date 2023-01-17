#include "biologicalprocess.h"

//biologicalprocess::biologicalprocess(parsefile files)
//{

//}

Eigen::MatrixXd biologicalprocess::compute_total_expression(const Eigen::MatrixXd& expression, const Eigen::MatrixXd& spatial){
    int rows = expression.rows();
    int cols = expression.cols();

    Eigen::MatrixXd tot = Eigen::MatrixXd(cols,3);
    tot.block(0,0,cols,2) = spatial;

    // initialize last column to 1
    for(int j = 0; j < cols; j++){
        tot(j,2) = 0;
    }

    for(int j = 0; j < cols; j++){
        for(int i = 0; i < rows; i++){
            tot(j,2) += expression(i,j);
        }
    }

    return tot;
}

void biologicalprocess::compute_tot_expr(){
    std::cout << "[Progress] Computing total expression ... "<<std::endl;



}
