#include "bioprocesswindow.h"
#include "filedata.h"
#include "ui_bioprocesswindow.h"
#include <QMessageBox>
#include <QFileDialog>




bioprocesswindow::bioprocesswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bioprocesswindow)
{
    ui->setupUi(this);
    ui->ChosenProcessText->setPlainText("Write here the chosen Process");
    uploadChecker=false;
}

bioprocesswindow::~bioprocesswindow()
{
    delete ui;
}


void bioprocesswindow::on_MenuWindowButton_clicked()
{
    this->close();
    emit MenuWindow(); //returns to menuWindow
}



void bioprocesswindow::setProcessesToAnalyze(){
    //this function will just create a vector with all the processes we can analyze
    //TEMPORARY, in the end we will have something a lot more sophisticated

    processesToAnalyze.push_back("hypoxia");

}

void bioprocesswindow::on_UploadGenesButton_clicked(){

    QString FileFilter = "Txt File (*.txt);;";
    QString userText = QFileDialog::getOpenFileName(this, "Open a File", "C:\\Users\\", FileFilter);
    std::string filename;
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


    heatmapWindow->setX(this->getX());
    heatmapWindow->setY(this->getY());
    heatmapWindow->setP(this->getP());

    this->hide(); //hides menuwindow
    heatmapWindow->show(); //shows biowindow
    //heatmapWindow->makeHeatMap(); //generates the heatmap
}

void bioprocesswindow::on_AnalyzeButton_clicked()
{
    QString bio;
    std::string process;

    bio = ui->ChosenProcessText->toPlainText(); //gets the text the user wrote
    ui->ChosenProcessText->setPlainText("Write here the chosen Process"); //resets the text box to be empty

    process = bio.toStdString();

    std::transform(process.begin(), process.end(), process.begin(), ::tolower); //converts to lowercase

    //if we can analyze that process assign it to inputProcess, if not send error message
    if ( (std::find(processesToAnalyze.begin(), processesToAnalyze.end(), process) != processesToAnalyze.end()) && uploadChecker){
        inputProcess = process;
        openHeatMapWindow();
    }
    else{

        QString ErrorMesage = "Invalid Parameters.\n";
        if(uploadChecker){ErrorMesage.append("File has been uploaded correctly. \n");}else{ErrorMesage.append("Please upload a file. \n");};
        if((std::find(processesToAnalyze.begin(), processesToAnalyze.end(), process) != processesToAnalyze.end())){ErrorMesage.append("Valid Percentage of Expression. \n");}else{ErrorMesage.append( "We cannot analyze that process, please provide another one.");};

        QMessageBox::information(this, "Error", ErrorMesage , QMessageBox::Ok);
    }

}


