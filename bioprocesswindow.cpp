#include "bioprocesswindow.h"
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

void bioprocesswindow::makeHeatMap(){

    // configure axis rect:
           ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
           ui->customPlot->axisRect()->setupFullAxesBox(true);
           ui->customPlot->xAxis->setLabel("x");
           ui->customPlot->yAxis->setLabel("y");
           // set up the QCPColorMap:
           QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);
           int nx = 6;
           int ny = 4;
           colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
           colorMap->data()->setRange(QCPRange(0, 6), QCPRange(0, 4)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions

           // now we assign some data, by accessing the QCPColorMapData instance of the color map:
           //HERE WE WOULD LIKE TO USE THE DATA FROM THE TEXTFILES


           for(int xIndex = 0; xIndex<=nx; xIndex++){
               //colorMap->data()->cellToCoord(getX()[xIndex],getY()[xIndex], &x, &y);
                    // random function for third coordinate
                    //z = sin(x) + sin(y);
               colorMap->data()->setCell(getX()[xIndex], getY()[xIndex], getP()[xIndex]);

           }

           // set the color gradient of the color map to one of the presets:
           colorMap->setGradient(QCPColorGradient::gpPolar);
           // we could have also created a QCPColorGradient instance and added own colors to
           // the gradient, see the documentation of QCPColorGradient for what's possible.
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
    //this function will jsut create a vector with all the processes we can analyze

    processesToAnalyze.push_back("hypoxia");

}


void bioprocesswindow::on_AnalyzeButton_clicked()
{
    QString bio;
    std::string process;

    bio = ui->plainTextEdit->toPlainText(); //gets the text the user wrote
    ui->plainTextEdit->setPlainText(""); //resets the text box to be empty

    process = bio.toStdString();

    std::transform(process.begin(), process.end(), process.begin(), ::tolower); //converts to lozercase

    //if we can analyze that process assign it to inputProcess, if not send error message
    if (std::find(processesToAnalyze.begin(), processesToAnalyze.end(), process) != processesToAnalyze.end()){
        inputProcess = process;
    }
    else{
        QMessageBox::information(this, "Error", "We cannot analyze that process, please provide another one.", QMessageBox::Ok);
      }
}

