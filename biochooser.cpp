#include "biochooser.h"
#include "api.h"
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
    connect(biowindow, &bioprocesswindow::chooserWindow, this, &BioChooser::show); //connects menuwindow and colocalizationwindow so that we can navigate between them


    this->hide();
    biowindow->show();
}


void BioChooser::on_ClusterButton_clicked()
{
    cluster1 = new HeatMapWindow(this);
    connect(cluster1, &HeatMapWindow::PreviousWindow, this, &HeatMapWindow::show); //connects menuwindow and colocalizationwindow so that we can navigate between them

    cluster2 = new HeatMapWindow(this);
    connect(cluster2, &HeatMapWindow::PreviousWindow, this, &HeatMapWindow::show); //connects menuwindow and colocalizationwindow so that we can navigate between them

    cluster3 = new HeatMapWindow(this);
    connect(cluster3, &HeatMapWindow::PreviousWindow, this, &HeatMapWindow::show); //connects menuwindow and colocalizationwindow so that we can navigate between them

    cluster4 = new HeatMapWindow(this);
    connect(cluster4, &HeatMapWindow::PreviousWindow, this, &HeatMapWindow::show); //connects menuwindow and colocalizationwindow so that we can navigate between them


    // perform cluster analysis

    qDebug() << "Initialize BiologicalProcess object";
    int rows = 100;
    int cols = 700;
    biologicalprocess object = biologicalprocess(files,rows,cols);
    object.filter_simple(true,0.001);
    qDebug() << "Start clustering";
    std::vector<std::string> clusters_dict=object.bioprocess_2(4,3);

    qDebug() << "Referencing clusters";
    std::vector<std::string> bio_process = getOverrep(clusters_dict);
    std::vector<std::vector<std::string>> clusters = object.plottable(clusters_dict);

    std::vector<HeatMapWindow*> heatmaps;
    heatmaps.push_back(cluster1);
    heatmaps.push_back(cluster2);
    heatmaps.push_back(cluster3);
    heatmaps.push_back(cluster4);


    HeatMapWindow* tmp;
    biologicalprocess clusterObject;
    for(int i = 0; i < 4; i++){
        if(clusters_dict[i] != "empty"){
            qDebug() << "Cluster : " << i ;
            tmp = heatmaps[i];
            clusterObject = biologicalprocess(files,rows,cols);
            clusterObject.addGeneList(clusters[i]);
            clusterObject.compute_tot_expr();
            tmp->setLabel(bio_process[i]);

            tmp->makeHeatMap(clusterObject.getPerc_expression());
            tmp->show(); //shows biowindow
        }

    }

    this->hide(); //hides menuwindow



    std::cout << "Biological processes: \n";
    for (std::string i : bio_process){
        std::cout << i << ",";
    }
    std::cout << std::endl;





//    cluster1->makeHeatMap(object.getPerc_expression());
//    cluster1->show(); //shows biowindow

//    cluster2->makeHeatMap(object.getPerc_expression());
//    cluster2->show(); //shows biowindow

//    cluster3->makeHeatMap(object.getPerc_expression());
//    cluster3->show(); //shows biowindow

//    cluster4->makeHeatMap(object.getPerc_expression());
//    cluster4->show(); //shows biowindow


//    this->hide(); //hides menuwindow

}

