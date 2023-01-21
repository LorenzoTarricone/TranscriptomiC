#ifndef BIOCHOOSER_H
#define BIOCHOOSER_H

#include "bioprocesswindow.h"
#include <QDialog>

namespace Ui {
class BioChooser;
}

class BioChooser : public QDialog
{
    Q_OBJECT

public:
    explicit BioChooser(QWidget *parent = nullptr);
    ~BioChooser();
    void setFileObject(const parsefile givenFiles) {files = givenFiles;};


signals:
    void MenuWindow();

private slots:
    void on_MenuButton_clicked();

    void on_ProcessButton_clicked();

    void on_ClusterButton_clicked();

private:
    Ui::BioChooser *ui;
    bioprocesswindow *biowindow;
    parsefile files;

    HeatMapWindow *cluster1, *cluster2, *cluster3, *cluster4;
};

#endif // BIOCHOOSER_H
