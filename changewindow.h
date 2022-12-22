#ifndef CHANGEWINDOW_H
#define CHANGEWINDOW_H

#include "mainwindow.h"
#include "SecondWindow.h"

class ChangeWindow{

public:
    void ChangeToMainWindow();
    void ChangeToSecondWindow();


private:
    MainWindow *PointerMainWindow;
    SecondWindow *PointerSecondWindow;

};

#endif // FILEDATA_H
