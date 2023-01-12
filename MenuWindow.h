#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "colocalizationwindow.h"
#include "bioprocesswindow.h"
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

     MatrixXd getMatrix() {return m;};
     void setMatrix(MatrixXd& given_m) {m = given_m;};

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

    MatrixXd m;



};

#endif // MENUWINDOW_H
