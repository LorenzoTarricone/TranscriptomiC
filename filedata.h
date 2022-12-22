#ifndef FILEDATA_H
#define FILEDATA_H

#include <string>
#include <vector>
#include <QVector>


class FileData
{
public:
    FileData();

    const QVector<double>& getX() {return xCoordinates;};
    const QVector<double>& getY() {return yCoordinates;};
    const QVector<double>& getP() {return pValues;};
    const std::vector<std::string>& getGenes() {return genesToAnalyze;};


    bool readData(std::string fileName);
    bool readGenes(std::string fileName);


private:
    QVector<double> xCoordinates;
    QVector<double> yCoordinates;
    QVector<double> pValues;

    std::string x;
    std::string y;
    std::string p;
    std::string row;

    std::vector<std::string> genesToAnalyze;
    std::string g;


};

#endif // FILEDATA_H
