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

void SecondWindow::on_ColocalizationButton_clicked()
{
    coWindow = new colocalizationwindow(this);

    this->hide();
    coWindow->show();
    coWindow->makeHeatMap(m);

}


void SecondWindow::on_BiologicalButton_clicked()
{
    bioWindow = new bioprocesswindow(this);
    /*bioWindow->setX(this->getX());
    bioWindow->setY(this->getY());
    bioWindow->setP(this->getP());*/

    this->hide();
    bioWindow->show();
    bioWindow->makeHeatMap();
    bioWindow->setProcessesToAnalyze();

}



