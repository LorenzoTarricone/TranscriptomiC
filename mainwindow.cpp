#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    /*prints hello on the console and opens a dialogue box (completely useless, just experimenting)
     *
     * qDebug() << "Hello";
    QMessageBox::information(this, "Message", "Check the console", QMessageBox::Ok);*/

    userText= ui->plainTextEdit->toPlainText();
    qDebug() << "Text: " << userText;

    filename = userText.toStdString();
}

