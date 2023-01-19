#include "biologicalprocess.h"


Eigen::MatrixXd biologicalprocess::compute_total_expression(const Eigen::MatrixXd& expression, const Eigen::MatrixXd& spatial, bool perc){
    std::cout << "[Progress] Calling total expression function ... "<<std::endl;
    int rows = expression.rows();
    int cols = expression.cols();

    std::cout << "Expression matrix of shape ("<<rows<<","<<cols<<") - spatial data of shape ("<<spatial.rows()<<","<<spatial.cols()<<")"<<std::endl;
//    std::cout << spatial.block(0,0,cols,spatial.cols()) << std::endl;
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


//    std::cout << tot << std::endl;

    return tot;
}

void biologicalprocess::compute_tot_expr(){
    std::cout << "[Progress] Simple filter ... "<<std::endl;
    filter_simple(true,0.001);
    std::cout << "[Progress] Simple filter by genes done. "<<std::endl;

    std::cout << "[Progress] Computing total expression ... "<<std::endl;
    total_expression = compute_total_expression(*expression,A_spatial);

    std::cout << "[Progress] Filter by genes ... "<<std::endl;
    filter_genes();
    std::cout << "[Progress] Filter by genes done. "<<std::endl;

    std::cout << "[Progress] Computing expression percentage ... "<<std::endl;
    perc_expression = compute_total_expression(*expression,A_spatial,true);



}

double biologicalprocess::WassersteinDistance(const Eigen::MatrixXd& mat1, const Eigen::MatrixXd& mat2, const Eigen::MatrixXd& distance) {
  // Number of points in each matrix

  std::cout << "Started WassersteinDistance"<<std::endl;

  int n1 = mat1.rows();
  int n2 = mat2.rows();

  // Create sparse matrix for each matrix
  Eigen::MatrixXd A(n1, n2);
  Eigen::MatrixXd B(n1, n2);

  // Fill sparse matrices with weights
  for (int i = 0; i < n1; i++) {
    A.row(i)=distance.row(i)*mat1(i,2);
    B.col(i)=distance.col(i)*mat2(i,2);
  }

  std::cout << "Finished weight initialization, starting linear program"<<std::endl;
  // Solve linear program to find optimal transport plan
  Eigen::VectorXd x(n1 + n2);
  Eigen::VectorXd b(n1 + n2);
  b.head(n1) = Eigen::VectorXd::Ones(n1);
  b.tail(n2) = Eigen::VectorXd::Ones(n2);
  Eigen::SparseMatrix<double> G(n1 + n2, n1 + n2);
  for(int i = 0; i < n1; i++)
    G.insert(i,i) = 1;
  for(int i = n1; i < n1 + n2; i++)
    G.insert(i,i) = -1;
  Eigen::VectorXd c(n1 + n2);
  c.head(n1) = A * Eigen::VectorXd::Ones(n2);
  c.tail(n2) = B.transpose() * Eigen::VectorXd::Ones(n1);
  Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>> solver;
  solver.compute(G.transpose() * G);
  x = solver.solve(G.transpose() * c);

  // Compute Wasserstein distance
  std::cout << "finished linear program"<<std::endl;
  return x.dot(c);
}

