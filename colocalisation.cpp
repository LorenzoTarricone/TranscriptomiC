// this object will wrap all functionalities needed to compute the colocalisation matrix

#include "colocalisation.h"


colocalisation::~colocalisation(){
    delete A_distance;
    delete A_linkage;
    delete A_combine;
    delete A_compare;
    delete A_colocalisation;
    delete expression;
}


void colocalisation::compute(){

    // compute colocalisation matrix
    step1();
    std::cout << "[Progress] Step 1 finished successfully ..." << std::endl;
    step2();
    std::cout << "[Progress] Step 2 finished successfully ..." << std::endl;
    step3();
    std::cout << "[Progress] Step 3 finished successfully ..." << std::endl;
    step4();
    std::cout << "[Progress] Step 4 finished successfully ..." << std::endl;
    step5();
    std::cout << "[Progress] Step 5 finished successfully ..." << std::endl;

}


void colocalisation::saveToFile(std::string filename){
    std::cout << "[Progress] Saving File ..." << std::endl;
    expression_raw.writeToFile(filename,*A_colocalisation);
}
