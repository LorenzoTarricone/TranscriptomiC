#ifndef COLOCALIZATIONWINDOW_H
#define COLOCALIZATIONWINDOW_H

#include <QDialog>
#include <Eigen/Eigen>
/*Includes Dense and Sparse header files (the whole Eigen library)*/
using Eigen::MatrixXd;

namespace Ui {
class colocalizationwindow;
}

class colocalizationwindow : public QDialog
{
    Q_OBJECT

public:
    explicit colocalizationwindow(QWidget *parent = nullptr);
    ~colocalizationwindow();

    void makeHeatMap(MatrixXd m);

private slots:
    void on_SaveHeatmapButton_clicked();
    void on_UploadGenesButton_clicked();

private:
    Ui::colocalizationwindow *ui;
};

#endif // COLOCALIZATIONWINDOW_H
