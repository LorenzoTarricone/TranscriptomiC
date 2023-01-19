#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "Eigen/Eigen"
#include "colocalizationwindow.h"
#include "bioprocesswindow.h"
#include "filedata.h"
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

    void setData(FileData givenData){Data = givenData;};




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

   FileData Data;


};

#endif // MENUWINDOW_H
