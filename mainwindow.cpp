#include "mainwindow.h"
#include "SecondWindow.h"
#include "ui_mainwindow.h"
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
    delete PointerSecondWindow;
}

void MainWindow::close(){

<<<<<<< Updated upstream
    Pointersecondwindow = new SecondWindow(this);
    Pointersecondwindow->setX(inputData.getX());
    Pointersecondwindow->setY(inputData.getY());
<<<<<<< HEAD
    Pointersecondwindow->setP(inputData.getP());

=======
    PointerSecondWindow = new SecondWindow(this);
    PointerSecondWindow->setX(inputData.getX());
    PointerSecondWindow->setY(inputData.getY());
>>>>>>> Stashed changes
=======
>>>>>>> parent of 63260a0 (Merge branch 'main' into QMake-Revamp-Second-GUIdirected)

    PointerSecondWindow->makePlot();
    PointerSecondWindow->show();

    this->hide();
}

void MainWindow::on_SelectButton_clicked()
{
    QString FileFilter = "Text File (*.txt) ;; CSV File (*.csv) ;; MTX File (*.mtx)"; //All File (*.*) ;;
    QString userText = QFileDialog::getOpenFileName(this, "Open a File", "C:\\Users\\", FileFilter);
    ui->plainTextEdit->setPlainText(userText);

}


void MainWindow::on_UploadButton_clicked()
{
    userText= ui->plainTextEdit->toPlainText();
    filename = userText.toStdString();


    readBoolean = inputData.readData(filename);

    if(readBoolean){
        QMessageBox::information(this, "Success", "File has been uploaded.", QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this, "Error", "Could not find file, please specify the entire file location.", QMessageBox::Ok);

    }

<<<<<<< HEAD
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
=======
    close();
>>>>>>> parent of 63260a0 (Merge branch 'main' into QMake-Revamp-Second-GUIdirected)


}


