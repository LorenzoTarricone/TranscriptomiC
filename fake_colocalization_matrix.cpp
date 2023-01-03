#include "fake_colocalization_matrix.h"
#include <iostream>

fake_colocalization_matrix::fake_colocalization_matrix(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fake_colocalization_matrix)
{
    ui->setupUi(this);
    // Test colocalization matrix
    MatrixXd m(3,3); // create random calocalization matrix with values between -1 and 1
      m(0,0) = 0.3;
      m(0,1) = 0.5;
      m(0,2) = -1;

      m(1,0) = 1,
      m(1,1) = 0.7;
      m(1,2) = 0.2;

      m(2,0) = -1;
      m(2,1) = 1;
      m(2,2) = 0.5;

      Fake = m;
}

fake_colocalization_matrix::~fake_colocalization_matrix()
{
    delete ui;
}


void fake_colocalization_matrix::make_heat_plot(){
     std::cout << "Here is the matrix m:\n" << Fake << std::endl;

}

