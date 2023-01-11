#include "colocalizationwindow.h"
#include "ui_colocalizationwindow.h"
#include "filedata.h"
#include <iostream>



colocalizationwindow::colocalizationwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::colocalizationwindow)
{
    ui->setupUi(this);
}

colocalizationwindow::~colocalizationwindow()
{
    delete ui;
}

void colocalizationwindow::makeHeatMap(MatrixXd m){

    // configure axis rect:
           ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
           ui->customPlot->axisRect()->setupFullAxesBox(true);
           ui->customPlot->xAxis->setLabel("x");
           ui->customPlot->yAxis->setLabel("y");
           // set up the QCPColorMap:
           QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);

           int number_rows = m.rows();
           int number_cols = m.cols();

           QVector<double> xCoordinates;
           QVector<double> yCoordinates;
           QVector<double> pValues;

           for(int i = 0; i < number_rows; i++){
               for(int j = 0; j< number_cols; j++){
                   xCoordinates.push_back(i);
                   yCoordinates.push_back(j);
                   pValues.push_back(m(i,j));
               }
           }

           // Use nx = ny = 7 for rec_Data: We need to find nx and ny for each individual file.
           // It only works for quadratic matrices, we want to get the biggest x- and y-coordinate of the coordinate vectors
           int nx = sqrt(xCoordinates.size());
           std::cout << "nx: "<< nx;// check if nx is correct: delete this line later
           int ny = sqrt(yCoordinates.size());
           std::cout << "ny:"<< ny; // check if ny is correct: delte this line later

           colorMap->data()->setSize(nx, ny);
           colorMap->data()->setRange(QCPRange(0, nx-1), QCPRange(0, ny-1)); //set the range of the HeatMap;
           //This is just for rec_Data: We need to find the Range for each individual file

           // now we assign some data, by accessing the QCPColorMapData instance of the color map:
           //HERE WE WOULD LIKE TO USE THE DATA FROM THE TEXTFILES

           for(int Index = 0; Index< nx * ny; Index++){ // We have 49 data points for rec_Data file
               colorMap->data()->setCell(xCoordinates[Index], yCoordinates[Index], pValues[Index]);
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
           colorMap->setInterpolate(false);

           // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
           colorMap->rescaleDataRange();

           // rescale the key (x) and value (y) axes so the whole color map is visible:
           ui->customPlot->rescaleAxes();


}


void colocalizationwindow::on_SaveHeatmapButton_clicked()
{
    QPixmap heatmap;
    QString filename;

    //grabs the heatmap widget as a QPixmap
    heatmap = ui->customPlot->grab();

    //opens the file explorer and get file name (with full location)
    filename = QFileDialog::getSaveFileName(this,"Save file");


    heatmap.save(filename + ".png"); //saves as .png

}


void colocalizationwindow::on_UploadGenesButton_clicked()
{
    /* This method allows the user to uplaod a csv file with
     * the names of the genes that they want to analyze. It
     * opens the file explorer, then reads the file into
     * a new instance of FileData. Data is stored in
     * genesToAnalyze vector of the instance of FileData.
     * (can be accessed with getter)
     */

    QString FileFilter = "CSV File (*.csv);;";
    QString userText = QFileDialog::getOpenFileName(this, "Open a File", "C:\\Users\\", FileFilter);
    std::string filename;
    FileData geneNames;
    bool uploadChecker;

    filename = userText.toStdString();
    uploadChecker = geneNames.readGenes(filename); //checks for successful upload

    if(uploadChecker){
        QMessageBox::information(this, "Success", "File has been uploaded.", QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this, "Error", "Could not find file, please specify the entire file location.", QMessageBox::Ok);

    }
}

