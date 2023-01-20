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
    ui->PercentParamText->setPlainText("5");
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

    QString Percent = ui->PercentParamText->toPlainText();
    PercentParameter = ui->PercentParamText->toPlainText().toDouble()*0.01;
    QString p = ui->pParamText->toPlainText();
    pParameter = ui->pParamText->toPlainText().toDouble();
    MParameter = ui->MParamText->toPlainText().toDouble();

    bool PercentChecker = false;
    qDebug() <<"this is p" << Percent;
    if(Percent.length() <=3){
        for(int i = 0; i <= 100; i++){
            if(Percent == QString::number(i)){
                PercentChecker = true;
                break;
            }
        }
    }


    bool pChecker = false;

    if(p.length() == 1){
        for(int i = 0; i <= 5; i++){
            if(p == QString::number(i)){
                pChecker = true;
                break;
            }
        }
    }


    if((PercentParameter<0 && PercentParameter>1 && PercentChecker) || (pParameter<0 && pParameter>5 && pChecker) || (MParameter<10 && MParameter>10000)){

        QString ErrorMesage = "Invalid Parameters.\n";
        if(PercentParameter<0 || pParameter >1 || PercentChecker){ErrorMesage.append("Invalid value for Percentage of Expression.");}else{ErrorMesage.append("Valid Percentage of Expression.");};
        if(pParameter<0 || pParameter >5 || pChecker){ErrorMesage.append("Invalid value for p parameter.\n");}else{ErrorMesage.append("Valid p parameter.\n");};
        if(MParameter<10 || MParameter >10000){ErrorMesage.append("Invalid value for M parameter.\n");}else{ErrorMesage.append("Valid M parameter.\n");};

        QMessageBox::information(this, "Error", ErrorMesage , QMessageBox::Ok); //error message
    }
    else{

        //setLinkageParameters(PercentParameter,pParameter, MParameter)
        heatmapWindow->setX(this->getX());
        heatmapWindow->setY(this->getY());
        heatmapWindow->setP(this->getP());

        this->hide(); //hides menuwindow
        heatmapWindow->show(); //shows biowindow
        heatmapWindow->makeHeatMap(); //generates the heatmap
    }



}

