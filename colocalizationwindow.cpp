#include "colocalizationwindow.h"
#include "ui_colocalizationwindow.h"
#include "filedata.h"
#include <iostream>
#include "qdebug.h"


colocalizationwindow::colocalizationwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::colocalizationwindow)
{
    ui->setupUi(this);
}

colocalizationwindow::~colocalizationwindow()
{
    delete ui;
}

void colocalizationwindow::makeHeatMap(){

    // configure axis rect:
           ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
           ui->customPlot->axisRect()->setupFullAxesBox(true);
           ui->customPlot->xAxis->setLabel("x");
           ui->customPlot->yAxis->setLabel("y");
           // set up the QCPColorMap:
           QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);
           int nx = 6;
           int ny = 4;
           colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
           colorMap->data()->setRange(QCPRange(0, 6), QCPRange(0, 4)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions

           // now we assign some data, by accessing the QCPColorMapData instance of the color map:
           //HERE WE WOULD LIKE TO USE THE DATA FROM THE TEXTFILES

           double x, y, z;/*
           // Questions: Can we plot specific coordinates or do we have to plot in a specific range?
           for(int xIndex = 0; xIndex<=nx; xIndex++){
               for(int yIndex = 0; yIndex<=nx; yIndex++){
                    colorMap->data()->cellToCoord(getX()[xIndex],getY()[yIndex], &x, &y);
                    // random function for third coordinate
                    z = sin(x) + sin(y);
                    colorMap->data()->setCell(xIndex, yIndex, getP()[xIndex]);
               }
           }*/

           qDebug() << "X vector" <<getX();
           qDebug() << "Y vector" <<getY();
           qDebug() << "P vector" <<getP();


           for(int xIndex = 0; xIndex<=nx; xIndex++){
               //colorMap->data()->cellToCoord(getX()[xIndex],getY()[xIndex], &x, &y);
                    // random function for third coordinate
                    //z = sin(x) + sin(y);
               colorMap->data()->setCell(getX()[xIndex], getY()[xIndex], getP()[xIndex]);

           }

           // set the color gradient of the color map to one of the presets:
           colorMap->setGradient(QCPColorGradient::gpPolar);
           // we could have also created a QCPColorGradient instance and added own colors to
           // the gradient, see the documentation of QCPColorGradient for what's possible.
           // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
           colorMap->rescaleDataRange();
           // rescale the key (x) and value (y) axes so the whole color map is visible:
           ui->customPlot->rescaleAxes();

}

void colocalizationwindow::on_SaveHeatmapButton_clicked()
{
    QPixmap heatmap;
    heatmap = ui->customPlot->grab();
    QString filename;

    filename = QFileDialog::getSaveFileName(this,"Save file");
    //qDebug() << filename;
    //filename = filename +
    //QFile file("HeatMap.png");
    //file.open(QIODevice::WriteOnly);
    //heatmap.save(&file, "PNG");

    heatmap.save(filename + ".png"); //QDir::currentPath() + "/HeatMap.png"
    //qDebug() << QDir::currentPath();
}


void colocalizationwindow::on_UploadGenesButton_clicked()
{
    QString FileFilter = "CSV File (*.csv);; Text File (*.txt);;  MTX File (*.mtx)"; //All File (*.*) ;;
    QString userText = QFileDialog::getOpenFileName(this, "Open a File", "C:\\Users\\", FileFilter);
    std::string filename;
    FileData geneNames;
    bool uploadChecker;

    filename = userText.toStdString();


    uploadChecker = geneNames.readData(filename);

    if(uploadChecker){
        QMessageBox::information(this, "Success", "File has been uploaded.", QMessageBox::Ok);
        close();
    }
    else{
        QMessageBox::information(this, "Error", "Could not find file, please specify the entire file location.", QMessageBox::Ok);

    }
}

