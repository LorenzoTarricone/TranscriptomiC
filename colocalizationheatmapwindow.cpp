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

//Might be usefull
//#include "colocalizationwindow.h"
//    double colocalizationwindow::pParameter;
//    double colocalizationwindow::MParameter;


/*

void colocalizationwindow::makeHeatMap(){

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


void colocalizationwindow::on_SaveMatrixButton_clicked(){

    //opens the file explorer and get file name (with full location)
    QString filename;
    filename = QFileDialog::getSaveFileName(this,"Save file");
    filename = filename + ".csv";


    MatrixXd m(5,5); //needs to be changed to the colocalization matrix
    m(0,0) = 0.3; m(0,1) = 0.5; m(0,2) = -1; m(0,3) = 0.6; m(0,4) = 0;
    m(1,0) =  1, m(1,1) = 0.7; m(1,2) = 0.2; m(1,3) = 0.4; m(1,4) = -0.7;
    m(2,0) = -1; m(2,1) = 1; m(2,2) = 0.5; m(2,3) = 0.8; m(2,4) = -0.9;
    m(3,0) = -1; m(3,1) = 1; m(3,2) = 0.5; m(3,3) = 0.8; m(3,4) = -0.9;
    m(4,0) = -1; m(4,1) = 1; m(4,2) = 0.5; m(4,3) = 0.8; m(4,4) = -0.9;



    // Using std library to create and writes the file
    std::string stdfilemane;
    stdfilemane = filename.toStdString();
    ofstream fout;

    //opens file, parses the data and writes it as a .csv
    fout.open(stdfilemane, ios::out);
    const static Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n");
    fout <<m.format(CSVFormat);


    QMessageBox::information(this, "Success (COMENTED OUT)", "The colocalization matrix has been saved under" + filename , QMessageBox::Ok);

};


 */
