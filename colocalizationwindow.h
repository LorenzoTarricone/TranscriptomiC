#ifndef COLOCALIZATIONWINDOW_H
#define COLOCALIZATIONWINDOW_H

#include "colocalizationheatmapwindow.h"
#include <QDialog>
#include <QDialog>
#include <Eigen/Eigen>
/*Includes Dense and Sparse header files (the whole Eigen library)*/
using Eigen::MatrixXd;
using namespace std;

namespace Ui {
class colocalizationwindow;
}

class colocalizationwindow : public QDialog
{
    Q_OBJECT

public:
    explicit colocalizationwindow(QWidget *parent = nullptr);
    ~colocalizationwindow();

    void makeHeatMap(MatrixXd m);

signals:
    void MenuWindow();


private slots:

    void on_MenuWindowButton_clicked();

    void on_UploadGenesButton_clicked();

    void on_GenerateHeatmapButton_clicked();

private:
    Ui::colocalizationwindow *ui;

    double pParameter;
    double MParameter;

    QVector<double> xCoordinates;
    QVector<double> yCoordinates;
    QVector<double> pValues;


    ColocalizationHeatmapWindow *heatmapWindow;

};

#endif // COLOCALIZATIONWINDOW_H
