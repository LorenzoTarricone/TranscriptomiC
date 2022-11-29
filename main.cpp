#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    arrow::Status st = RunMain();
    if (!st.ok()) {
      std::cerr << st << std::endl;
      return 1;
    }
    return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
