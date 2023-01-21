#ifndef BIOPROCESSWINDOW_H
#define BIOPROCESSWINDOW_H

#include "biologicalprocess.h"
#include "computation.h"
#include "heatmapwindow.h"
#include "parsefile.h"
#include <QDialog>

namespace Ui {
class bioprocesswindow;
}

class bioprocesswindow : public QDialog
{
    Q_OBJECT

public:
    explicit bioprocesswindow(QWidget *parent = nullptr);
    ~bioprocesswindow();


    void setFileObject(const parsefile givenFiles) {files = givenFiles;};

    void openHeatMapWindow();


signals:
    void MenuWindow();


private slots:

    void on_MenuWindowButton_clicked();


    void on_UploadGenesButton_clicked();

    void on_AnalyzeButton_clicked();


private:
    Ui::bioprocesswindow *ui;

    bool uploadChecker;


    std::string filename;

    HeatMapWindow *heatmapWindow;

    parsefile files;
//    plotObject plot = plotObject{};
    biologicalprocess object; // = biologicalprocess();

};

#endif // BIOPROCESSWINDOW_H
