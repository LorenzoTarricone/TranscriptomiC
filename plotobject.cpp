#include "plotobject.h"


plotObject::plotObject(){

}

plotObject::plotObject(Eigen::MatrixXd matrix){
    compute(matrix);
}

void plotObject::compute(Eigen::MatrixXd matrix){
    int rows = matrix.rows();
    int cols = matrix.cols();

    X.clear();
    Y.clear();
    vals.clear();

    for (int j = 0; j < cols; j++){
        for(int i = 0; i < rows; i++){
            X.push_back(i);
            Y.push_back(j);
            vals.push_back(matrix(i,j));
        }
    }
}

std::vector<double> plotObject::getExprX(){
    return X;
}


std::vector<double> plotObject::getExprY(){
    return Y;
}


std::vector<double> plotObject::getExprVal(){
    return vals;
}
