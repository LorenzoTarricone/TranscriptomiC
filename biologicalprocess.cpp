#include "biologicalprocess.h"
#include "float.h"
#include "wasserstein.h"
#include <time.h>



// this function computes the ratio of total expression before and after filtering
// by a given list of genes
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

    std::cout << perc_expression << std::endl;

}

const Eigen::MatrixXd &biologicalprocess::getPerc_expression() const
{
    return perc_expression;
}

//This function computes the "Sliced" Wasserstein distance between two genes: it runs
//n_computations times and takes the average distance. Each iteration performs a
//projection of the spatial data on some random plane, from which we can then
//compute a 1-dimensional Wasserstein distance. Large n_computations would lead to better results
//but also much longer runtimes.
double biologicalprocess::Wass_distance(Eigen::MatrixXd& Coord_mat, Eigen::MatrixXd& Express_mat, int gene_1, int gene_2, int n_computations){


    std::vector<double> First_expr(Express_mat.cols());
    for(int i = 0; i < Express_mat.cols(); i++)
    {
       //this will put all the elements in the first column of Eigen::Matrix into the column3 vector
        First_expr.at(i) = Express_mat(gene_1, i);
    }



    std::vector<double> Second_expr(Express_mat.cols());
    for(int j = 0; j < Express_mat.cols(); j++)
    {
       //this will put all the elements in the first column of Eigen::Matrix into the column3 vector
        Second_expr.at(j) = Express_mat(gene_2, j);
    }

    //Calculte random direction Wass dist

    std::vector<double> All_dists(n_computations);

    for(int timer = 0; timer < n_computations; timer ++){


        double value1 = (double) rand()/RAND_MAX;
        double value2 = sqrt(1 - (value1 * value1));


        std::vector<double> Proj_coord(Coord_mat.rows());

        for( int i = 0; i < Coord_mat.cols(); i++){
            Proj_coord.at(i) = Coord_mat(i, 0) * value1 + Coord_mat(i, 1) * value2;
        }

         double dist = wasserstein(Proj_coord,First_expr,Proj_coord,Second_expr);
         All_dists.push_back(dist);

    }

    double avg = std::reduce(All_dists.begin(), All_dists.end()) / n_computations;


    return avg;
}



//This function is responsible for computing the Wasserstein distance matrix
Eigen::MatrixXd biologicalprocess::Wass_Matrix(Eigen::MatrixXd& Coord_mat, Eigen::MatrixXd& Express_mat, int n_compute){

    Eigen::MatrixXd EMD = Eigen::MatrixXd::Zero(Express_mat.rows(),Express_mat.rows());

    for (int gene_1 = 0; gene_1 < Express_mat.rows() - 1; gene_1++){
        for(int gene_2 = gene_1 + 1; gene_2 < Express_mat.rows(); gene_2++){

            double value=Wass_distance(Coord_mat, Express_mat, gene_1, gene_2, n_compute);
            std::cout << "Wass distance:"<< value <<std::endl;
            EMD(gene_1,gene_2)=value;
            EMD(gene_2,gene_1)=value;
        }
    }


    return EMD;
}


//This function helps us when assigning the nearest medoid (cluster center) to each point.
int biologicalprocess::findNearestMedoid(Eigen::MatrixXd distanceMatrix, std::vector<int> medoids, int point) {
    int nearestMedoid = -1;
    double minDistance = DBL_MAX;

    for (int i=0;i<medoids.size();i++) {
        double distance = distanceMatrix(point, medoids[i]);
        if (distance < minDistance) {
            nearestMedoid = i;
            minDistance = distance;
        }
    }

    return nearestMedoid;
}

