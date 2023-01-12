#ifndef HEATMAPWINDOW_H
#define HEATMAPWINDOW_H

#include <QDialog>

namespace Ui {
class HeatMapWindow;
}

class HeatMapWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HeatMapWindow(QWidget *parent = nullptr);
    ~HeatMapWindow();

    void makeHeatMap();
    void setX(const QVector<double>& givenX) {xCoordinates = givenX;};
    void setY(const QVector<double>& givenY) {yCoordinates = givenY;};
    void setP(const QVector<double>& givenP) {pValues = givenP;};


    const QVector<double>& getX() {return xCoordinates;};
    const QVector<double>& getY() {return yCoordinates;};
    const QVector<double>& getP() {return pValues;};

private slots:
    void on_SaveHeatmapButton_clicked();

    void on_MenuButton_clicked();

signals:
    void PreviousWindow();

private:
    Ui::HeatMapWindow *ui;

    QVector<double> xCoordinates;
    QVector<double> yCoordinates;
    QVector<double> pValues;

};

#endif // HEATMAPWINDOW_H
