#ifndef FAKE_COLOCALIZATION_MATRIX_H
#define FAKE_COLOCALIZATION_MATRIX_H

#include <Eigen/Eigen>
/*Includes Dense and Sparse header files (the whole Eigen library)*/
using Eigen::MatrixXd;

#include <QDialog>

namespace Ui {
class fake_colocalization_matrix;
}

class fake_colocalization_matrix : public QDialog
{
    Q_OBJECT

public:
    explicit fake_colocalization_matrix(QWidget *parent = nullptr);
    ~fake_colocalization_matrix();

    void make_heat_plot();
    const MatrixXd& getMatrix() {return Fake;};

private:
    Ui::fake_colocalization_matrix *ui;
    MatrixXd Fake;
};

#endif // FAKE_COLOCALIZATION_MATRIX_H
