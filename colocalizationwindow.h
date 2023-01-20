#ifndef COLOCALIZATIONWINDOW_H
#define COLOCALIZATIONWINDOW_H

#include "colocalizationheatmapwindow.h"
#include <QDialog>

namespace Ui {
class colocalizationwindow;
}

class colocalizationwindow : public QDialog
{
    Q_OBJECT

public:
    explicit colocalizationwindow(QWidget *parent = nullptr);
    ~colocalizationwindow();

    void makeHeatMap(m);



    Eigen :: MatrixXd getMatrix() {return m;};
    void setMatrix(Eigen::MatrixXd given_m){m = given_m;};

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

    Eigen::MatrixXd m;

    ColocalizationHeatmapWindow *heatmapWindow;

};

#endif // COLOCALIZATIONWINDOW_H
