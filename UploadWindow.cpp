#include "UploadWindow.h"
#include "parsefile.h"
#include "ui_UploadWindow.h"
#include <fstream>
#include <QMessageBox>
#include <iostream>
#include <QDialog>
#include <QFileDialog>


UploadWindow::UploadWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UploadWindow)
{
    ui->setupUi(this);

    ui->GeneFileText->setPlainText("Please select a TSV File (*.tsv).");
    ui->SpatialFileText->setPlainText("Please select a CSV File (*.csv).");
    ui->ExpressFileText->setPlainText("Please select a MTX File (*.mtx).");

    PointerMenuWindow = new MenuWindow(this);
    connect(PointerMenuWindow, &MenuWindow::UploadWindow, this, &UploadWindow::show);

}

UploadWindow::~UploadWindow()
{
    delete ui;
    delete PointerMenuWindow;
}

void UploadWindow::close(){

    /*This function closes the upload window and sets the data for the menuwindow. It also calls makePlot()
     * to generate the scatterplot and shows the menuwindow.
     */

    //sets the data
    PointerMenuWindow->setX(ExpressData.getX());
    PointerMenuWindow->setY(ExpressData.getY());
    PointerMenuWindow->setP(ExpressData.getP());

    PointerMenuWindow->setFileObject(this->files);

//    PointerMenuWindow->makePlot(); //generates the plot
    PointerMenuWindow->show(); //shows menuwindow

    this->hide(); //hides uploadwindow
}

void UploadWindow::on_GeneSelectButton_clicked()
{
    /*This function opens the file explorer and allows the user to choose a file. Once that file is
     * chosen, it sets the path as the text in the text edit.
     */

    QString GFileFilter = "TSV File (*.tsv);;";//"TSV File (*.tsv);;"; //creates a file filter so that only the relevant formats can be chosen
    QString GeneUserText = QFileDialog::getOpenFileName(this, "Open a File", "C:\\Users\\", GFileFilter); //opens the file explorer with the filter
    ui->GeneFileText->setPlainText(GeneUserText); //sets the test in the text edit to be the flie location

}

void UploadWindow::on_SpatialSelectButton_clicked(){

    QString SFileFilter = "CSV File (*.csv);;"; //creates a file filter so that only the relevant formats can be chosen MTX File (*.mtx)
    QString SpatialUserText = QFileDialog::getOpenFileName(this, "Open a File", "C:\\Users\\", SFileFilter); //opens the file explorer with the filter
    ui->SpatialFileText->setPlainText(SpatialUserText); //sets the test in the text edit to be the flie location

};


void UploadWindow::on_ExpressSelectButton_clicked(){

    QString EFileFilter = "MTX File (*.mtx);;";//"MTX File (*.mtx);;"; //creates a file filter so that only the relevant formats can be chosen
    QString ExpressUserText = QFileDialog::getOpenFileName(this, "Open a File", "C:\\Users\\", EFileFilter); //opens the file explorer with the filter
    ui->ExpressFileText->setPlainText(ExpressUserText); //sets the test in the text edit to be the flie location

};


void UploadWindow::on_UploadButton_clicked()
{
    /*This file uploads the data. It reads it and parses it, if everything is fine, then it opens the menu
     * window and closes the upload window.
     */

    files = parsefile();

    FileData Genedata;
    FileData Spatialdata;

    GeneUserText = ui->GeneFileText->toPlainText(); //takes the file location
    GeneFilename = GeneUserText.toStdString(); //converts the file location to std::string
    GeneBoolean = Genedata.readData(GeneFilename); //reads and parses the data, returns a boolean to check for sucessful upload

    SpatialUserText = ui->SpatialFileText->toPlainText(); //takes the file location
    SpatialFilename = SpatialUserText.toStdString(); //converts the file location to std::string
    SpatialBoolean = Spatialdata.readData(SpatialFilename); //reads and parses the data, returns a boolean to check for sucessful upload

    ExpressUserText = ui->ExpressFileText->toPlainText(); //takes the file location
    ExpressFilename = ExpressUserText.toStdString(); //converts the file location to std::string
    ExpressBoolean = ExpressData.readData(ExpressFilename); //reads and parses the data, returns a boolean to check for sucessful upload

    int fileRead = files.readFiles(ExpressFilename, SpatialFilename, GeneFilename);

    if(fileRead == 0){
        QMessageBox::information(this, "Success", "File has been uploaded.", QMessageBox::Ok); //sucess message
        close(); //closes this window and opens the menu

    }else{

        QString ErrorMesage = "Could not find all of the files.\n";
        if(fileRead != 3){ErrorMesage.append("Gene File is allowed,\n");}else{ErrorMesage.append("Select Gene File again,\n");};
        if(fileRead != 1){ErrorMesage.append("Spatial File is allowed,\n");}else{ErrorMesage.append("Select Spatial File again,\n");};
        if(fileRead != 2){ErrorMesage.append("Express File is allowed.");}else{ErrorMesage.append("Select Express File again.");};

        QMessageBox::information(this, "Error", ErrorMesage , QMessageBox::Ok); //error message
    }


//    if(GeneBoolean&&SpatialBoolean&&ExpressBoolean){
//        QMessageBox::information(this, "Success", "File has been uploaded.", QMessageBox::Ok); //sucess message
//        close(); //closes this window and opens the menu

//    }else{

//        QString ErrorMesage = "Could not find all of the files.\n";
//        if(GeneBoolean){ErrorMesage.append("Gene File is allowed,\n");}else{ErrorMesage.append("Select Gene File again,\n");};
//        if(SpatialBoolean){ErrorMesage.append("Spatial File is allowed,\n");}else{ErrorMesage.append("Select Spatial File again,\n");};
//        if(ExpressBoolean){ErrorMesage.append("Express File is allowed.");}else{ErrorMesage.append("Select Express File again.");};

//        QMessageBox::information(this, "Error", ErrorMesage , QMessageBox::Ok); //error message
//    }

}


