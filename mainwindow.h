#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "secondwindow.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QString>
#include <QDialog>


using namespace std;

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


private:
    Ui::MainWindow *ui;//UI window

    SecondWindow *Pointersecondwindow;

    QString userText;//User text input
    string filename;//std::string of user input
    vector<QString> left;
    vector<QString> right;

};
#endif // MAINWINDOW_H
