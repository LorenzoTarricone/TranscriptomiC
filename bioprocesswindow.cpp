#include "bioprocesswindow.h"
#include "colocalizationwindow.h"
#include "qcustomplot.h"
#include "ui_bioprocesswindow.h"
#include "qdebug.h"



bioprocesswindow::bioprocesswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bioprocesswindow)
{
    ui->setupUi(this);

}

bioprocesswindow::~bioprocesswindow()
{
    delete ui;
}


void bioprocesswindow::on_MenuWindowButton_clicked()
{
    this->close();
    emit MenuWindow(); //returns to menuWindow
}



void bioprocesswindow::setProcessesToAnalyze(){
    //this function will just create a vector with all the processes we can analyze
    //TEMPORARY, in the end we will have something a lot more sophisticated

    processesToAnalyze.push_back("hypoxia");

}

void bioprocesswindow::openHeatMapWindow(){
    heatmapWindow = new HeatMapWindow(this);
    connect(heatmapWindow, &HeatMapWindow::PreviousWindow, this, &HeatMapWindow::show); //connects menuwindow and colocalizationwindow so that we can navigate between them


    heatmapWindow->setX(this->getX());
    heatmapWindow->setY(this->getY());
    heatmapWindow->setP(this->getP());

    this->hide(); //hides menuwindow
    heatmapWindow->show(); //shows biowindow
    heatmapWindow->makeHeatMap(); //generates the heatmap
}

void bioprocesswindow::on_AnalyzeButton_clicked()
{
    QString bio;
    std::string process;

    bio = ui->plainTextEdit->toPlainText(); //gets the text the user wrote
    ui->plainTextEdit->setPlainText(""); //resets the text box to be empty

    process = bio.toStdString();

    std::transform(process.begin(), process.end(), process.begin(), ::tolower); //converts to lowercase

    //if we can analyze that process assign it to inputProcess, if not send error message
    if (std::find(processesToAnalyze.begin(), processesToAnalyze.end(), process) != processesToAnalyze.end()){
        inputProcess = process;
        openHeatMapWindow();
    }
    else{
        QMessageBox::information(this, "Error", "We cannot analyze that process, please provide another one.", QMessageBox::Ok);
      }

}


