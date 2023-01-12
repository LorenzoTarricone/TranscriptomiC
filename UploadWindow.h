#ifndef UPLOADWINDOW_H
#define UPLOADWINDOW_H

#include <QMainWindow>
#include "MenuWindow.h"
#include "filedata.h"


QT_BEGIN_NAMESPACE
namespace Ui { class UploadWindow; }
QT_END_NAMESPACE

class UploadWindow : public QMainWindow
{
    Q_OBJECT

public:
    UploadWindow(QWidget *parent = nullptr);
    ~UploadWindow();

private slots:

    void on_GeneSelectButton_clicked();
    void on_SpatialSelectButton_clicked();
    void on_ExpressSelectButton_clicked();

    void on_UploadButton_clicked();
    void close();


private:
    Ui::UploadWindow *ui;

    MenuWindow *PointerMenuWindow;

    std::string GeneFilename;
    QString GeneUserText;
    std::string GeneInput;
    bool GeneBoolean;

    std::string SpatialFilename;
    QString SpatialUserText;
    std::string SpatialInput;
    bool SpatialBoolean;

    std::string ExpressFilename;
    QString ExpressUserText;
    std::string ExpressInput;
    bool ExpressBoolean;


    std::vector<double> x;
    std::vector<double> y;

    FileData inputData;
};
#endif // UPLOADWINDOW_H
