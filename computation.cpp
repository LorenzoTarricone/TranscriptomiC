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


    std::cout << "[Progress] Initiating spatial matrix ..." << std::endl;
    A_spatial = spatial.convertToMatrix();

    if(rows <= 0 && cols <= 0){
        std::cout << "Considering the entire expression matrix" << std::endl;
        *expression =  expression_raw.getSparse();
        std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),10)<<std::endl;
        std::cout<<"Expression matrix shape: (" << expression->rows() << ", " << expression->cols() << ")\n"<<std::endl;
        expression_raw.initiateGeneIndex(geneNames);
        return;
    }
    else if(rows <= 0){
        block_rows = expression_raw.getRows()-1;
        block_cols = cols;
        std::cout << "Considering all rows of the expression matrix" << std::endl;


    }
    else if(cols <= 0){
        block_rows = rows;
        block_cols = expression_raw.getCols()-1;
        std::cout << "Considering all columns of the expression matrix" << std::endl;

    }
    else{
        block_rows = rows;
        block_cols = cols;
    }

    std::cout << "crop matrix at block("<<block_rows_start<<","<<block_cols_start<<","<<block_rows<<","<<block_cols<<")"<<std::endl;
    //*expression =  expression_raw.getExpressionDense().block(block_rows_start,block_cols_start,block_rows,block_cols);
    *expression =  expression_raw.getSparse().block(block_rows_start,block_cols_start,block_rows,block_cols);
    std::cout << "crop spatial at block("<<block_rows_start<<","<<block_cols_start<<","<<block_cols<<","<<2<<")"<<std::endl;
    A_spatial=A_spatial.block(block_rows_start,block_cols_start,block_cols,2);


    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),10)<<std::endl;
    std::cout<<"Expression matrix shape: (" << expression->rows() << ", " << expression->cols() << ")\n"<<std::endl;



    std::cout << "[Progress] Initiating cropped gene name index ..." << std::endl;

    expression_raw.initiateGeneIndex_cropped(geneNames,block_rows);
}

void computation::filter_simple(bool zeroes, double min_expr_perc){
    std::cout << "[Progress] Filtering data (simple)..." << std::endl;

    std::cout << "Before filtering: " << std::endl;
    std::cout << "expression matrix size: ("<<(*expression).rows()<<","<<(*expression).cols()<<")"<<std::endl;
    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),10)<<std::endl;


    //filter out sparse rows from the ones we kept before
    std::cout << "[Progress] Filtering sparse rows ..." << std::endl;
    *expression=expression_raw.filter_simple(*expression,zeroes,min_expr_perc);
    std::cout << "After filtering: " << std::endl;
    std::cout << "New expression matrix size: ("<<(*expression).rows()<<","<<(*expression).cols()<<")"<<std::endl;
    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),10)<<std::endl;

}

//function to filter by genes
void computation::filter_genes(){
    std::cout << "[Progress] Filtering data for desired genes..." << std::endl;


    std::cout << "Before filtering: " << std::endl;
    std::cout << "expression matrix size: ("<<(*expression).rows()<<","<<(*expression).cols()<<")"<<std::endl;
    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),10)<<std::endl;


    expression_raw.initiateGeneSubset(geneSubset);

    *expression=expression_raw.filterByGenes(*expression, geneSubset);

    std::cout << "[Progress] Filtering by genes finished"<<std::endl;
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
    expression_raw.writeToFile(filename,*expression,expression_raw.getFinalGenes());
}

std::vector<std::string> computation::getcurrentGenes(){
    return expression_raw.getcurrentGenes();
}