Eigen::MatrixXd biologicalprocess::EMD_Matrix(const Eigen::MatrixXd& expression, const Eigen::MatrixXd& spatial){

    Eigen::MatrixXd EMD = Eigen::MatrixXd::Zero(expression.rows(),expression.rows());
    Eigen::MatrixXd distance(expression.cols(),expression.cols());

    for (int i = 0; i < expression.cols(); i++) {
      for (int j = 0; j < expression.cols(); j++) {
        distance(i,j) = sqrt(pow(spatial(i, 0) - spatial(j, 0), 2) + pow(spatial(i, 1) - spatial(j, 1), 2));
      }
    }

    for(int gene1=0;gene1<expression.rows()-1;gene1++){
        for(int gene2=gene1+1;gene2<expression.rows();gene2++){
            std::cout << "Looping through gene1: "<<gene1<<" and gene2: "<<gene2<<std::endl;
            Eigen::MatrixXd coords1(expression.cols(),3);
            Eigen::MatrixXd coords2(expression.cols(),3);

            std::cout << "[Progress] coords1 computed with size ("<<coords1.rows()<<","<<coords1.cols()<<")"<<std::endl;
            std::cout << "[Progress] spatial size: ("<<spatial.rows()<<","<<spatial.cols()<<")"<<std::endl;

            coords1.col(0)=spatial.col(0);
            coords2.col(0)=spatial.col(0);
            coords1.col(1)=spatial.col(1);
            coords2.col(1)=spatial.col(1);

            coords1.col(2)=expression.row(gene1);
            coords2.col(2)=expression.row(gene2);


            double value=WassersteinDistance(coords1,coords2, distance);
            std::cout << "Wass distance:"<< value <<std::endl;
            EMD(gene1,gene2)=value;
            EMD(gene2,gene1)=value;
        }
    }

    return EMD;

}

std::map<int, std::vector<std::string>> biologicalprocess::Cluster(Eigen::MatrixXd& EMD, int n){
    std::map<int, std::vector<std::string>> clusters_dict;
    int numPoints = EMD.rows();
    Eigen::VectorXi clusters = Eigen::VectorXi::LinSpaced(numPoints, 0, numPoints-1); // Initialize each data point to its own cluster
    std::cout<<"started Clustering"<<std::endl;
    int index = 0;
    while (clusters.maxCoeff()+1 > n) { // Repeat until number of clusters is less than or equal to n
        std::cout << "clusters.maxCoeff() = "<< clusters.maxCoeff() << std::endl;
        std::cout << "index: " << index << std::endl;
        // Find the two closest clusters
        int minRow, minCol;
        EMD.minCoeff(&minRow, &minCol);
        if (minRow > minCol) std::swap(minRow, minCol);

        // Merge the two closest clusters
        for (int i = 0; i < numPoints; i++) {
            if (clusters(i) == minCol) {
                clusters(i) = minRow;
             }else if (clusters(i) > minCol) {
                clusters(i)--;
             }
        }

        // Update the distance matrix
        EMD.block(minRow, minCol, 1, EMD.cols()-minCol) = EMD.block(minCol, minCol, 1, EMD.cols()-minCol);
        EMD.block(minRow, minCol+1, EMD.rows()-minCol-1, 1) = EMD.block(minCol+1, minCol, EMD.rows()-minCol-1, 1);
        EMD.conservativeResize(numPoints-1, numPoints-1);

        index++;
     }

    std::cout<<"finished clustering, got clusters: \n"<<clusters<<std::endl;

    std::vector<std::string> currentGenes=getcurrentGenes();

    std::cout << "Current genes are: [";
    for(int i = 0; i < currentGenes.size()-1; i++){
    std::cout << currentGenes[i] << ",";
    }
    std::cout << currentGenes[currentGenes.size()-1] << "]" << std::endl;


    for(int i=0;i<clusters.size();i++){
        int current_cluster=clusters[i];
        clusters_dict[current_cluster].push_back(currentGenes[i]);
    }

}

void biologicalprocess::bioprocess_2(int n){
    std::cout << "[Progress] Computing EMD Matrix ... "<<std::endl;
    Eigen::MatrixXd EMD_Mat = EMD_Matrix(*expression,A_spatial);
    std::map<int, std::vector<std::string>> clusters=Cluster(EMD_Mat,n);

    std::cout << "[Progress] EMD Matrix computed with size ("<<EMD_Mat.rows()<<","<<EMD_Mat.cols()<<")"<<std::endl;
    std::cout << "EMD Matrix:\n "<<EMD_Mat.block(0,0,10,10)<<std::endl;
}
