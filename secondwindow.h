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

    MatrixXd getMatrix() {return m;};
    void setMatrix(MatrixXd& given_m) {m = given_m;};

private slots:
    void on_ColocalizationButton_clicked();

    void on_BiologicalButton_clicked();

private:
    Ui::SecondWindow *ui;
    colocalizationwindow *coWindow;
    bioprocesswindow *bioWindow;

    MatrixXd m;


};

#endif // SECONDWINDOW_H
