#ifndef UPLOAD_MATRIX_H
#define UPLOAD_MATRIX_H
#include <Eigen/Eigen>
/*Includes Dense and Sparse header files (the whole Eigen library)*/
#include <QVector>

using Eigen::MatrixXd;
class upload_matrix
{
public:
    upload_matrix();
    const MatrixXd& getMatrix() {return m;};

    bool setData_Matrix(std::string fileName); // Adrian: I try to read a file as matrix and plot it


 private:
    MatrixXd m;

    QVector<double> xCoordinates;
    QVector<double> yCoordinates;
    QVector<double> pValues;

    std::string x;
    std::string y;
    std::string p;
};

#endif // UPLOAD_MATRIX_H
