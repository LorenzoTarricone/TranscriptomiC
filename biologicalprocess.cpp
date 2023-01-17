#include "biologicalprocess.h"

Eigen::MatrixXd biologicalprocess::compute_total_expression(const Eigen::MatrixXd& expression, const Eigen::MatrixXd& spatial, bool perc){
    std::cout << "[Progress] Calling total expression function ... "<<std::endl;
    int rows = expression.rows();
    int cols = expression.cols();

    std::cout << "Expression matrix of shape ("<<rows<<","<<cols<<") - spatial data of shape ("<<spatial.rows()<<","<<spatial.cols()<<")"<<std::endl;
    std::cout << spatial.block(0,0,cols,spatial.cols()) << std::endl;
    Eigen::MatrixXd tot = Eigen::MatrixXd(cols,3);




    // initialize last column to 0
    for(int j = 0; j < tot.rows(); j++){
        tot(j,2) = 0;
    }

    std::cout << spatial.block(0,0,expression.cols(),spatial.cols()) << std::endl;

    for(int j = 0; j < expression.cols(); j++){
        for(int i = 0; i < expression.rows(); i++){
            tot(j,0) = spatial(j,0);
            tot(j,1) = spatial(j,1);
            if(perc){
                tot(j,2) += expression(i,j)/total_expression(j,2);
            }

        }
    }

    std::cout << "total expression data of shape ("<<tot.rows()<<","<<tot.cols()<<")"<<std::endl;


    std::cout << tot << std::endl;

    return tot;
}

void biologicalprocess::compute_tot_expr(){
    std::cout << "[Progress] Computing total expression ... "<<std::endl;
    total_expression = compute_total_expression(*expression,A_spatial);

    std::cout << "[Progress] Filter by genes ... "<<std::endl;
    filter(false,true);
    std::cout << "[Progress] Filter by genes done. "<<std::endl;

    std::cout << "[Progress] Computing expression percentage ... "<<std::endl;
    perc_expression = compute_total_expression(*expression,A_spatial,true);



}
