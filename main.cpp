#include "mainwindow.h"
#include <QApplication>
#include <Eigen/Dense>

using Eigen::MatrixXd;

int main(int argc, char *argv[])
{
    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;

    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
}
