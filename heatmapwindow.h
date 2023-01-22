#ifndef HEATMAPWINDOW_H
#define HEATMAPWINDOW_H

#include "computation.h"
#include "ui_heatmapwindow.h"
#include <QDialog>
#include <Eigen/Dense>
#include <Eigen/Eigen>

namespace Ui {
class HeatMapWindow;
}

class HeatMapWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HeatMapWindow(QWidget *parent = nullptr);
    ~HeatMapWindow();

//    void makeHeatMap();
    void makeHeatMap(const Eigen::MatrixXd m);
    void setX(const QVector<double>& givenX) {xCoordinates = givenX;};
    void setY(const QVector<double>& givenY) {yCoordinates = givenY;};
    void setP(const QVector<double>& givenP) {pValues = givenP;};

    void setObject(const computation givenObject) {object = givenObject;};


    void setLabel(std::string text){ui->label->setText(QString::fromStdString(text));};



private slots:
    void on_SaveHeatmapButton_clicked();

    void on_MenuButton_clicked();

signals:
    void PreviousWindow();

protected:
    Ui::HeatMapWindow *ui;

    QVector<double> xCoordinates;
    QVector<double> yCoordinates;
    QVector<double> pValues;

    computation object;

};

#endif // HEATMAPWINDOW_H
