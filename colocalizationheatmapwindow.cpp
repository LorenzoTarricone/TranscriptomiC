#include "colocalizationheatmapwindow.h"
#include "QtWidgets/qcolormap.h"
#include "ui_colocalizationheatmapwindow.h"
#include "heatmapwindow.h"
#include "QFileDialog"
#include "qcustomplot.h"


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




//void colocalizationwindow::makeHeatMap(){

//    // configure axis rect:
//           ui->coloPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
//           ui->coloPlot->axisRect()->setupFullAxesBox(true);
//           ui->coloPlot->xAxis->setLabel("x");
//           ui->coloPlot->yAxis->setLabel("y");
//           // set up the QCPColorMap:
//           QCPColorMap *colorMap = new QCPColorMap(ui->coloPlot->xAxis, ui->coloPlot->yAxis);

//           // Use nx = ny = 7 for rec_Data: We need to find nx and ny for each individual file.
//           // It only works for quadratic matrices, we want to get the biggest x- and y-coordinate of the coordinate vectors
//           int nx = sqrt(getX().size());
//           std::cout << "nx: "<< nx;// check if nx is correct: delete this line later
//           int ny = sqrt(getX().size());
//           std::cout << "ny:"<< ny; // check if ny is correct: delte this line later

//           colorMap->data()->setSize(nx, ny);
//           colorMap->data()->setRange(QCPRange(0, nx-1), QCPRange(0, ny-1)); //set the range of the HeatMap;
//           //This is just for rec_Data: We need to find the Range for each individual file

//           // now we assign some data, by accessing the QCPColorMapData instance of the color map:
//           //HERE WE WOULD LIKE TO USE THE DATA FROM THE TEXTFILES

//           for(int Index = 0; Index< nx * ny; Index++){ // We have 49 data points for rec_Data file
//               colorMap->data()->setCell(getX()[Index], getY()[Index], getP()[Index]);
//           }
//           // add a color scale
//           QCPColorScale *colorScale = new QCPColorScale(ui->coloPlot);
//           ui->coloPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
//           colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
//           colorMap->setColorScale(colorScale); // associate the color map with the color scale
//           colorScale->axis()->setLabel("Third coordinate");

//           // set the color gradient of the color map to one of the presets:
//           colorMap->setGradient(QCPColorGradient::gpPolar);
//           // we could have also created a QCPColorGradient instance and added own colors to
//           // the gradient, see the documentation of QCPColorGradient for what's possible.

//           //Uncomment for ColourMap without interpolation
//           //colorMap->setInterpolate(false);

//           // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
//           colorMap->rescaleDataRange();

//           // rescale the key (x) and value (y) axes so the whole color map is visible:
//           ui->coloPlot->rescaleAxes();

//}


void ColocalizationHeatmapWindow::on_SaveMatrixButton_clicked(){

    //opens the file explorer and get file name (with full location)
    QString filename;
    filename = QFileDialog::getSaveFileName(this,"Save file");
    filename = filename + ".csv";
    std::string name;
    name = filename.toStdString();


     object->saveToFile(name);

//    MatrixXd m(5,5); //needs to be changed to the colocalization matrix
//    m(0,0) = 0.3; m(0,1) = 0.5; m(0,2) = -1; m(0,3) = 0.6; m(0,4) = 0;
//    m(1,0) =  1, m(1,1) = 0.7; m(1,2) = 0.2; m(1,3) = 0.4; m(1,4) = -0.7;
//    m(2,0) = -1; m(2,1) = 1; m(2,2) = 0.5; m(2,3) = 0.8; m(2,4) = -0.9;
//    m(3,0) = -1; m(3,1) = 1; m(3,2) = 0.5; m(3,3) = 0.8; m(3,4) = -0.9;
//    m(4,0) = -1; m(4,1) = 1; m(4,2) = 0.5; m(4,3) = 0.8; m(4,4) = -0.9;



//    // Using std library to create and writes the file
//    std::string stdfilemane;
//    stdfilemane = filename.toStdString();
//    ofstream fout;

//    //opens file, parses the data and writes it as a .csv
//    fout.open(stdfilemane, ios::out);
//    const static Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n");
//    fout <<m.format(CSVFormat);


//    QMessageBox::information(this, "Success (COMENTED OUT)", "The colocalization matrix has been saved under" + filename , QMessageBox::Ok);

}

void ColocalizationHeatmapWindow::makeHeatMap(const Eigen::MatrixXd m){

    // configure axis rect:
               ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
               ui->customPlot->axisRect()->setupFullAxesBox(true);
               ui->customPlot->xAxis->setLabel("x");
               ui->customPlot->yAxis->setLabel("y");
               // set up the QCPColorMap:
               QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);

               int number_rows = m.rows();
               int number_cols = m.cols();
               // data size
               int data_size = number_cols * number_rows;

               colorMap->data()->setSize(number_cols, number_rows);
               colorMap->data()->setRange(QCPRange(0, number_cols-1), QCPRange(0, number_rows-1)); //set the range of the HeatMap;

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
               for(int i= 0; i<number_cols; i++){
                   for (int j = 0; j<number_rows; j++){
                       mean += m(i,j);

                   }
               }
               mean /= data_size;

               //calculate standard deviation
               double sd = 0.0;
               for(int i= 0; i<number_cols; i++){
                   for (int j = 0; j<number_rows; j++){
                        sd += pow(m(i,j) - mean,2);
                   }
               }
               //standart error
               sd = sqrt(sd/(data_size));

               //margin of error
               double ci = 2* sd;

               double q1 = mean-ci;
               double q3 = mean+ci;
               //output
               std::cout << "95% Confidence Interval: [" << q1 << ", " << q3 << "]" << std::endl;




               // now we assign some data, by accessing the QCPColorMapData instance of the color map:

               for(int i = 0; i < number_cols; i++){
                   for(int j = 0; j< number_rows; j++){
                       if(m(i,j)>q1 && m(i,j)<q3){
                           colorMap->data()->setCell(i, j, m(i,j));} // plot only data between q1 and q3 here we want quantile
                       else{colorMap->data()->setCell(i, j, 0);}

                       }
                   }

              // Ticks and Labels
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

              /*//assign each label individually
              for(int i = 0; i < number_cols; i++){
                  textTickerx->addTick(i, "Bacteria");}; // Here we need the gene names

              for(int j = 0; j< number_rows; j++){
                  textTickery->addTick(j, "Bacteria");}; // Here we need the gene names */



              //set x-axis ticker
              ui->customPlot->xAxis->setTicker(textTickerx);
              ui->customPlot->xAxis->setTickLabelPadding(8); //Sets the distance between the axis base line
              ui->customPlot->xAxis->setTickLabelColor(QColorConstants::Red); //Sets the color of the tick labels.
              ui->customPlot->xAxis->setTickLabelRotation(-90.0); //Sets the rotation of the tick labels.

              //set y-axis ticker
              ui->customPlot->yAxis->setTicker(textTickery);
              ui->customPlot->yAxis->setTickLabelColor(QColorConstants::Red); //Sets the color of the tick labels.

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

