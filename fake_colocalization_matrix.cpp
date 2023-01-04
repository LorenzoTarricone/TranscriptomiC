#include "fake_colocalization_matrix.h"
#include <iostream>

fake_colocalization_matrix::fake_colocalization_matrix(MatrixXd m){
    // Test colocalization matrix
      Fake = m;
}

fake_colocalization_matrix::~fake_colocalization_matrix(){}

void fake_colocalization_matrix::setdata(){
    // i is the x coordinate and j is the y coordinate

    int number_rows = Fake.rows();
    int number_cols = Fake.cols();

    for(int i = 0; i < number_rows; i++){
        for(int j = 0; j< number_cols; j++){
            xCoordinates.push_back(i);
            yCoordinates.push_back(j);
            pValues.push_back(Fake(i,j));
        }
    }

}



