#ifndef FILEDATA_H
#define FILEDATA_H

#include "Eigen/Eigen"
#include <string>
#include <vector>
#include <QVector>
using namespace std;

class FileData
{
public:
    FileData();

    //Spatial
    const QVector<double>& getX() {return xCoordinates;};
    const QVector<double>& getY() {return yCoordinates;};
    const QVector<double>& getP() {return pValues;};
    //read Spatial
    bool readSpatial(string fileName);

    //Genes
    const vector<string>& getGenes() {return genesToAnalyze;};
    //read Genes
    bool readGenes(string fileName);

    //Expression Matrix
    const Eigen::MatrixXd& getMatrix() {return m;};
    //read Matrix
    bool readMatrix(string fileName);


private:
    //Expression/Spatial
    QVector<double> xCoordinates;
    QVector<double> yCoordinates;
    QVector<double> pValues;

    //Genes
    vector<string> genesToAnalyze;

    //Matrix
    Eigen::MatrixXd m;


};

#endif // FILEDATA_H
