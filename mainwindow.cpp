#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "changewindow.h"
#include <fstream>
#include <QMessageBox>
#include <iostream>
#include <QDialog>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plainTextEdit->setPlainText("Please select a file and then upload it.");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::close(){
    ChangeWindow change;
    change.ChangeToSecondWindow();
    this->hide();
}

void MainWindow::on_SelectButton_clicked()
{
    QString FileFilter = "Text File (*.txt) ;; CSV File (*.csv) ;; MTX File (*.mtx)"; //All File (*.*) ;;
    QString userText = QFileDialog::getOpenFileName(this, "Open a File", "C:\\Users\\", FileFilter);
    ui->plainTextEdit->setPlainText(userText);

}


void MainWindow::on_UploadButton_clicked(){

    userText= ui->plainTextEdit->toPlainText();
    filename = userText.toStdString();


    readBoolean = inputData.readData(filename);

    if(readBoolean){
        QMessageBox::information(this, "Success", "File has been uploaded.", QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this, "Error", "Could not find file, please specify the entire file location.", QMessageBox::Ok);

    }

    close();


}


// -> works on a pointer
// :: works one namespace
// .  works on a object


