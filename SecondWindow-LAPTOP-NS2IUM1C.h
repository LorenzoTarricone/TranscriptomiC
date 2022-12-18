#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include "qdebug.h"
#include <QMainWindow>
#include <QVector>



namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

    void makePlot();


    void setX(const QVector<double>& givenX) {

        //qDebug() << "setX()" << QString::number(givenX.size());//
        x = givenX;
        //qDebug() << "size of x" << QString::number(x.size());//


    };
    void setY(const QVector<double>& givenY) {y = givenY;};

    const QVector<double>& getX() {
        //qDebug() << "size of x in the getX() fucntion" << QString::number(x.size());
        return x;};
    const QVector<double>& getY() {return y;};


private slots:
    void on_NewFileButton_clicked();





private:
    Ui::SecondWindow *ui;

    MainWindow *PointerMainWindow;


    QVector<double> x;
    QVector<double> y;


};

#endif // SECONDWINDOW_H
