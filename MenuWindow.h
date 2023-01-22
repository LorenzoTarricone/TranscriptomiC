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
#include "biochooser.h"


namespace Ui {
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

    void makePlot(Eigen::MatrixXd m);



    void setFileObject(const parsefile& givenFiles) {files = givenFiles;};


signals:
    void UploadWindow();


private slots:
    void on_ColocalizationButton_clicked();

    void on_BiologicalButton_clicked();

    void on_UploadWindowButton_clicked();

private:
    Ui::MenuWindow *ui;
    colocalizationwindow *coWindow;
    BioChooser *biochooseWindow;



    parsefile files;
//    plotObject plot = plotObject{};
    computation object = computation{};

};

#endif // MENUWINDOW_H
