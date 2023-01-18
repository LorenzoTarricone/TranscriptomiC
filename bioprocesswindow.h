#ifndef BIOPROCESSWINDOW_H
#define BIOPROCESSWINDOW_H

#include "heatmapwindow.h"
#include <QDialog>
#include <Eigen/Eigen>
/*Includes Dense and Sparse header files (the whole Eigen library)*/
using Eigen::MatrixXd;
using namespace std;

namespace Ui {
class bioprocesswindow;
}

class bioprocesswindow : public QDialog
{
    Q_OBJECT

public:
    explicit bioprocesswindow(QWidget *parent = nullptr);
    ~bioprocesswindow();

    void makeHeatMap();
    void setX(const QVector<double>& givenX) {xCoordinates = givenX;};
    void setY(const QVector<double>& givenY) {yCoordinates = givenY;};
    void setP(const QVector<double>& givenP) {pValues = givenP;};

    void setProcessesToAnalyze();
    void openHeatMapWindow();

    const QVector<double>& getX() {return xCoordinates;};
    const QVector<double>& getY() {return yCoordinates;};
    const QVector<double>& getP() {return pValues;};



signals:
    void MenuWindow();


private slots:

    void on_MenuWindowButton_clicked();

    void on_SaveHeatmapButton_clicked();

    void on_AnalyzeButton_clicked();

    void on_GenerateHeatmapButton_clicked();

private:
    Ui::bioprocesswindow *ui;

    QVector<double> xCoordinates;
    QVector<double> yCoordinates;
    QVector<double> pValues;

    std::vector<std::string> processesToAnalyze;
    std::string inputProcess;

    HeatMapWindow *heatmapWindow;



};

#endif // BIOPROCESSWINDOW_H
