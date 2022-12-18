#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include "qdebug.h"
#include <QMainWindow>
#include <QVector>

class MainWindow;

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

    //SecondWindow* get_Pointer() {return PointerSecondWindow;};

    void makePlot();


<<<<<<< HEAD
<<<<<<< Updated upstream
    void setX(const QVector<double>& givenX) {x = givenX;};
=======
    void setX(const QVector<double>& givenX) {

        //qDebug() << "setX()" << QString::number(givenX.size());//
        x = givenX;
        //qDebug() << "size of x" << QString::number(x.size());//


    };
>>>>>>> parent of 63260a0 (Merge branch 'main' into QMake-Revamp-Second-GUIdirected)
    void setY(const QVector<double>& givenY) {y = givenY;};

    const QVector<double>& getX() {
        //qDebug() << "size of x in the getX() fucntion" << QString::number(x.size());
        return x;};
    const QVector<double>& getY() {return y;};

=======
    void setX(const QVector<double>& givenX) {
        x = givenX;
    };
    void setY(const QVector<double>& givenY) {y = givenY;};
>>>>>>> Stashed changes



<<<<<<< HEAD
private slots:
<<<<<<< Updated upstream
    void on_ColocalizationButton_clicked();
=======
    void on_NewFileButton_clicked();



>>>>>>> Stashed changes

    void on_BiologicalButton_clicked();

=======
>>>>>>> parent of 63260a0 (Merge branch 'main' into QMake-Revamp-Second-GUIdirected)
private:
    Ui::SecondWindow *ui;

    MainWindow* PointerMainWindow;

    QVector<double> x;
    QVector<double> y;

};

#endif // SECONDWINDOW_H
