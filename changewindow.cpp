
#include "changewindow.h"



void ChangeWindow::ChangeToMainWindow(){


};

void ChangeWindow::ChangeToSecondWindow(){

    PointerSecondWindow = new SecondWindow(PointerMainWindow);

    //PointerSecondWindow->setX(inputData.getX());
    //PointerSecondWindow->setY(inputData.getY());
    //PointerSecondWindow->makePlot();

    PointerSecondWindow->show();

};
