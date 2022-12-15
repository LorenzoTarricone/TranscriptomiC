#ifndef PARSEMTX_H
#define PARSEMTX_H

#include <string>
#include <Eigen/Dense>

class parsemtx
{
public:
    parsemtx();
    void readFile(std::string filename);

private:
    Eigen::MatrixXd matrix;
};

#endif // PARSEMTX_H
