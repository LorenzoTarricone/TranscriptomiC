#ifndef COLOCALIZATIONWINDOW_H
#define COLOCALIZATIONWINDOW_H

#include "bioprocesswindow.h"
#include <QDialog>

namespace Ui {
class colocalizationwindow;
}

class colocalizationwindow : public QDialog
{
    Q_OBJECT

public:
    explicit colocalizationwindow(QWidget *parent = nullptr);
    ~colocalizationwindow();

    void makeHeatMap();
    void setX(const QVector<double>& givenX) {xCoordinates = givenX;};
    void setY(const QVector<double>& givenY) {yCoordinates = givenY;};
    void setP(const QVector<double>& givenP) {pValues = givenP;};


    const QVector<double>& getX() {return xCoordinates;};
    const QVector<double>& getY() {return yCoordinates;};
    const QVector<double>& getP() {return pValues;};

signals:
    void MenuWindow();


private slots:
    void on_SaveHeatmapButton_clicked();

    void on_UploadGenesButton_clicked();

    void on_MenuWindowButton_clicked();

    void on_BiologicalButton_clicked();

private:
    Ui::colocalizationwindow *ui;

    QVector<double> xCoordinates;
    QVector<double> yCoordinates;
    QVector<double> pValues;

};

#endif // COLOCALIZATIONWINDOW_H
