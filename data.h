#ifndef DATA_H
#define DATA_H


#include "ui_mainwindow.h"
#include <string>
#include <vector>
#include <QMainWindow>



class data
{
public:
    data();
    void uploadData();
    void parseData();
    std::vector<double> getX() {return xCoordinates;};
    std::vector<double> getY() {return yCoordinates;};



private:
    std::vector<double> xCoordinates;
    std::vector<double> yCoordinates;
    std::string filename;

    Ui::MainWindow *ui;
    QString userText;//User text input


};

#endif // DATA_H
