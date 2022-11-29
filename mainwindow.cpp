#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
//#include <QDebug>
#include <QMessageBox>
#include <fstream>
using namespace std;

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
    userText= ui->plainTextEdit->toPlainText();
    filename = userText.toStdString();

    ifstream coordinates;

    coordinates.open(filename);

    if(coordinates.fail()){
       QMessageBox::information(this, "Error", "Could not find file, please specify the entire file location", QMessageBox::Ok);
    }
    int i = 0;
        while(coordinates.peek() != EOF){
            string coordinate;
            getline(coordinates,coordinate,',');

            QString s = QString::fromStdString(coordinate);
            qDebug().nospace() << qPrintable(s);

            /*if(i%2 == 0){
                left.push_back(s);
            }
            else{
                right.push_back(s);
            }*/

            //uncomment the following line and run to see something funny
          //QMessageBox::information(this, "Error", QString::fromStdString(coordinate), QMessageBox::Ok);

            //            i++;

        }

        coordinates.close();

}
//file location on Leonard's computer
//C:\Users\leona\OneDrive\Bureau\TranscriptomiC\dummyData.csv


