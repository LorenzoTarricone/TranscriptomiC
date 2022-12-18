#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qdebug.h"
#include <QMainWindow>
#include "SecondWindow.h"
#include "filedata.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //MainWindow* get_Pointer() {return PointerMainWindow;};


private slots:
    void on_SelectButton_clicked();
    void on_UploadButton_clicked();

    void close();


private:
    Ui::MainWindow *ui;

    SecondWindow *PointerSecondWindow;

    QString userText;
    std::string input;

    std::string filename;
    std::vector<double> x;
    std::vector<double> y;

    FileData inputData;
    bool readBoolean;
};
#endif // MAINWINDOW_H
