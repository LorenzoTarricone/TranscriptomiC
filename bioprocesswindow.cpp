#include "bioprocesswindow.h"
#include "colocalizationwindow.h"
#include "qcustomplot.h"
#include "ui_bioprocesswindow.h"
#include "qdebug.h"
#include <algorithm>
#include <iostream>

bioprocesswindow::bioprocesswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bioprocesswindow)
{
    ui->setupUi(this);

}

bioprocesswindow::~bioprocesswindow()
{
    delete ui;
}

void bioprocesswindow::makeHeatMap(){

          // configure axis:
           ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by zooming/dragging
           ui->customPlot->axisRect()->setupFullAxesBox(true);
           ui->customPlot->xAxis->setLabel("x");
           ui->customPlot->yAxis->setLabel("y");

           // QCPColorMap:
           QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);

           // Vector lenght
           int nx = sqrt(getX().size());
           int ny = sqrt(getY().size());

           //set the range of the HeatMap;
           colorMap->data()->setSize(nx, ny);
           colorMap->data()->setRange(QCPRange(0, nx-1), QCPRange(0, ny-1)); //set the range of the HeatMap;

           //Quantile Vector
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
           std::cout << q3;



           for(int Index = 0; Index < nx * ny; Index++){
                          colorMap->data()->setCell(getX()[Index], getY()[Index], getP()[Index]);
                      }

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

void bioprocesswindow::on_SaveHeatmapButton_clicked()
{
    QPixmap heatmap;
    QString filename;

    //grabs the heatmap widget as a QPixmap
    heatmap = ui->customPlot->grab();

    //opens the file explorer and get file name (with full location)
    filename = QFileDialog::getSaveFileName(this,"Save file");

    heatmap.save(filename + ".png"); // saves as .png

}

void bioprocesswindow::setProcessesToAnalyze(){
    //this function will just create a vector with all the processes we can analyze
    //TEMPORARY, in the end we will have something a lot more sophisticated

    processesToAnalyze.push_back("hypoxia");

}


void bioprocesswindow::on_AnalyzeButton_clicked()
{
    QString bio;
    std::string process;

    bio = ui->plainTextEdit->toPlainText(); //gets the text the user wrote
    ui->plainTextEdit->setPlainText(""); //resets the text box to be empty

    process = bio.toStdString();

    std::transform(process.begin(), process.end(), process.begin(), ::tolower); //converts to lowercase

    //if we can analyze that process assign it to inputProcess, if not send error message
    if (std::find(processesToAnalyze.begin(), processesToAnalyze.end(), process) != processesToAnalyze.end()){
        inputProcess = process;
    }
    else{
        QMessageBox::information(this, "Error", "We cannot analyze that process, please provide another one.", QMessageBox::Ok);
      }
}


void bioprocesswindow::on_MenuWindowButton_clicked()
{
    this->close();
    emit MenuWindow(); //returns to menuWindow
}

