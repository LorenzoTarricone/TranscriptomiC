#include <QCoreApplication>
#include "Visualize.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Code to read and visualize the data
    //start
    string myFilePath = "fake_coordinates.csv"; // get file fake_coordinates
    CSV b;
    b.read_csv_file(myFilePath);
    //end
    return a.exec();
}
