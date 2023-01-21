#include "MenuWindow.h"
#include "biologicalprocess.h"
#include "colocalisation.h"
#include "ui_MenuWindow.h"
#include "qcustomplot.cpp"
#include <iostream>
#include <QMessageBox>


MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::makePlot() {

//    //This fucntion makes the scatterplot

//    ui->customPlot->addGraph();
//    ui->customPlot->graph(0)->setData(this->getX(),this->getY());
//    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone); //lsNone = no line
//    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssStar); //ssStar = star points

//    ui->customPlot->xAxis->setLabel("x"); //axis labels
//    ui->customPlot->yAxis->setLabel("y");

//    ui->customPlot->xAxis->setRange(0,10); //axis ranges
//    ui->customPlot->yAxis->setRange(0,10);

//    ui->customPlot->replot();
}

void MenuWindow::on_ColocalizationButton_clicked()
{

    /* This function creates an instance of colocalizationwindow and shows it when the button is pressed.
     * It also sets all of the data in the object of colocalizationwindow to be the data from the file and
     * calls makeHeatMap() to generate the heatmap.
     */


    coWindow = new colocalizationwindow(this); //creates the instance of colocalizationWindow
    connect(coWindow, &colocalizationwindow::MenuWindow, this, &MenuWindow::show); //connects menuwindow and colocalizationwindow so that we can navigate between them

    coWindow->setFileObject(files);
//    //sets the data
//    coWindow->setX(this->getX());
//    coWindow->setY(this->getY());
//    coWindow->setP(this->getP());

    this->hide(); //hides menuwindow
    coWindow->show(); //shows colocalizationwindow
    //coWindow->makeHeatMap(); //makes the heatmap

}


void MenuWindow::on_BiologicalButton_clicked()
{

    /* This function creates an instance of bioprocesswindow and shows it when the button is pressed.
     * It also sets all of the data in the object of bioprocesswindow to be the data from the file and
     * calls makeHeatMap() to generate the heatmap. It also calls setProcessToAnalyze(), but that will
     * be deleted later on.
     */

    biochooseWindow = new BioChooser(this); //creates the instance of colocalizationWindow
    connect(BioChooser, &BioChooser::MenuWindow, this, &MenuWindow::show); //connects menuwindow and colocalizationwindow so that we can navigate between them

    biochooseWindow->setFileObject(files);
//    //sets the data
//    bioWindow->setX(this->getX());
//    bioWindow->setY(this->getY());
//    bioWindow->setP(this->getP());

    this->hide(); //hides menuwindow
    biochooseWindow->show(); //shows biowindow
    //bioWindow->makeHeatMap(); //generates the heatmap

}


void MenuWindow::on_UploadWindowButton_clicked()
{
    this->close();
    emit UploadWindow(); //returns to uploadwindow
}


//const QVector<double>& MenuWindow::getX() {
//    std::vector<double> stdVec = plot.getExprX();
//    x = QVector<double>(stdVec.begin(), stdVec.end());
//    return x;
//}


//const QVector<double>& MenuWindow::getY() {
//    std::vector<double> stdVec = plot.getExprY();
//    y = QVector<double>(stdVec.begin(), stdVec.end());
//    return y;
//}
//const QVector<double>& MenuWindow::getP() {
//    std::vector<double> stdVec = plot.getExprVal();
//    p = QVector<double>(stdVec.begin(), stdVec.end());
//    return p;
//}

