#ifndef PLOTOBJECT_H
#define PLOTOBJECT_H

#include "Eigen/Dense"
#include <stdlib.h>
#include <vector>

class plotObject
{
public:
    plotObject();
    plotObject(Eigen::MatrixXd);
    std::vector<double> getExprX();
    std::vector<double> getExprY();
    std::vector<double> getExprVal();
    void compute(Eigen::MatrixXd matrix);

private:
    std::vector<double> X;
    std::vector<double> Y;
    std::vector<double> vals;

};

#endif // PLOTOBJECT_H
