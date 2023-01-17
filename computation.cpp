#include "computation.h"


computation::computation(parsefile files,int rows, int cols){
    expression_raw = files.getExpression();
    spatial = files.getSpatial();
    geneNames = files.getGenes();
    block_rows_start = 0;
    block_cols_start = 0;
    block_rows = 0;
    block_cols = 0;
    initialise(rows, cols);
}

void computation::initialise(int rows, int cols){
    // this method for now contains anything in the readFiles method that is not handled by the
    // parsefile object
    // set default cropping to dimensions of the matrix

    std::cout << "[Progress] Extracting expression matrix ..." << std::endl;
    expression = new Eigen::MatrixXd;

    if(rows <= 0 || cols <= 0){
        block_rows = expression_raw.getRows();
        block_cols = expression_raw.getCols();

        *expression =  expression_raw.getExpressionDense();
    }
    else{
        block_rows = rows;
        block_cols = cols;
        std::cout << "crop matrix at block("<<block_rows_start<<","<<block_cols_start<<","<<block_rows<<","<<block_cols<<")"<<std::endl;
        *expression =  expression_raw.getExpressionDense().block(block_rows_start,block_cols_start,block_rows,block_cols);

    }



    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),10)<<std::endl;
    std::cout<<"Expression matrix shape: (" << expression->rows() << ", " << expression->cols() << ")\n"<<std::endl;

    std::cout << "[Progress] Initiating spatial matrix ..." << std::endl;
    A_spatial = spatial.convertToMatrix();

//    std::cout << "[Progress] Initiating gene name index ..." << std::endl;
//    expression_raw.initiateGeneIndex(geneNames);
}

void computation::filter(bool zeroes, bool filterGenes, double min_expr_perc){
    std::cout << "[Progress] Filtering data ..." << std::endl;
//    std::cout << "Before filtering: " << std::endl;
//    std::cout<<expression->block(0,0,10,10)<<std::endl;
//    Eigen::MatrixXd* temp = new Eigen::MatrixXd;
//    temp = expression;

    std::cout << "Before filtering: " << std::endl;
    std::cout << "expression matrix size: ("<<(*expression).rows()<<","<<(*expression).cols()<<")"<<std::endl;
    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),10)<<std::endl;


    if(filterGenes){
        //keep only desired genes
        std::cout << "[Progress] Filtering data for desired genes ..." << std::endl;

        std::cout << "[Progress] Initializing gene index ..." << std::endl;

        expression_raw.initiateGeneIndex(geneNames,geneSubset);

        *expression=expression_raw.filterByGenes(*expression, geneSubset);

        std::cout << "[Progress] Filtering by genes finished"<<std::endl;
        std::cout << "New expression matrix size: ("<<(*expression).rows()<<","<<(*expression).cols()<<")"<<std::endl;
        std::cout <<expression->block(0,0,20,20)<<std::endl;

    }
    else{
        // initialize gene index
        std::cout << "[Progress] Filtering without gene list ..." << std::endl;
        std::cout << "[Progress] Initializing gene index ..." << std::endl;
        expression_raw.initiateGeneIndex(geneNames);
    }


    //filter out sparse rows from the ones we kept before
    std::cout << "[Progress] Filtering sparse rows ..." << std::endl;
    expression_raw.filter_simple(*expression,zeroes,filterGenes,min_expr_perc);
//    delete temp;
    std::cout << "After filtering: " << std::endl;
    std::cout << "New expression matrix size: ("<<(*expression).rows()<<","<<(*expression).cols()<<")"<<std::endl;
    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),10)<<std::endl;
}




void computation::normalisation(std::string type_of_normal){
    std::cout << "[Progress] Normalising data according to " << type_of_normal << " ..." << std::endl;

    std::cout << "Before normalisation: " << std::endl;
    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),std::min(10,(int) expression->cols()))<<std::endl;

    *expression = expression_raw.normalisation_simple(*expression);

    std::cout << "[Progress] Normalising data according to " << type_of_normal << " finished ..." << std::endl;
    std::cout << "After normalisation: " << std::endl;
    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),std::min(10,(int) expression->cols()))<<std::endl;
}



void computation::addGeneList(std::string geneListPath){
    geneSubset = listgene(geneListPath);
}


void computation::saveToFile(std::string filename){
    std::cout << "[Progress] Saving File ..." << std::endl;
    expression_raw.writeToFile(filename,*expression);
}
