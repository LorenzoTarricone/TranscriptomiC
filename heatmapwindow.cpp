#include "heatmapwindow.h"
#include "bioprocesswindow.h"
#include "ui_heatmapwindow.h"
#include <iostream>

HeatMapWindow::HeatMapWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HeatMapWindow)
{
    ui->setupUi(this);
}

HeatMapWindow::~HeatMapWindow()
{
    delete ui;
}

/*void HeatMapWindow::makeHeatMap(){

    // configure axis rect:
           ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
           ui->customPlot->axisRect()->setupFullAxesBox(true);
           ui->customPlot->xAxis->setLabel("x");
           ui->customPlot->yAxis->setLabel("y");
           // set up the QCPColorMap:
           QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);

           // Use nx = ny = 7 for rec_Data: We need to find nx and ny for each individual file.
           // It only works for quadratic matrices, we want to get the biggest x- and y-coordinate of the coordinate vectors
           int nx = sqrt(getX().size());
           std::cout << "nx: "<< nx;// check if nx is correct: delete this line later
           int ny = sqrt(getX().size());
           std::cout << "ny:"<< ny; // check if ny is correct: delte this line later

           colorMap->data()->setSize(nx, ny);
           colorMap->data()->setRange(QCPRange(0, nx-1), QCPRange(0, ny-1)); //set the range of the HeatMap;
           //This is just for rec_Data: We need to find the Range for each individual file

           // now we assign some data, by accessing the QCPColorMapData instance of the color map:
           //HERE WE WOULD LIKE TO USE THE DATA FROM THE TEXTFILES

           for(int Index = 0; Index< nx * ny; Index++){ // We have 49 data points for rec_Data file
               colorMap->data()->setCell(getX()[Index], getY()[Index], getP()[Index]);
           }
           // add a color scale
           QCPColorScale *colorScale = new QCPColorScale(ui->customPlot);
           ui->customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
           colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
           colorMap->setColorScale(colorScale); // associate the color map with the color scale
           colorScale->axis()->setLabel("Third coordinate");

           // set the color gradient of the color map to one of the presets:
           colorMap->setGradient(QCPColorGradient::gpPolar);
           // we could have also created a QCPColorGradient instance and added own colors to
           // the gradient, see the documentation of QCPColorGradient for what's possible.

           //Uncomment for ColourMap without interpolation
           //colorMap->setInterpolate(false);

           // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
           colorMap->rescaleDataRange();

           // rescale the key (x) and value (y) axes so the whole color map is visible:
           ui->customPlot->rescaleAxes();

}*/

void HeatMapWindow::makeHeatMap(const MatrixXd m){

    // configure axis rect:
               ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
               ui->customPlot->axisRect()->setupFullAxesBox(true);
               ui->customPlot->xAxis->setLabel("x");
               ui->customPlot->yAxis->setLabel("y");
               // set up the QCPColorMap:
               QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);

               int number_rows = m.rows();
               int number_cols = m.cols();

               colorMap->data()->setSize(number_cols, number_rows);
               colorMap->data()->setRange(QCPRange(0, number_cols-1), QCPRange(0, number_rows-1)); //set the range of the HeatMap;

               // now we assign some data, by accessing the QCPColorMapData instance of the color map:

               for(int i = 0; i < number_cols; i++){
                   for(int j = 0; j< number_rows; j++){
                       if(m(i,j)<3 && m(i,j)>-3){
                           colorMap->data()->setCell(i, j, m(i,j));} // plot only data between -3 and 3
                       else{colorMap->data()->setCell(i, j, 0);}

                       }
                   }
              // Ticks
              QSharedPointer<QCPAxisTickerText> textTickerx(new QCPAxisTickerText);

              // tick strategy. readability is more important
              textTickerx->setTickStepStrategy(QCPAxisTicker::tssReadability);
              textTickerx->setTickCount(3);

              //set x-axis ticker
              ui->customPlot->xAxis->setTicker(textTickerx);

              QSharedPointer<QCPAxisTickerText> textTickery(new QCPAxisTickerText);
              // tick strategy. readability is more important
              textTickery->setTickStepStrategy(QCPAxisTicker::tssReadability);
              textTickery->setTickCount(3);

              //set y-axis ticker
              ui->customPlot->yAxis->setTicker(textTickery);

              for(int i = 0; i < number_cols; i++){
                  textTickerx->addTick(i, "Bacteria");};

              for(int j = 0; j< number_rows; j++){
                  textTickery->addTick(j, "Bacteria");};

              // color scale:
               QCPColorScale *colorScale = new QCPColorScale(ui->customPlot);
               ui->customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
               colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right
               colorScale->setRangeDrag(&free); // drag the data range. we dont need that
               colorMap->setColorScale(colorScale); // associate the color map with the color scale
               colorScale->axis()->setLabel("Intensity");
/*
               //color gradient:
               QCPColorGradient gradient; // empty gradient with no defined colour stops
               //Hue variation similar to a spectrum, often used in numerical visualization (creates banding illusion but allows more precise magnitude estimates)
               gradient.setColorStopAt(0, QColor(0,0,0));//Sets the color the gradient will have at the specified position (from 0 to 1).
               gradient.setColorStopAt(1, QColor(255,100,0));//In between these color stops, the color is interpolated according to setColorInterpolation.
               gradient.setColorInterpolation(QCPColorGradient::ciRGB);//interpolated linearly in RGB color space.
               gradient.setNanHandling(QCPColorGradient::nhLowestColor); //NaN data points as the lowest color.
               gradient.setLevelCount(350); //sets the number of discretization levels of the color gradient to n (max. n = 350)
               colorMap->setGradient(gradient);//assign it to the heatmap */

               colorMap->setGradient(QCPColorGradient::gpJet);

               //Uncomment for ColourMap without interpolation
               colorMap->setInterpolate(false);

               // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
               QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->customPlot);
               ui->customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
               colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

               // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
               colorMap->rescaleDataRange();

               // rescale the key (x) and value (y) axes so the whole color map is visible:
               ui->customPlot->rescaleAxes();


}

void HeatMapWindow::on_SaveHeatmapButton_clicked()
{
    QPixmap heatmap;
    QString filename;

    //grabs the heatmap widget as a QPixmap
    heatmap = ui->customPlot->grab();

    //opens the file explorer and get file name (with full location)
    filename = QFileDialog::getSaveFileName(this,"Save file");

    heatmap.save(filename + ".png"); //saves as .png

}

void HeatMapWindow::on_MenuButton_clicked()
{
    this->close();
    emit PreviousWindow();

}

