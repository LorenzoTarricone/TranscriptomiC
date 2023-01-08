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



    PointerMenuWindow->setX(inputData.getX());
    PointerMenuWindow->setY(inputData.getY());
    PointerMenuWindow->setP(inputData.getP());


    PointerMenuWindow->makePlot();
    PointerMenuWindow->show();

    this->hide();
}

void UploadWindow::on_SelectButton_clicked()
{
    QString FileFilter = "CSV File (*.csv);; Text File (*.txt);;  MTX File (*.mtx)"; //All File (*.*) ;;
    QString userText = QFileDialog::getOpenFileName(this, "Open a File", "C:\\Users\\", FileFilter);
    ui->plainTextEdit->setPlainText(userText);

}


void UploadWindow::on_UploadButton_clicked()
{

    userText = ui->plainTextEdit->toPlainText();
    filename = userText.toStdString();


    readBoolean = inputData.readData(filename);

    if(readBoolean){
        QMessageBox::information(this, "Success", "File has been uploaded.", QMessageBox::Ok);
        close();
    }
    else{
        QMessageBox::information(this, "Error", "Could not find file, please specify the entire file location.", QMessageBox::Ok);

    }



}


