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
    biowindow = new bioprocesswindow;
    biowindow->setFileObject(files);
    connect(bioprocesswindow, &bioprocesswindow::chooserWindow, this, &BioChooser::show); //connects menuwindow and colocalizationwindow so that we can navigate between them


    this->hide();
    biowindow->show();
}

