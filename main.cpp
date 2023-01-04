#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    // Test Eigen library and to plot a heatmap using a fake-colcalization matrix
    //Colocalization
    MatrixXd m(3,3);
      m(0,0) = 0.3;
      m(0,1) = 0.5;
      m(0,2) = -1;

      m(1,0) = 1,
      m(1,1) = 0.7;
      m(1,2) = 0.2;

      m(2,0) = -1;
      m(2,1) = 1;
      m(2,2) = 0.5;

      fake_colocalization_matrix fake = fake_colocalization_matrix(m);
      fake.setdata();

      SecondWindow s;
      s.setX(fake.getX());
      s.setY(fake.getY());
      s.setP(fake.getP());
      s.makePlot();
      s.show();


    return a.exec();

//    parsemtx mtxobject = parsemtx();
//    mtxobject.readFile("mtx_test.mtx");
//    mtxobject.print();
//    return 0;
}
