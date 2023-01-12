#include "colocalizationheatmapwindow.h"
#include "ui_colocalizationheatmapwindow.h"
#include "heatmapwindow.h"


ColocalizationHeatmapWindow::ColocalizationHeatmapWindow(QWidget *parent) :
    HeatMapWindow(parent),
    ui(new Ui::ColocalizationHeatmapWindow)
{
    ui->setupUi(this);
}

ColocalizationHeatmapWindow::~ColocalizationHeatmapWindow()
{
    delete ui;
}
