#include "heatmapwindow.h"
#include "ui_heatmapwindow.h"
#include <iostream>
#include "Eigen/Dense"

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

void HeatMapWindow::makeHeatMap(const Eigen::MatrixXd m){

    // configure axis rect:
               ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
               ui->customPlot->axisRect()->setupFullAxesBox(true);
               ui->customPlot->xAxis->setLabel("x");
               ui->customPlot->yAxis->setLabel("y");
               // set up the QCPColorMap:
               QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);

               int number_rows = m.rows(); // number beams x,y -coordinate
               int number_cols = m.cols(); // should be 3
               // data size
               int data_size = number_cols; // just the third column

               // Maybe I have to change the size and find first max, min value
               double maxValx = m.col(0).maxCoeff(); // biggest x- value
               double minValx = m.col(0).minCoeff(); // smalles x- value
               double maxValy = m.col(1).maxCoeff(); // biggest y- value
               double minValy = m.col(1).minCoeff(); // smallest y- value

               colorMap->data()->setSize(number_rows, number_rows); // Change that

               //Maybe use here min and max values. If it doesn't work create a bigger map first
               colorMap->data()->setRange(QCPRange(minValx-1, maxValx+1), QCPRange(minValy-1,maxValy+1));
               //colorMap->data()->setRange(QCPRange(0, number_cols-1), QCPRange(0, number_rows-1)); //set the range of the HeatMap;

              /* //Quantile Matrix : I dont know if this is right.
               double median = 0;
               double q1 = 0;
               double q3 = 0;
               double eta = 0.005;

               for(int i= 0; i<number_cols; i++){
                   for (int j = 0; j<number_rows; j++){
                      median += eta *std::copysign(1.0f,m(i,j) - median);
                   }
               }
               for(int i= 0; i<number_cols; i++){
                   for (int j = 0; j<number_rows; j++){
                       if(m(i,j) < median)
                           q1 += eta*std::copysign(1.0f,m(i,j) - q1);
                       else
                           q3 += eta*std::copysign(1.0f,m(i,j) - q3);
                   }
               }
               //test
               std::cout << median;
               std::cout << q1;
               std::cout << q3; */



               //95 PERCENT CONFIDENCE interval
               //calculate mean
               double mean = 0.0;
               for(int i= 0; i<data_size; i++){
                      mean += m(i,2); };//only the third column

                         mean /= data_size;

               //calculate standard deviation
               double sd = 0.0;
               for(int i= 0; i<data_size; i++){
                      sd += pow(m(i,2) - mean,2);} // only third column
               //standart error
               sd = sqrt(sd/(data_size));

               //margin of error
               double ci = 2* sd;

               double q1 = mean-ci;
               double q3 = mean+ci;
               //output
               std::cout << "95% Confidence Interval: [" << q1 << ", " << q3 << "]" << std::endl;




               // now we assign some data, by accessing the QCPColorMapData instance of the color map:

               for(int i = 0; i < number_rows; i++){
                       if(m(i,2)>q1 && m(i,2)<q3){ // if the third value of the row is in the confidence interval
                           colorMap->data()->setCell(m(i,0),m(i,1), m(i,2));} // plot only data between q1 and q3 here we want quantile
                       else{colorMap->data()->setCell(m(i,0),m(i,1), m(i,2));} //assign 0

                   }

               // Do we have axis labels?
              /*// Ticks and Labels
              QSharedPointer<QCPAxisTickerText> textTickerx(new QCPAxisTickerText);

              // tick strategy. readability is more important
              textTickerx->setTickStepStrategy(QCPAxisTicker::tssReadability);
              textTickerx->setTickOrigin(0);// sets origin (not necessary)
              textTickerx->setTickCount(3);

              QSharedPointer<QCPAxisTickerText> textTickery(new QCPAxisTickerText);

              // tick strategy. readability is more important
              textTickery->setTickStepStrategy(QCPAxisTicker::tssReadability);
              textTickery->setTickOrigin(0);// sets origin (not necessary)
              textTickery->setTickCount(4);

              //assign the labels using vectors
              QVector<QString> xgenenames;
              QVector<double> xpositions;
              for(int i = 0; i < number_cols; i++){
                  xgenenames.append("Bacteria");
                  xpositions.append(i);
              };

              QVector<QString> ygenenames;
              QVector<double> ypositions;
              for(int i = 0; i < number_cols; i++){
                  ygenenames.append("Bacteria");
                  ypositions.append(i);
              };


              textTickerx->setTicks(xpositions, xgenenames);
              textTickery->setTicks(ypositions, ygenenames);

              ///assign each label individually
              for(int i = 0; i < number_cols; i++){
                  textTickerx->addTick(i, "Bacteria");}; // Here we need the gene names

              for(int j = 0; j< number_rows; j++){
                  textTickery->addTick(j, "Bacteria");}; // Here we need the gene names



              //set x-axis ticker
              ui->customPlot->xAxis->setTicker(textTickerx);
              ui->customPlot->xAxis->setTickLabelPadding(8); //Sets the distance between the axis base line
              ui->customPlot->xAxis->setTickLabelColor(QColorConstants::Red); //Sets the color of the tick labels.
              ui->customPlot->xAxis->setTickLabelRotation(-90.0); //Sets the rotation of the tick labels.

              //set y-axis ticker
              ui->customPlot->yAxis->setTicker(textTickery);
              ui->customPlot->yAxis->setTickLabelColor(QColorConstants::Red); //Sets the color of the tick labels. */

              // color scale:
               QCPColorScale *colorScale = new QCPColorScale(ui->customPlot);
               ui->customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
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

