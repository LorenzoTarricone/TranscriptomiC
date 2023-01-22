#include "computation.h"
// base class for biologicalprocess and colocalisation

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

// this method deals with extracting the actual matrices from their storage/computation objects

void computation::initialise(int rows, int cols){
    // this method for now contains anything in the readFiles method that is not handled by the
    // parsefile object
    // set default cropping to dimensions of the matrix

    std::cout << "[Progress] Extracting expression matrix ..." << std::endl;
    expression = new Eigen::MatrixXd;


    std::cout << "[Progress] Initiating spatial matrix ..." << std::endl;
    A_spatial = spatial.convertToMatrix();

    // 0 is the default value and signifies the inclusion of all rows or columns
    if(rows <= 0 && cols <= 0){
        std::cout << "Considering the entire expression matrix" << std::endl;
        *expression =  expression_raw.getSparse();
        std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),10)<<std::endl;
        std::cout<<"Expression matrix shape: (" << expression->rows() << ", " << expression->cols() << ")\n"<<std::endl;
        // initiate gene index from gene name file
        expression_raw.initiateGeneIndex(geneNames);
        return;
    }
    else if(rows <= 0){
        block_rows = expression_raw.getRows()-1;
        block_cols = cols;
        std::cout << "Considering all rows of the expression matrix" << std::endl;
        expression_raw.initiateGeneIndex(geneNames);

    }
    else if(cols <= 0){
        block_rows = rows;
        block_cols = expression_raw.getCols()-1;
        std::cout << "Considering all columns of the expression matrix" << std::endl;
        expression_raw.initiateGeneIndex_cropped(geneNames,block_rows);
    }
    else{
        block_rows = rows;
        block_cols = cols;
        // initiate gene index from gene name file in the case of not including all rows
        // (not all genes from the gene name file have to be initiated)
        expression_raw.initiateGeneIndex_cropped(geneNames,block_rows);
    }

    std::cout << "crop matrix at block("<<block_rows_start<<","<<block_cols_start<<","<<block_rows<<","<<block_cols<<")"<<std::endl;
    *expression =  expression_raw.getSparse().block(block_rows_start,block_cols_start,block_rows,block_cols);
    std::cout << "crop spatial at block("<<block_rows_start<<","<<block_cols_start<<","<<block_cols<<","<<2<<")"<<std::endl;
    A_spatial=A_spatial.block(block_rows_start,block_cols_start,block_cols,2);


    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),10)<<std::endl;
    std::cout<<"Expression matrix shape: (" << expression->rows() << ", " << expression->cols() << ")\n"<<std::endl;



    std::cout << "[Progress] Initiating cropped gene name index ..." << std::endl;
}

// filter: remove genes that are never expressed (all-zero rows) or expressed in under min_expr_perc
// of cases
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


// perform library normalisation
void computation::normalisation(std::string type_of_normal){
    std::cout << "[Progress] Normalising data according to " << type_of_normal << " ..." << std::endl;

    std::cout << "Before normalisation: " << std::endl;
    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),std::min(10,(int) expression->cols()))<<std::endl;

    *expression = expression_raw.normalisation_simple(*expression);

    std::cout << "[Progress] Normalising data according to " << type_of_normal << " finished ..." << std::endl;
    std::cout << "After normalisation: " << std::endl;
    std::cout<<expression->block(0,0,std::min(10,(int) expression->rows()),std::min(10,(int) expression->cols()))<<std::endl;
}

// add gene subset to filter by
void computation::addGeneList(std::vector<std::string> geneList){
    std::cout << "[Progress] Adding gene subset ..." << std::endl;
    geneSubset = geneList;
    std::cout << "[Progress] Subset added ..." << std::endl;

}

// add gene subset to filter by (overloaded)
void computation::addGeneList(std::string geneListPath){
    addGeneList(listgene(geneListPath));
}

// save expression matrix to file (overloaded in colocalisation)
void computation::saveToFile(std::string filename){
    std::cout << "[Progress] Saving File ..." << std::endl;
    expression_raw.writeToFile(filename,*expression,expression_raw.getcurrentGenes());
}

// get genes that currently remain in the matrix
std::vector<std::string> computation::getcurrentGenes(){
    return expression_raw.getcurrentGenes();
}

// compute either column sum (how many genes are expressed where in the tissue)
// or compute expression percentage of a subset
Eigen::MatrixXd computation::compute_total_expression(const Eigen::MatrixXd& expression, const Eigen::MatrixXd& spatial, bool perc){
    std::cout << "[Progress] Calling total expression function ... "<<std::endl;
    int rows = expression.rows();
    int cols = expression.cols();

    std::cout << "Expression matrix of shape ("<<rows<<","<<cols<<") - spatial data of shape ("<<spatial.rows()<<","<<spatial.cols()<<")"<<std::endl;
    Eigen::MatrixXd tot = Eigen::MatrixXd(cols,3);




    // initialize last column to 0
    for(int j = 0; j < tot.rows(); j++){
        tot(j,2) = (double) 0;
    }

    std::cout << spatial.block(0,0,std::min(20,(int) spatial.rows()),spatial.cols()) << std::endl;

    for(int j = 0; j < spatial.rows(); j++){
        for(int i = 0; i < expression.rows(); i++){
            tot(j,0) = spatial(j,0);
            tot(j,1) = spatial(j,1);
            if(perc && (total_expression(j,2) != 0)){
                tot(j,2) += (double) (expression(i,j)/total_expression(j,2));
            }
            else{
                tot(j,2) += (double) expression(i,j);
            }

        }
    }

    std::cout << "total expression data of shape ("<<tot.rows()<<","<<tot.cols()<<")"<<std::endl;

    return tot;
}

const parsemtx &computation::getExpression_raw() const
{
    return expression_raw;
}



Eigen::MatrixXd computation::compute_tot_expr(){
    std::cout << "[Progress] Simple filter ... "<<std::endl;
    filter_simple(true,0.001);
    std::cout << "[Progress] Simple filter by genes done. "<<std::endl;

    std::cout << "[Progress] Computing total expression ... "<<std::endl;

    Eigen::MatrixXd tot_exp = compute_total_expression(*expression,A_spatial);

    std::cout << tot_exp << std::endl;

    return tot_exp;


}
