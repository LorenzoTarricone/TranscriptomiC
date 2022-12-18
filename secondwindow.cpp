#include "SecondWindow.h"
#include "ui_SecondWindow.h"
#include "qcustomplot.cpp"
#include <iostream>
#include <QMessageBox>


SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);

}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::makePlot() {

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(this->getX(),this->getY());
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone); //lsNone = no line
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssStar); //ssStar = star points

    ui->customPlot->xAxis->setLabel("x"); //axis labels
    ui->customPlot->yAxis->setLabel("y");

    ui->customPlot->xAxis->setRange(0,10); //axis ranges
    ui->customPlot->yAxis->setRange(0,10);

    ui->customPlot->replot();

    /* Uncomment to work on the heatmap or work in Repository: ScatterTest5
    //***********************************************************************************************************************************************

    //Adrian : Here I tried to plot a heat map.
    //Problems:
    //How can I read in the Data from a file?
        // configure axis rect:
        ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
        ui->customPlot->axisRect()->setupFullAxesBox(true);
        ui->customPlot->xAxis->setLabel("x");
        ui->customPlot->yAxis->setLabel("y");

        // set up the QCPColorMap:
        QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);
        int nx = 1000;
        int ny = 1000;
        colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
        colorMap->data()->setRange(QCPRange(-4, 4), QCPRange(-4, 4)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions

        // now we assign some data, by accessing the QCPColorMapData instance of the color map:
        //HERE WE WOULD LIKE TO USE THE DATA FROM THE TEXTFILES
        double x, y, z;
        // Questions: Can we plot specific coordinates or do we have to plot in a specific range?
        for(int xIndex = 0; xIndex<nx; xIndex++){
            for(int yIndex = 0; yIndex<nx; yIndex++){
                 colorMap->data()->cellToCoord(xIndex,yIndex, &x, &y);
                 // random function for third coordinate
                 z = sin(x) + sin(y);
                 colorMap->data()->setCell(xIndex, yIndex, z);

            }
        }

        // set the color gradient of the color map to one of the presets:
        colorMap->setGradient(QCPColorGradient::gpPolar);
        // we could have also created a QCPColorGradient instance and added own colors to
        // the gradient, see the documentation of QCPColorGradient for what's possible.

        // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
        colorMap->rescaleDataRange();

        // rescale the key (x) and value (y) axes so the whole color map is visible:
        ui->customPlot->rescaleAxes(); */

    //************************************************************************************************************************************************
}

<<<<<<< HEAD
<<<<<<< Updated upstream
void SecondWindow::on_ColocalizationButton_clicked()
{
    coWindow = new colocalizationwindow(this);
    coWindow->setX(this->getX());
    coWindow->setY(this->getY());
    coWindow->setP(this->getP());

    this->hide();
    coWindow->show();
    coWindow->makeHeatMap();

}


void SecondWindow::on_BiologicalButton_clicked()
{
    bioWindow = new bioprocesswindow(this);
    this->hide();
    bioWindow->show();
}

=======


void SecondWindow::on_NewFileButton_clicked()
{
    PointerMainWindow->show();
    this->hide();

}


//C:\Users\leona\OneDrive\Bureau\ScatterTest5\recData.csv
>>>>>>> Stashed changes
=======
//C:\Users\leona\OneDrive\Bureau\ScatterTest5\recData.csv
>>>>>>> parent of 63260a0 (Merge branch 'main' into QMake-Revamp-Second-GUIdirected)
