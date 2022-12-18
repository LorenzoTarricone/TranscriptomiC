#ifndef BIOPROCESSWINDOW_H
#define BIOPROCESSWINDOW_H

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

    void makeHeatMap();

private:
    Ui::bioprocesswindow *ui;
};

#endif // BIOPROCESSWINDOW_H
