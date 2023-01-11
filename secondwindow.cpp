#include "SecondWindow.h"
#include "ui_SecondWindow.h"
#include "qcustomplot.cpp"
#include <iostream>
#include <QMessageBox>


SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);

}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::makePlot() {

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(this->getX(),this->getY());
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone); //lsNone = no line
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssStar); //ssStar = star points

    ui->customPlot->xAxis->setLabel("x"); //axis labels
    ui->customPlot->yAxis->setLabel("y");

    ui->customPlot->xAxis->setRange(0,10); //axis ranges
    ui->customPlot->yAxis->setRange(0,10);

    ui->customPlot->replot();
}

void SecondWindow::on_ColocalizationButton_clicked()
{
    coWindow = new colocalizationwindow(this);

    this->hide();
    coWindow->show();
    coWindow->makeHeatMap(MatrixXd m);

}


void SecondWindow::on_BiologicalButton_clicked()
{
    bioWindow = new bioprocesswindow(this);
    bioWindow->setX(this->getX());
    bioWindow->setY(this->getY());
    bioWindow->setP(this->getP());

    this->hide();
    bioWindow->show();
    bioWindow->makeHeatMap();
    bioWindow->setProcessesToAnalyze();

}



