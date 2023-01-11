#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include "colocalizationwindow.h"
#include "bioprocesswindow.h"
#include "qdebug.h"
#include <QMainWindow>
#include <QVector>


namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

    void makePlot();


    void setX(const QVector<double>& givenX) {x = givenX;};
    void setY(const QVector<double>& givenY) {y = givenY;};
    void setP(const QVector<double>& givenP) {p = givenP;};


    const QVector<double>& getX() {return x;};
    const QVector<double>& getY() {return y;};
    const QVector<double>& getP() {return p;};




private slots:
    void on_ColocalizationButton_clicked();

    void on_BiologicalButton_clicked();

private:
    Ui::SecondWindow *ui;
    colocalizationwindow *coWindow;
    bioprocesswindow *bioWindow;


    QVector<double> x;
    QVector<double> y;
    QVector<double> p;


};

#endif // SECONDWINDOW_H
