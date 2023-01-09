#include "MenuWindow.h"
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

void MenuWindow::on_ColocalizationButton_clicked()
{

    coWindow = new colocalizationwindow(this);
    connect(coWindow, &colocalizationwindow::MenuWindow, this, &MenuWindow::show);


    coWindow->setX(this->getX());
    coWindow->setY(this->getY());
    coWindow->setP(this->getP());

    this->hide();
    coWindow->show();
    coWindow->makeHeatMap();

}


void MenuWindow::on_BiologicalButton_clicked()
{

    bioWindow = new bioprocesswindow(this);
    connect(bioWindow, &bioprocesswindow::MenuWindow, this, &MenuWindow::show);

    bioWindow->setX(this->getX());
    bioWindow->setY(this->getY());
    bioWindow->setP(this->getP());

    this->hide();
    bioWindow->show();
    bioWindow->makeHeatMap();
    bioWindow->setProcessesToAnalyze();

}


void MenuWindow::on_MenuWindowButton_clicked()
{
    this->close();
    emit UploadWindow();
}

