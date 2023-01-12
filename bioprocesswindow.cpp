#include "bioprocesswindow.h"
#include "colocalizationwindow.h"
#include "qcustomplot.h"
#include "ui_bioprocesswindow.h"
#include "qdebug.h"

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

void bioprocesswindow::makeHeatMap(MatrixXd m){

    // configure axis rect:
           ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
           ui->customPlot->axisRect()->setupFullAxesBox(true);
           ui->customPlot->xAxis->setLabel("x");
           ui->customPlot->yAxis->setLabel("y");
           // set up the QCPColorMap:
           QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);
           // This is just for rec_Data but we need to find nx and ny for each individual file
           int number_rows = m.rows();
           int number_cols = m.cols();

           colorMap->data()->setSize(number_cols, number_rows);
           colorMap->data()->setRange(QCPRange(0, number_cols-1), QCPRange(0, number_rows-1)); //set the range of the HeatMap;
           //This is just for rec_Data: We need to find the Range for each individual file

           // now we assign some data, by accessing the QCPColorMapData instance of the color map:
           //HERE WE WOULD LIKE TO USE THE DATA FROM THE TEXTFILES


           for(int i = 0; i < number_cols; i++){
               for(int j = 0; j< number_rows; j++){
                  colorMap->data()->setCell(i, j, m(i,j));
               }
           }


           // add a color scale:
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

