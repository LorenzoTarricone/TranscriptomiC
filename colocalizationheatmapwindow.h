#ifndef COLOCALIZATIONHEATMAPWINDOW_H
#define COLOCALIZATIONHEATMAPWINDOW_H

#include "heatmapwindow.h"
#include "Eigen/Eigen"

namespace Ui {
class ColocalizationHeatmapWindow;
}

class ColocalizationHeatmapWindow : public HeatMapWindow
{
    Q_OBJECT

public:
    explicit ColocalizationHeatmapWindow(QWidget *parent = nullptr);
    ~ColocalizationHeatmapWindow();

 //   void on_SaveHeatmapButton_clicked();
    void makeHeatMap(const Eigen::MatrixXd m);

    void on_SaveMatrixButton_clicked();


private:
    Ui::ColocalizationHeatmapWindow *ui;
};

#endif // COLOCALIZATIONHEATMAPWINDOW_H
