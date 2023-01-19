#include "colocalisation.h"
#include "colocalization_matrix.h"



//void colocalisation::step1(){
//    std::cout << "[Progress] Running step 1 ..." << std::endl;
//    A_distance = new Eigen::MatrixXd;
//    *A_distance = matrix_distance(A_spatial.block(block_rows_start,0,block_cols,2));
//}

//void colocalisation::step2(){
//    // step 2 - linkage matrix with parameters m and p
//    std::cout << "[Progress] Running step 2 ..." << std::endl;
//    A_linkage = new Eigen::MatrixXd;
//    *A_linkage = matrix_linkage(*A_distance, m, p);

//    delete A_distance;

//    std::cout<<(*A_linkage).block(0,0,10,10)<<std::endl;
//    std::cout<<"\nLinkage matrix shape: (" << (*A_linkage).rows() << ", " << (*A_linkage).cols() << ")"<<std::endl;

//}

//void colocalisation::step3(){
//    //  step 3 - apply linkage to expression matrix -> neighbouring matrix
//    std::cout << "[Progress] Running step 3 ..." << std::endl;


//    A_combine = new Eigen::MatrixXd;
//    *A_combine = combine_linkage(*A_linkage,*expression);

//    delete A_linkage;

//    std::cout<<A_combine->block(0,0,10,10)<<std::endl;
//    std::cout<<"\n Comparison matrix shape: (" << A_combine->rows() << ", " << A_combine->cols() << ")"<<std::endl;
//}

//void colocalisation::step4(){
//    //  step 4 - compare expression and neighbouring matrices (with default parameters
//    std::cout << "[Progress] Running step 4 ..." << std::endl;
//    A_compare = new Eigen::MatrixXd;
//    *A_compare = comparison_old(*expression, *A_combine);

//    std::cout<<A_compare->block(0,0,10,10)<<std::endl;
//    std::cout<<"\n Comparison matrix shape: (" << A_compare->rows() << ", " << A_compare->cols() << ")"<<std::endl;


//    delete A_combine;
//}

//void colocalisation::step5(){
//    std::cout << "[Progress] Running step 5 ..." << std::endl;
//    A_colocalisation = new Eigen::MatrixXd;
//    *A_colocalisation = enrichment(*A_compare);

//    std::cout<<A_colocalisation->block(0,0,10,10)<<std::endl;
//    std::cout<<"\n Colocalisation matrix shape: (" << A_colocalisation->rows() << ", " << A_colocalisation->cols() << ")"<<std::endl;

//}
