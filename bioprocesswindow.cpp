#include "bioprocesswindow.h"
#include "colocalizationwindow.h"
#include "qcustomplot.h"
#include "ui_bioprocesswindow.h"
#include "qdebug.h"
#include <algorithm>

bioprocesswindow::bioprocesswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bioprocesswindow)
{
    ui->setupUi(this);
    ui->ChosenProcessText->setPlainText("Write here the chosen Process");

}

bioprocesswindow::~bioprocesswindow()
{
    delete ui;
}

/*void bioprocesswindow::makeHeatMap(){

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

           for(int Index = 0; Index < nx * ny; Index++){ // We have 49 data points
                          colorMap->data()->setCell(getX()[Index], getY()[Index], getP()[Index]);
                      }

           //Color scale:
           QCPColorScale *colorScale = new QCPColorScale(ui->customPlot);
           ui->customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis
           colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right
           colorScale->setRangeDrag(&free); // drag the data range. we dont need that
           colorMap->setColorScale(colorScale); // associate the color map with the color scale
           colorScale->axis()->setLabel("Intensity");

           //Color gradient:
           QCPColorGradient gradient; // empty gradient with no defined colour stops
           //Hue variation similar to a spectrum, often used in numerical visualization (creates banding illusion but allows more precise magnitude estimates)
           gradient.setColorStopAt(0, QColor(0,0,0));//Sets the color the gradient will have at the specified position (from 0 to 1).
           gradient.setColorStopAt(1, QColor(255,0,0));//In between these color stops, the color is interpolated according to setColorInterpolation.
           gradient.setColorInterpolation(QCPColorGradient::ciRGB);//interpolated linearly in RGB color space.
           gradient.setNanHandling(QCPColorGradient::nhLowestColor); //NaN data points as the lowest color.
           gradient.setLevelCount(350); //sets the number of discretization levels of the color gradient to n (max. n = 350)
           colorMap->setGradient(gradient);//assign it to the heatmap

           colorMap->setGradient(QCPColorGradient::gpJet);

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

}*/

void bioprocesswindow::setProcessesToAnalyze(){
    //this function will just create a vector with all the processes we can analyze
    //TEMPORARY, in the end we will have something a lot more sophisticated

    processesToAnalyze.push_back("hypoxia");

}


void bioprocesswindow::on_AnalyzeButton_clicked()
{
    QString bio;
    std::string process;

    bio = ui->ChosenProcessText->toPlainText(); //gets the text the user wrote
    ui->ChosenProcessText->setPlainText(""); //resets the text box to be empty

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



void bioprocesswindow::openHeatMapWindow(){
    heatmapWindow = new HeatMapWindow(this);
    connect(heatmapWindow, &HeatMapWindow::PreviousWindow, this, &HeatMapWindow::show); //connects menuwindow and colocalizationwindow so that we can navigate between them


    heatmapWindow->setX(this->getX());
    heatmapWindow->setY(this->getY());
    heatmapWindow->setP(this->getP());

    this->hide(); //hides menuwindow
    heatmapWindow->show(); //shows biowindow
    heatmapWindow->makeHeatMap(); //generates the heatmap
}



