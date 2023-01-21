#include "colocalizationwindow.h"
#include "colocalisation.h"
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

    uploadChecker=false;

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

    QString FileFilter = "TSV File (*.tsv);;";
    userText = QFileDialog::getOpenFileName(this, "Open a File", "C:\\Users\\", FileFilter);
    FileData geneNames;


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

    if(uploadChecker && (PercentParameter>0 && PercentParameter<=1 && PercentChecker) && (pParameter>=0 && pParameter<=5 && pChecker) && (MParameter>=10 && MParameter<=10000)){

        //setLinkageParameters(pParameter, MParameter)
        qDebug() << "Instantiating colocalisation object ... ";
        colocalisation* object = new colocalisation(files,200,200);
        qDebug() << "[Progress] Colocalisation object initialised ..." ;
        object->addGeneList(filename);
        qDebug() << "[Progress] Gene list added ..." ;

        double MParameter = 5000;
        double pParameter = 2;

        object->setM(MParameter);
        object->setP(pParameter);
        qDebug() << "[Progress] Parameter m and p set ...";
        double perc = 0.001;

        object->filter_simple(true,perc);
        object->filter_genes();
        // normalise data
        object->normalisation();
        // compute colocalisation matrix
        object->compute();

        qDebug() << "[Progress] Matrix computation done ..." ;

        QMessageBox::information(this, "Success", "File has been uploaded and \n Parameters have been inputed.", QMessageBox::Ok); //sucess message

        this->hide(); //hides menuwindow
        qDebug() << "[Progress] Setting colocalisation object ..." ;
        heatmapWindow->setColocalisationObject(object);
        qDebug() << "[Progress] Setting colocalisation object done." ;
        heatmapWindow->show(); //shows biowindow
        heatmapWindow->makeHeatMap(object->getColocalisationMatrix()); //generates the heatmap


    }
    else{

        QString ErrorMesage = "Invalid Parameters.\n";
        if(uploadChecker){ErrorMesage.append("File has been uploaded correctly. \n");}else{ErrorMesage.append("Please upload a file. \n");};
        if(PercentParameter>0 && PercentParameter<=1 && PercentChecker){ErrorMesage.append("Valid Percentage of Expression. \n");}else{ErrorMesage.append("Invalid value for Percentage of Expression. \n");};
        if(pParameter>=0 && pParameter<=5 && pChecker){ErrorMesage.append("Valid p parameter.\n");}else{ErrorMesage.append("Invalid value for p parameter.\n");};
        if(MParameter>=10 && MParameter<=10000){ErrorMesage.append("Valid M parameter.\n");}else{ErrorMesage.append("Invalid value for M parameter.");};

        QMessageBox::information(this, "Error", ErrorMesage , QMessageBox::Ok); //error message

    }



}

