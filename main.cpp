
#include "UploadWindow.h"
#include <QApplication>

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include <QJsonDocument>
#include <set>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UploadWindow w;
    w.show();
    return a.exec();


}