//This function, given a distance matrix (in our case it will be the Wasserstein distance matrix),
//performs clustering through an implementation of the PAM algorithm for k Medoids clustering. This is
//a variation of k-Means clustering which is better suited to cluster data points given their distances
//rather than their positions in space.
std::vector<std::string> biologicalprocess::kMedoidsClustering(Eigen::MatrixXd distanceMatrix, int k, int num_runs) {
    std::vector<std::string> clusters_dict(k);
    double bestCost = DBL_MAX;
    std::vector<std::vector<int>> best_clusters(k);
    int n = distanceMatrix.rows();


    std::cout<<"started Clustering"<<std::endl;
    for(int run=0;run<num_runs;run++){
        std::cout<<"started run number "<<run<<std::endl;
        std::vector<int> medoids(k);
        std::vector<std::vector<int>> clusters(k);
        // randomly select initial medoids
        for (int i = 0; i < k; i++) {
            int random = rand()%n;
            while (std::find(medoids.begin(), medoids.end(), random) != medoids.end()) {
                random = rand()%n;
            }
            medoids[i] = random;
        }
        bool changed;
        do {
            std::cout<<"iterating again"<<std::endl;
            changed = false;

            // assign each point to the nearest medoid
            for (int i = 0; i < n; i++) {
                int nearestMedoid = findNearestMedoid(distanceMatrix, medoids, i);
                clusters[nearestMedoid].push_back(i);
            }

            // try to improve the solution by swapping medoids
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < n; j++) {
                    if (std::find(medoids.begin(), medoids.end(), j) == medoids.end()) {
                        int oldMedoid = medoids[i];
                        double oldCost = 0;
                        for (int point : clusters[i]) {
                            oldCost += distanceMatrix(point, oldMedoid);
                        }

                        medoids[i] = j;
                        double newCost = 0;
                        for (int point : clusters[i]) {
                            newCost += distanceMatrix(point, j);
                        }

                        if (newCost >= oldCost) {
                            medoids[i] = oldMedoid;
                        } else {
                            changed = true;
                        }
                    }
                }
            }
            // clear the clusters
            if(changed){
                for (int i = 0; i < k; i++) {
                    clusters[i].clear();
                }
            }


        } while (changed);
        //calculate cost of this clustering solution
        double cost = 0;
        for (int i = 0; i < k; i++) {
            for (int point : clusters[i]) {
                cost += distanceMatrix(point, medoids[i]);
            }
        }
        // check if this clustering solution is the best so far
        if (cost < bestCost) {
            bestCost = cost;
            best_clusters=clusters;
        }
    }
    std::cout << "Finished clustering, got clusters: "<<std::endl;
    for(int i = 0; i < best_clusters.size(); i++){
        for(int j=0;j<best_clusters[i].size();j++){
            std::cout<<"cluster "<<i<<" with gene: "<<best_clusters[i][j]<<std::endl;
        }
    }
    std::vector<std::string> currentGenes=getcurrentGenes();

    std::cout << "Current genes are: [";
    for(int i = 0; i < currentGenes.size()-1; i++){
    std::cout << currentGenes[i] << ",";
    }
    std::cout << currentGenes[currentGenes.size()-1] << "]" << std::endl;


    //We wish to return a vector of strings, where each entry of the vector represents
    //the list of genes belonging to a cluster. Each string will be of the type "gene1,gene2,gene3,...,geneN"
    //if there are N genes in the associated cluster. We chose this formatting in order to pass the output directly
    //to the API, which can then find the biological processes most closely associated to each cluster of genes.
    for(int i=0;i<best_clusters.size();i++){
        std::vector<int> current_cluster=best_clusters[i];
        if(current_cluster.size()>0){
            for(int j=0;j<current_cluster.size()-1;j++){
                std::string current_string=currentGenes[current_cluster[j]];
                clusters_dict[i]+=(current_string+",");
            }
            clusters_dict[i]+=currentGenes[current_cluster[current_cluster.size()-1]];
        }else{
            clusters_dict[i]+="empty";
        }
    }

    return clusters_dict;
}


//This function executes the second biological process analysis, which involves the clustering of genes.
//First, it computes an Earth Mover Distance matrix so that we have a measure of "distance" between genes,
//which can then be clustered.
std::vector<std::string> biologicalprocess::bioprocess_2(int n, int num_runs){
    //set a random seed
    std::srand(time(NULL));
    std::cout << "[Progress] Computing EMD Matrix ... "<<std::endl;
    Eigen::MatrixXd EMD_Mat = Wass_Matrix(A_spatial, *expression,3);

    std::cout << "[Progress] EMD Matrix computed with size ("<<EMD_Mat.rows()<<","<<EMD_Mat.cols()<<")"<<std::endl;
    std::cout << "EMD Matrix:\n "<<EMD_Mat.block(0,0,std::min((int) EMD_Mat.rows(),10),std::min((int) EMD_Mat.cols(),10))<<std::endl;
    std::vector<std::string> clusters_dict=kMedoidsClustering(EMD_Mat,n, num_runs);

    std::cout << "Finished bioprocess 2, got clusters: "<<std::endl;
    for(int i = 0; i < clusters_dict.size(); i++){
        std::cout<<"cluster "<<i<<" with genes: "<<clusters_dict[i]<<std::endl;
    }

    return clusters_dict;

}

// helper function that splits a comma separated string into a vector
std::vector<std::string> split(std::string text, char delim) {
    std::string line;
    std::vector<std::string> vec;
    std::stringstream ss(text);
    while(std::getline(ss, line, delim)) {
        vec.push_back(line);
    }
    return vec;
}

// helper function which is used to convert the output clusters into vectors of strings
// these can then be used to filter the data and thus compute the expression of each gene
// wrt to a biological process
std::vector<std::vector<std::string>> biologicalprocess::plottable(std::vector<std::string> cluster_dict){
    std::vector<std::vector<std::string>> clusters;
    for(std::string i : cluster_dict){
        clusters.push_back(split(i,','));
    }
    return clusters;
}
