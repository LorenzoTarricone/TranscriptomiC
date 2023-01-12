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


void MenuWindow::on_ColocalizationButton_clicked()
{

    /* This function creates an instance of colocalizationwindow and shows it when the button is pressed.
     * It also sets all of the data in the object of colocalizationwindow to be the data from the file and
     * calls makeHeatMap() to generate the heatmap.
     */

    coWindow = new colocalizationwindow(this); //creates the instance of colocalizationWindow
    connect(coWindow, &colocalizationwindow::MenuWindow, this, &MenuWindow::show); //connects menuwindow and colocalizationwindow so that we can navigate between them

    this->hide(); //hides menuwindow
    coWindow->show(); //shows colocalizationwindow
    coWindow->makeHeatMap(m); //makes the heatmap

}


void MenuWindow::on_BiologicalButton_clicked()
{

    /* This function creates an instance of bioprocesswindow and shows it when the button is pressed.
     * It also sets all of the data in the object of bioprocesswindow to be the data from the file and
     * calls makeHeatMap() to generate the heatmap. It also calls setProcessToAnalyze(), but that will
     * be deleted later on.
     */

    bioWindow = new bioprocesswindow(this); //creates the instance of colocalizationWindow
    connect(bioWindow, &bioprocesswindow::MenuWindow, this, &MenuWindow::show); //connects menuwindow and colocalizationwindow so that we can navigate between them

    this->hide(); //hides menuwindow
    bioWindow->show(); //shows biowindow
    bioWindow->makeHeatMap(m); //generates the heatmap
    bioWindow->setProcessesToAnalyze(); //instantiates the vector of processes

}


void MenuWindow::on_MenuWindowButton_clicked()
{
    this->close();
    emit UploadWindow(); //returns to uploadwindow
}

