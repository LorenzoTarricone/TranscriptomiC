#ifndef FAKE_COLOCALIZATION_MATRIX_H
#define FAKE_COLOCALIZATION_MATRIX_H

#include <Eigen/Eigen>
/*Includes Dense and Sparse header files (the whole Eigen library)*/
#include <QVector>

using Eigen::MatrixXd;

class fake_colocalization_matrix {
public:
    fake_colocalization_matrix(MatrixXd m);
    ~fake_colocalization_matrix();

    void setdata();
    const MatrixXd& getMatrix() {return Fake;};
    const QVector<double>& getX() {return xCoordinates;};
    const QVector<double>& getY() {return yCoordinates;};
    const QVector<double>& getP() {return pValues;};

private:
    QVector<double> xCoordinates;
    QVector<double> yCoordinates;
    QVector<double> pValues;
    MatrixXd Fake;
};

#endif // FAKE_COLOCALIZATION_MATRIX_H
