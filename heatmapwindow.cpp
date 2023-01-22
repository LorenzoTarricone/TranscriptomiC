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

    // allow rescaling the color scale by dragging/zooming
    ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    // configure axis rect
    ui->customPlot->axisRect()->setupFullAxesBox(true);
    // set the axis labels
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    // set up the QCPColorMap
    QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);

    // get matrix dimensions
    int number_rows = m.rows();
    int number_cols = m.cols(); // should be 3
    // set data size
    int data_size = number_rows; // just the third column

    // find max, min value
    double maxValx = m.col(0).maxCoeff(); // biggest x- value
    double minValx = m.col(0).minCoeff(); // smalles x- value
    double maxValy = m.col(1).maxCoeff(); // biggest y- value
    double minValy = m.col(1).minCoeff(); // smallest y- value

    // print out the values (test)
    std::cout << "Datasize :"<< data_size << std::endl;
    std::cout << "NumberCols :"<< number_cols << std::endl;
    std::cout << "NumberRows :"<< number_rows << std::endl;

    std::cout << "maxValx :"<< maxValx << std::endl;
    std::cout << "minValx :"<< minValx << std::endl;
    std::cout << "maxValy :"<< maxValy << std::endl;
    std::cout << "minValy :"<< minValy << std::endl;

    // set the size of the data
    colorMap->data()->setSize(data_size,data_size);

    // set range of color map using max and min values
    colorMap->data()->setRange(QCPRange(minValx, maxValx), QCPRange(minValy, maxValy)); //set the range of the HeatMap;



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

    //print confidence interval
    std::cout << "95% Confidence Interval: [" << q1 << ", " << q3 << "]" << std::endl;


    // assign some data, by accessing the QCPColorMapData instance of the color map
    for(int i = 0; i < number_rows; i++){
        if(m(i,2)>q1 && m(i,2)<q3){
            colorMap->data()->setData(m(i,0),m(i,1),m(i,2));
        }
    }

    // assign data with cell and with confidence level
    /*for(int i = 0; i < number_rows; i++){
           i f(m(i,2)>q1 && m(i,2)<q3){ // if the third value of the row is in the confidence interval
                colorMap->data()->setCell(int(m(i,0)),int(m(i,1)), m(i,2)); // plot only data between q1 and q3 here we want quantile
                  }
            else{colorMap->data()->setCell(m(i,0),m(i,1), m(i,2));} //assign 0
    }*/



   /* Ticks and Labels: The following code is just an example hot it works
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


   // color scale
   // create color scale
   QCPColorScale *colorScale = new QCPColorScale(ui->customPlot);
   // add it to the right of the main axis rect
   ui->customPlot->plotLayout()->addElement(0, 1, colorScale);
   // scale shall be vertical bar with tick/axis labels right
   colorScale->setType(QCPAxis::atRight);
   // set width of scale
   colorScale->setBarWidth(8);
   // allos to drag the data range
   colorScale->setRangeDrag(&free);
   // associate the color map with the color scale
   colorMap->setColorScale(colorScale);
   // set label of color scale
   colorScale->axis()->setLabel("Intensity");



   // color gradient
   // empty gradient with no defined colour stops
   QCPColorGradient gradient;
   //Hue variation similar to a spectrum, often used in numerical visualization (creates banding illusion but allows more precise magnitude estimates)
   //In between these color stops, the color is interpolated according to setColorInterpolation.
   gradient.setColorInterpolation(QCPColorGradient::ciRGB);
   gradient.setColorStopAt(0, QColor(0, 0, 100));
   gradient.setColorStopAt(0.15, QColor(0, 50, 255));
   gradient.setColorStopAt(0.35, QColor(0, 255, 255));
   gradient.setColorStopAt(0.65, QColor(255, 255, 0));
   gradient.setColorStopAt(0.85, QColor(255, 30, 0));
   gradient.setColorStopAt(1, QColor(100, 0, 0));
   // NaN data points as the transparent
   gradient.setNanHandling(QCPColorGradient::nhTransparent);
   // set the number of discretization levels of the color gradient to n (max. n = 350)
   gradient.setLevelCount(350);
   //assign it to the heatmap
   colorMap->setGradient(gradient);


   // set interpolation: True or False
   colorMap->setInterpolate(false);

   // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up)
   QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->customPlot);
   ui->customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
   colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

   // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient
   colorMap->rescaleDataRange();

   // rescale the key (x) and value (y) axes so the whole color map is visible
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

