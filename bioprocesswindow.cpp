#include "bioprocesswindow.h"
#include "filedata.h"
#include "ui_bioprocesswindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include "api_bio_pro_to_gene.h"



bioprocesswindow::bioprocesswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bioprocesswindow)
{
    ui->setupUi(this);
    uploadChecker=false;
}

bioprocesswindow::~bioprocesswindow()
{
    delete ui;
}


void bioprocesswindow::on_MenuWindowButton_clicked()
{
    this->close();
    emit chooserWindow(); //returns to chooserWindow
}



void bioprocesswindow::on_UploadGenesButton_clicked(){

    QString FileFilter = "Txt File (*.txt);;";
    QString userText = QFileDialog::getOpenFileName(this, "Open a File", "C:\\Users\\", FileFilter);

    FileData geneNames;

    filename = userText.toStdString();
    uploadChecker = geneNames.readGenes(filename); //checks for successful upload and reads the genes

    if(uploadChecker){
        QMessageBox::information(this, "Success", "File has been uploaded.", QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this, "Error", "Could not find file, please specify the entire file location.", QMessageBox::Ok);
    }
};

void bioprocesswindow::openHeatMapWindow(){
    heatmapWindow = new HeatMapWindow(this);
    connect(heatmapWindow, &HeatMapWindow::PreviousWindow, this, &HeatMapWindow::show); //connects menuwindow and colocalizationwindow so that we can navigate between them

    // perform biological process analysis
    // crop data at 5000 columns due to computational constraints
    biologicalprocess object = biologicalprocess(files,0,5000);
    // retrieve genes that appear both in the list containing genes correlated to the
    // biological process of interest provided by the researcher and genes that are supported by the
    // data base
    std::vector<std::string> geneSubsetBioPro;
    int nb_study = 50;
    geneSubsetBioPro = api_bio_pro_to_gene::api_bio_pro_to_gene_function(files.getGenePath(),filename,nb_study);
    object.addGeneList(geneSubsetBioPro);
    // compute expression ratio
    object.compute_tot_expr();

    // plot expression ratio
    heatmapWindow->makeHeatMap(object.getPerc_expression());
    this->hide(); //hides menuwindow
    heatmapWindow->show(); //shows biowindow
    //heatmapWindow->makeHeatMap(); //generates the heatmap
}

void bioprocesswindow::on_AnalyzeButton_clicked()
{
    if(uploadChecker){
        QMessageBox::information(this, "Success", "File has been uploaded correctly. \n" , QMessageBox::Ok);
        openHeatMapWindow();
    }else{
        QMessageBox::information(this, "Error", "Please upload a file. \n" , QMessageBox::Ok);

    }


}




