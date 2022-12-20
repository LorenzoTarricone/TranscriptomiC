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

    bool readData(std::string fileName);


private:
    QVector<double> xCoordinates;
    QVector<double> yCoordinates;

    std::string x;
    std::string y;
    std::string row;


};

#endif // FILEDATA_H
