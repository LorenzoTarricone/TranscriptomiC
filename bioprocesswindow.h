#ifndef BIOPROCESSWINDOW_H
#define BIOPROCESSWINDOW_H

#include <QDialog>
#include <Eigen/Eigen>
/*Includes Dense and Sparse header files (the whole Eigen library)*/
using Eigen::MatrixXd;
using namespace std;

namespace Ui {
class bioprocesswindow;
}

class bioprocesswindow : public QDialog
{
    Q_OBJECT

public:
    explicit bioprocesswindow(QWidget *parent = nullptr);
    ~bioprocesswindow();

    void makeHeatMap(MatrixXd m);

    void setProcessesToAnalyze();


signals:
    void MenuWindow();


private slots:
    void on_SaveHeatmapButton_clicked();
    void on_AnalyzeButton_clicked();

    void on_MenuWindowButton_clicked();

private:
    Ui::bioprocesswindow *ui;

    std::vector<std::string> processesToAnalyze;
    std::string inputProcess;


};

#endif // BIOPROCESSWINDOW_H
