#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "colocalizationwindow.h"
#include "bioprocesswindow.h"
#include "computation.h"
#include "parsefile.h"
#include "plotobject.h"
#include "qdebug.h"
#include <QMainWindow>
#include <QVector>


namespace Ui {
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

    void makePlot();


    void setX(const QVector<double>& givenX) {x = givenX;};
    void setY(const QVector<double>& givenY) {y = givenY;};
    void setP(const QVector<double>& givenP) {p = givenP;};

    void setFileObject(const parsefile& givenFiles) {files = givenFiles;};
//    void setPlotObject(const plotObject givenPlot){ plot = givenPlot;};

    const QVector<double>& getX();
    const QVector<double>& getY();
    const QVector<double>& getP();

//    const QVector<double>& getX() {return x;};
//    const QVector<double>& getY() {return y;};
//    const QVector<double>& getP() {return p;};

signals:
    void UploadWindow();


private slots:
    void on_ColocalizationButton_clicked();

    void on_BiologicalButton_clicked();

    void on_UploadWindowButton_clicked();

private:
    Ui::MenuWindow *ui;
    colocalizationwindow *coWindow;
    bioprocesswindow *bioWindow;


    QVector<double> x;
    QVector<double> y;
    QVector<double> p;

    parsefile files;
//    plotObject plot = plotObject{};
    computation object = computation{};

};

#endif // MENUWINDOW_H
