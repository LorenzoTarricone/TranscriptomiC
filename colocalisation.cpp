// this object will wrap all functionalities needed to compute the colocalisation matrix

#include "colocalisation.h"


colocalisation::colocalisation(parsefile files, int rows, int cols)
{
    expression_raw = files.getExpression();
    spatial = files.getSpatial();
    geneNames = files.getGenes();
    block_rows_start = 0;
    block_cols_start = 0;
    block_rows = 0;
    block_cols = 0;
    initialise(rows, cols);

}

colocalisation::~colocalisation(){
    delete A_distance;
    delete A_linkage;
    delete A_combine;
    delete A_compare;
    delete A_colocalisation;
    delete expression;
}

void colocalisation::initialise(int rows, int cols){
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



//this function applies the filtering by gene names and then
//filters out rows which either have only zeros (if zeroes==true)
//or if their expression percentage is below min_expr_perc
void colocalisation::filter(bool zeroes, double min_expr_perc){
    std::cout << "[Progress] Filtering data ..." << std::endl;
//    std::cout << "Before filtering: " << std::endl;
//    std::cout<<expression->block(0,0,10,10)<<std::endl;
//    Eigen::MatrixXd* temp = new Eigen::MatrixXd;
//    temp = expression;

    //keep only desired genes
    *expression=expression_raw.filterByGenes(*expression, geneSubset);

    std::cout << "[Progress] Filtering by genes finished"<<std::endl;
    std::cout << "New expression matrix size: ("<<(*expression).rows()<<","<<(*expression).cols()<<")"<<std::endl;
    std::cout <<expression->block(0,0,20,20)<<std::endl;

    //filter out sparse rows from the ones we kept before
    expression_raw.filter_simple(*expression,zeroes,min_expr_perc);
//    delete temp;
    std::cout << "After filtering: " << std::endl;
    std::cout << "New expression matrix size: ("<<(*expression).rows()<<","<<(*expression).cols()<<")"<<std::endl;
    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),10)<<std::endl;
}

void colocalisation::normalisation(std::string type_of_normal){
    std::cout << "[Progress] Normalising data according to " << type_of_normal << " ..." << std::endl;
    std::cout << "Before normalisation: " << std::endl;
    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),std::min(10,(int) expression->cols()))<<std::endl;
    *expression = expression_raw.normalisation_simple(*expression);
    std::cout << "[Progress] Normalising data according to " << type_of_normal << " finished ..." << std::endl;
    std::cout << "After normalisation: " << std::endl;
    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),std::min(10,(int) expression->cols()))<<std::endl;
}

void colocalisation::readFiles(std::string expressionFile, std::string spatialFile, std::string geneNameFile, std::string geneSubsetFile){
    // read beams and spatial information into parsing object
    spatial = parsing();
    std::cout << "[Progress] Reading spatial data ..." << std::endl;
    spatial.readBeamFileCSV(spatialFile);

    // convert object to eigen matrix
    std::cout << "[Progress] Converting spatial file to matrix ..." << std::endl;
    A_spatial = spatial.convertToMatrix();

    // read expression matrix
    expression_raw = parsemtx();
    std::cout << "[Progress] Reading expression matrix ..." << std::endl;
    expression_raw.readFile(expressionFile);
    std::cout << "[Progress] Finished reading expression matrix" << std::endl;

    // set default cropping to dimensions of the matrix
    if(def){
        block_rows = expression_raw.getRows();
        block_cols = expression_raw.getCols();
    }

    // read gene name file
    std::cout << "[Progress] Reading gene names file ..." << std::endl;
    geneNames = listgene(geneNameFile);


    // read gene subset files

    std::cout << "[Progress] Reading gene names file ..." << std::endl;
    geneSubset = listgene(geneSubsetFile);

    std::cout << "[Progress] Initiating gene name index ..." << std::endl;
    expression_raw.initiateGeneIndex(geneNames, geneSubset);

    std::cout << "[Progress] File reading finished successfully ..." << std::endl;

    std::cout << "[Progress] Extracting expression matrix ..." << std::endl;

    std::cout << "crop matrix at block("<<block_rows_start<<","<<block_cols_start<<","<<block_rows<<","<<block_cols<<")"<<std::endl;
    expression = new Eigen::MatrixXd;
    *expression =  expression_raw.getExpressionDense().block(block_rows_start,block_cols_start,block_rows,block_cols);


    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),10)<<std::endl;
    std::cout<<"Expression matrix shape: (" << expression->rows() << ", " << expression->cols() << ")\n"<<std::endl;

}


void colocalisation::setMatrixBlocks(int startRow, int startCol, int endRow, int endCol){
    block_rows_start = startRow;
    block_rows = endRow;
    block_cols_start = startCol;
    block_cols = endCol;

    std::cout << "crop matrix at block("<<block_rows_start<<","<<block_cols_start<<","<<block_rows<<","<<block_cols<<")"<<std::endl;
    *expression =  expression_raw.getExpressionDense().block(block_rows_start,block_cols_start,block_rows,block_cols);



    def = false;
}

void colocalisation::setMatrixBlocks(int endRow, int endCol){
    setMatrixBlocks(0, 0, endRow, endCol);
}

void colocalisation::test(bool def){
    std::cout << "call to funtion test " << std::endl;
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
