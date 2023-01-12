#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow.h"
#include "upload_matrix.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_SelectButton_clicked();
    void on_UploadButton_clicked();

    void close();


private:
    Ui::MainWindow *ui;

    SecondWindow *Pointersecondwindow;

    QString userText;
    std::string input;

    std::string filename;

    upload_matrix inputData;
    bool readBoolean;
};
#endif // MAINWINDOW_H
