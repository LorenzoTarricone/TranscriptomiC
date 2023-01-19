#include "colocalizationwindow.h"
#include "ui_colocalizationwindow.h"
#include "filedata.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

//#include <Eigen/Dense>

using namespace std;
//using namespace Eigen;



colocalizationwindow::colocalizationwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::colocalizationwindow)
{
    ui->setupUi(this);

    ui->pParamText->setPlainText("2");
    ui->MParamText->setPlainText("5000");

}

colocalizationwindow::~colocalizationwindow()
{
    delete ui;
}


void colocalizationwindow::on_MenuWindowButton_clicked()
{
    this->close();
    emit MenuWindow(); //returns to menuWindow
}


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




void colocalizationwindow::on_GenerateHeatmapButton_clicked()
{

    heatmapWindow = new ColocalizationHeatmapWindow(this);
    connect(heatmapWindow, &ColocalizationHeatmapWindow::PreviousWindow, this, &HeatMapWindow::show); //connects menuwindow and colocalizationwindow so that we can navigate between them

    QString p = ui->pParamText->toPlainText();
    pParameter = ui->pParamText->toPlainText().toDouble();
    MParameter = ui->MParamText->toPlainText().toDouble();

    bool checker = true;

    if(p.length() == 1){
        for(int i = 0; i <= 5; i++){
            if(p == QString::number(i)){
                checker = false;
                break;
            }
        }
    }


    if( (MParameter<10 || MParameter >10000) && (pParameter<0 || pParameter >5)){
        QMessageBox::information(this, "Error", "Invalid value for p and M parameters", QMessageBox::Ok);

    }
    else if(MParameter<10 || MParameter >10000){
        QMessageBox::information(this, "Error", "Invalid value for M parameter", QMessageBox::Ok);

    }
    else if(pParameter<0 || pParameter >5 || checker){
        QMessageBox::information(this, "Error", "Invalid value for p parameter", QMessageBox::Ok);

    }
    else{

        //setLinkageParameters(pParameter, MParameter)
        heatmapWindow->setX(this->getX());
        heatmapWindow->setY(this->getY());
        heatmapWindow->setP(this->getP());

        this->hide(); //hides menuwindow
        heatmapWindow->show(); //shows biowindow
        heatmapWindow->makeHeatMap(); //generates the heatmap
    }



}

