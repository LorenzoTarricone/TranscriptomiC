#ifndef COLOCALIZATIONHEATMAPWINDOW_H
#define COLOCALIZATIONHEATMAPWINDOW_H

#include "colocalisation.h"
#include "heatmapwindow.h"


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

    void on_SaveMatrixButton_clicked();
    void setColocalisationObject(colocalisation* object){this->object = object;};



private:
    Ui::ColocalizationHeatmapWindow *ui;
    colocalisation* object;
};

#endif // COLOCALIZATIONHEATMAPWINDOW_H
