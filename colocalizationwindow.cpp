#include "colocalizationwindow.h"
#include "ui_colocalizationwindow.h"
#include "filedata.h"
#include <iostream>
#include <fstream>
#include <sstream>



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

void colocalizationwindow::makeHeatMap(const MatrixXd m){

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



               //95 PERCENT CONFIDENCE LEVEL
               //get data size
               int data_size = number_cols * number_rows;

               //calculate mean
               double mean = 0.0;
               for(int i= 0; i<number_cols; i++){
                   for (int j = 0; j<number_rows; j++){
                       mean += m(i,j);
                   }
               }

               mean /= number_cols*number_rows;

               //calculate standard deviation
               double sd = 0.0;
               for(int i= 0; i<number_cols; i++){
                   for (int j = 0; j<number_rows; j++){
                        sd += pow(m(i,j) - mean,2);
                   }
               }


               //standart error
               sd = sqrt(sd/(data_size));

               //calculate 95% confidence interval
               //double  n = sqrt(data_size);
               //double ci = 1.96 * (sd/n); // maybe 2

               //margin of error
               double ci = 2* sd;

               double q1 = mean-ci;
               double q3 = mean+ci;
               //output
               cout << "95% Confidence Interval: [" << mean - ci << ", " << mean + ci << "]" << endl;




               // now we assign some data, by accessing the QCPColorMapData instance of the color map:

               for(int i = 0; i < number_cols; i++){
                   for(int j = 0; j< number_rows; j++){
                       if(m(i,j)>q1 && m(i,j)<q3){
                           colorMap->data()->setCell(i, j, m(i,j));} // plot only data between q1 and q3 here we want quantile
                       else{colorMap->data()->setCell(i, j, 0);}

                       }
                   }

              // Ticks
              QSharedPointer<QCPAxisTickerText> textTickerx(new QCPAxisTickerText);

              // tick strategy. readability is more important
              textTickerx->setTickStepStrategy(QCPAxisTicker::tssReadability);
              textTickerx->setTickCount(3);

              QSharedPointer<QCPAxisTickerText> textTickery(new QCPAxisTickerText);

              // tick strategy. readability is more important
              textTickery->setTickStepStrategy(QCPAxisTicker::tssReadability);
              textTickery->setTickOrigin(0);// sets origin (not necessary)
              textTickery->setTickCount(4);

              //assing the labels
              //textTickerx->setTicks(const QVector<double> &positions, const QVector<QString> &labels);
              //textTickery->setTicks(const QVector<double> &positions, const QVector<QString> &labels);
              for(int i = 0; i < number_cols; i++){
                  textTickerx->addTick(i, "Bacteria");};

              for(int j = 0; j< number_rows; j++){
                  textTickery->addTick(j, "Bacteria");};



              //set x-axis ticker
              ui->customPlot->xAxis->setTicker(textTickerx);

              //set y-axis ticker
              ui->customPlot->yAxis->setTicker(textTickery);

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

    MatrixXd m(5,5); //needs to be changed to the colocalization matrix
       m(0,0) = 0.3; m(0,1) = 0.5; m(0,2) = -1; m(0,3) = 0.6; m(0,4) = 0;
       m(1,0) =  1, m(1,1) = 0.7; m(1,2) = 0.2; m(1,3) = 0.4; m(1,4) = -0.7;
       m(2,0) = -1; m(2,1) = 1; m(2,2) = 0.5; m(2,3) = 0.8; m(2,4) = -0.9;
       m(3,0) = -1; m(3,1) = 1; m(3,2) = 0.5; m(3,3) = 0.8; m(3,4) = -0.9;
       m(4,0) = -1; m(4,1) = 1; m(4,2) = 0.5; m(4,3) = 0.8; m(4,4) = -0.9;

    //opens the file explorer and get file name (with full location)
    QString filename;
    filename = QFileDialog::getSaveFileName(this,"Save file");
    filename = filename + ".csv";

    // Using std library to create and writes the file
    std::string stdfilemane;
    stdfilemane = filename.toStdString();
    ofstream fout;

    //opens file, parses the data and writes it as a .csv
    fout.open(stdfilemane, ios::out);
    const static Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n");
    fout <<m.format(CSVFormat);

    QMessageBox::information(this, "Success", "The colocalization matrix has been saved under" + filename , QMessageBox::Ok);

};


void colocalizationwindow::on_UploadGenesButton_clicked()
{
    /* This method allows the user to upload a csv file with
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
    uploadChecker = geneNames.readGenes(filename); //checks for successful upload and reads the genes

    if(uploadChecker){
        QMessageBox::information(this, "Success", "File has been uploaded.", QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this, "Error", "Could not find file, please specify the entire file location.", QMessageBox::Ok);
    }
}


void colocalizationwindow::on_MenuWindowButton_clicked()
{
    this->close();
    emit MenuWindow(); //returns to menuWindow
}



