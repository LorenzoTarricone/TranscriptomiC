#include "UploadWindow.h"
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
    ui->plainTextEdit->setPlainText("Please select a file and then upload it.");

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

    PointerMenuWindow = new MenuWindow(this);

    //uncomment for plotting colocalization
    //PointerMenuWindow->setMatrix(inputData.getMatrix());

    //sets the data biological process
    PointerMenuWindow->setX(inputData.getX());
    PointerMenuWindow->setY(inputData.getY());
    PointerMenuWindow->setP(inputData.getP());

    PointerMenuWindow->show(); //shows menuwindow

    this->hide(); //hides uploadwindow
}

void UploadWindow::on_SelectButton_clicked()
{
    /*This function opens the file explorer and allows the user to choose a file. Once that file is
     * chosen, it sets the path as the text in the text edit.
     */

    QString FileFilter = "CSV File (*.csv);; Text File (*.tsv);;  MTX File (*.mtx)"; //creates a file filter so that only the relevant formats can be chosen
    QString userText = QFileDialog::getOpenFileName(this, "Open a File", "C:\\Users\\", FileFilter); //opens the file explorer with the filter
    ui->plainTextEdit->setPlainText(userText); //sets the test in the text edit to be the flie location

}


void UploadWindow::on_UploadButton_clicked()
{
    /*This file uploads the data. It reads it and parses it, if everything is fine, then it opens the menu
     * window and closes the upload window.
     */


    userText = ui->plainTextEdit->toPlainText(); //takes the file location
    filename = userText.toStdString(); //converts the file location to std::string

    //Uncomment for colocalization
    //readBoolean = inputData.setData_Matrix(filename); //reads and parses the data, returns a boolean to check for sucessful upload
    readBoolean = inputData.readData(filename);
    if(readBoolean){
        QMessageBox::information(this, "Success", "File has been uploaded.", QMessageBox::Ok); //sucess message
        close(); //closes this window and opens the menu
    }
    else{
        QMessageBox::information(this, "Error", "Could not find file, please specify the entire file location.", QMessageBox::Ok); //error message

    }



}


