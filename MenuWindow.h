#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "colocalizationwindow.h"
#include "bioprocesswindow.h"
#include "fake_colocalization_matrix.h" // just for the test
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


    const QVector<double>& getX() {return x;};
    const QVector<double>& getY() {return y;};
    const QVector<double>& getP() {return p;};

signals:
    void UploadWindow();


private slots:
    void on_ColocalizationButton_clicked();

    void on_BiologicalButton_clicked();

    void on_MenuWindowButton_clicked();

private:
    Ui::MenuWindow *ui;
    colocalizationwindow *coWindow;
    bioprocesswindow *bioWindow;


    QVector<double> x;
    QVector<double> y;
    QVector<double> p;


};

#endif // MENUWINDOW_H
