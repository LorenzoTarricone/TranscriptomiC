#include "heatmapwindow.h"
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

void HeatMapWindow::makeHeatMap(){
    //Craetes a HeatMap using vectors

    // configure axis:
               ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by zooming/dragging
               ui->customPlot->axisRect()->setupFullAxesBox(true);
               ui->customPlot->xAxis->setLabel("x");
               ui->customPlot->yAxis->setLabel("y");

               // QCPColorMap:
               QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);

               // Vector size // Need to change that
               int nx = sqrt(getX().size());
               int ny = sqrt(getY().size());

               int data_size = getP().size();

               //set the range of the HeatMap;
               colorMap->data()->setSize(nx, ny);
               colorMap->data()->setRange(QCPRange(0, nx-1), QCPRange(0, ny-1)); //set the range of the HeatMap;

               /*//Quantile Vector
               double median = 0;
               double q1 = 0;
               double q3 = 0;
               double eta = 0.005;

               for(int i= 0; i<getP().size(); i++){
                   median += eta *std::copysign(1.0f,getP()[i] - median);

               }
               for(int j= 0; j<getP().size(); j++){

                       if(getP()[j] < median)
                           q1 += eta*std::copysign(1.0f,getP()[j] - q1);
                       else
                           q3 += eta*std::copysign(1.0f,getP()[j] - q3);

               }
               //test
               std::cout << median;
               std::cout << q1;
               std::cout << q3;*/

               //95 PERCENT CONFIDENCE interval
               //calculate mean
               double mean = 0.0;

               for(int i= 0; i<getP().size(); i++){
                   mean += getP()[i]; };

               mean /= data_size;

               //calculate standard deviation
               double sd = 0.0;
               for(int i= 0; i<data_size; i++){
                   sd += pow(getP()[i] - mean,2);}

               //standart error
               sd = sqrt(sd/(data_size));

               //margin of error
               double ci = 2* sd;

               double q1 = mean-ci;
               double q3 = mean+ci;
               //output
               std::cout << "95% Confidence Interval: [" << q1 << ", " << q3 << "]" << std::endl;




               for(int Index = 0; Index < data_size; Index++){
                   if(getP()[Index]>q1 && getP()[Index]<q3){
                       colorMap->data()->setCell(getX()[Index], getY()[Index], getP()[Index]);//if the value is in the confidence level.
                   }
               }
               //Labels and Tickers?

               //Color scale:
               QCPColorScale *colorScale = new QCPColorScale(ui->customPlot);
               ui->customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis
               colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right
               colorScale->setBarWidth(8); //width of scale
               colorScale->setRangeDrag(&free); // drag the data range. we dont need that
               colorMap->setColorScale(colorScale); // associate the color map with the color scale
               colorScale->axis()->setLabel("Intensity");

               //color gradient:
               QCPColorGradient gradient; // empty gradient with no defined colour stops
               //Hue variation similar to a spectrum, often used in numerical visualization (creates banding illusion but allows more precise magnitude estimates)
               //In between these color stops, the color is interpolated according to setColorInterpolation.
               gradient.setColorInterpolation(QCPColorGradient::ciRGB);//interpolated linearly in RGB color space
               gradient.setColorStopAt(0, QColor(0, 0, 100));
               gradient.setColorStopAt(0.15, QColor(0, 50, 255));
               gradient.setColorStopAt(0.35, QColor(0, 255, 255));
               gradient.setColorStopAt(0.65, QColor(255, 255, 0));
               gradient.setColorStopAt(0.85, QColor(255, 30, 0));
               gradient.setColorStopAt(1, QColor(100, 0, 0));
               gradient.setNanHandling(QCPColorGradient::nhLowestColor); //NaN data points as the lowest color.
               gradient.setLevelCount(350); //sets the number of discretization levels of the color gradient to n (max. n = 350)
               colorMap->setGradient(gradient);//assign it to the heatmap

               //Uncomment for ColourMap without interpolation
               colorMap->setInterpolate(false);

               // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
               QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->customPlot);
               ui->customPlot->axisRect()->setMarginGroup(QCP::msTop|QCP::msBottom, marginGroup);
               colorScale->setMarginGroup(QCP::msTop|QCP::msBottom, marginGroup);

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

