#include "biochooser.h"
#include "ui_biochooser.h"
#include "ui_bioprocesswindow.h"
#include "bioprocesswindow.h"


BioChooser::BioChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BioChooser)
{
    ui->setupUi(this);
}

BioChooser::~BioChooser()
{
    delete ui;
}

void BioChooser::on_MenuButton_clicked()
{
    this->close();
    emit MenuWindow(); //returns to menuWindow
}


void BioChooser::on_ProcessButton_clicked()
{
    biowindow = new bioprocessWindow;
    biowindow->setFileObject(files);
}

