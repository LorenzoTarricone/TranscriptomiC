# :computer: TranscriptomiC++:microscope:

## DESCRIPTION 
This is the repo for the project TranscriptomiC++ in the context of the course CSE201 at École Polytechnique.

The project aims to build a compeletely working open access platform that can be used by biologists to have new insights on their spatial transcriptomics (Slide-Seq) data. In particular, the user will be able to perform two different kind of analysis on these data: ***gene colocalization analysis*** and ***biological process analysis***. More details about the data required and some specific features are described below
<br/><br/>
## INPUT

### TECHNOLOGY
The platform will accept files produced with the following technologies:

- SlideSeq: we will adopt the convention that the rows (indices) indicate the `gene` and the columns will indicate the `beam/barcode`. Each entry of the table will be therefore the level of expression of a certain gene registered on a certain beam

We will soon produce an adaptation of the pipeliine that allows the analysis of Cartana data

### FORMAT
The platform will need the following files in order to perform the analysis correctly. These data are usually provided by the sequencing facility and if they don't match perfectly they can be easily adjusted (usually deleating columns)

- SPATIAL MATRIX: One `.csv` file containing the spatial infomration. This table will have three columns corresponding respectively to: 
  - the nitrogenous bases sequence of the barcode associated to the spot (bead)
  - the row pixel coordinate of the center of the spot in the full resolution image (x coordinate)
  - the column pixel coordinate of the center of the spot in the full resolution image (y coordinate)
- FEATURE: One `.tsv` file containing one column with the names of all the genes (features) that will be included in the matrix file.
- EXPRESSION MATRIX: One `.mtx`file containing the expression matrix for this puck. We will adopt the convention that:
  - The rows correspond to the different genes as specified in the features file just above (the number of rows of this matrix will need therefore to match the lenght of the column of the file just above)
  - The columns corresponding to the different beads as specified by the first column of the first file. (the number of rows of the first file will need to match the number of columns of this matrix file
  
If you want to perform the colocalization matrix analysis:
- FESTURE SUBLIST: One `.tsv` file containing a sublist of genes that the researcher is interested in

If you want to perform the biological process (type 1) analysis:
- GENE IN BIOPROCESS: One `.txt` file that needs to be created in the following way:
  1. Go to https://www.genecards.org/ (genecards website), log in, enter the biological process name you want to study in "Explore a gene" (for example you can enter: "mitochondrion inheritence"). When you have the table, click on "export" and then "show symbols". 
  2. Copy paste the content of the new windows in a txt file and upload it when required by the platform.
<br/><br/>
## ANALYSIS

### FIRST VISAULIZATION 

The first thing resurned is a visualization of the data provided. This allows the user to navigate the the reconstruction of the tissue. The plotted value is the total expression for every single bead, meaning that in posistion `X`, `Y` (as given in the spatial matrix file) the sum over all the rows of the expression matrix is plotted. You will indeed see #beads point plotted with color according to their respective total expression value 

### PREPROCESSING: Filtering/Nomralization/Cropping

In the meanwhile the platform will already start the processing of the data. This has many steps that account for the limits of the technology and the experimental envirionment that we want to filter out. The user has the possibility to modify the metaparameter of this preprocessing. In particular the function inplemented will be the following:

- The FILTER function will by default take the Expression Matrix and eliminate all the genes that are never expressed and in general the genes that are expressed in less than 0.1% of the beams. In the colocalization matrix analysis it will also allow the user the possibility to choose a new percentage. This step is a common procedure and it's also implemented in the ["Seurat" R package](https://nbisweden.github.io/workshop-scRNAseq/labs/compiled/seurat/seurat_07_spatial.html#Filter)

- The NORMALIZATION will take the Expression Matrix (that is supposed to be already filtered) and preform the so called "library size" normalization when we will do the colocalization analysis (for the bioprocess type2 analysis this will not be needed as the function for the EMD performs a sort of normalization itself). As stated in the linked paper ["Normalization of RNA-seq read counts is an essential procedure that corrects for non-biological variation of samples due to library preparation, sequencing read depth, gene length, mapping bias and other technical issues"](https://bmcgenomics.biomedcentral.com/articles/10.1186/s12864-020-6502-7). Our normalization will consist in simply dividing each entry of the expression matrix by the corresponding sum over the rows $\dfrac{E_{i,j}}{\sum\limits_{i}^{}(E_{i,j})}$

- The CROPPING will reduce the size of the Expression and the Spatial matrix down to a specified dimension. This internal function is useful in order to do some tests on a reduced sample.
<br/><br/>
## FUNCTIONALITIES

### COLOCALIZATION MATRIX
This analysis starts from the set of common data required at the beginning and asks in addition a sublist of features (as described in FEATURE SUBLIST in the INPUT section). This sublist is used to specify the subset of genes (features) we are more interested in. Ususally, when one wants to study colocalization between genes. A definition of what is spatial (object-based) colocalization can be found [here](https://imagej.net/imaging/colocalization-analysis). In general we can think about it as the phenomenon for which if gene X and gene Y are colocalized, then finding X in a certain region of spaces means that I'm more likely to find Y in that same region.

Our colocalizaiton algorithm is made of many steps, that are pointed out here:
-**Step 0**: This preprocessing step will allow the user to filter (with custom parameters) and normalize the data. It will also allow the user to upload the list of genes he's interested in. At this step we try to select from the expression matrix only the genes specified in the uploaded file. Whenever a name in the sublist provided is not present in the expression matrix we run it on a database where we look if one of its possible alias is instead included in the matrix. This step is essential to take into account the redoundancy in the gene annotation.

- **Step 1**: This step is simply building a distance matrix between cells $i$ and $j$ , once you have the coordinates it's trivially done with the formula of the Euclidean distance between two points:

$$
d_{i,j} = \sqrt{(x_i - x_j)^2 +(y_i - y_j)^2}
$$
- **Step 2**: Construct the linkage matrix starting by the distance matrix and by substituting each entry $d$ with (where $M$ and $p$ are hyperparameters that can be modified by the user) :

$$
L_{i,j} = (\frac{max(0, M - d_{i,j})}{M})^p 
$$

- **Step 3**: In this step we build the Neighbouring expression matrix as follows. In the column where in the orinal expression matrix we had the expression of the cell $i$ now we insert a linear combination of all the other cells with weight that are the linkage scores $L_{i,j}$. Here the "OldCOlumns" are the ones of the original expression matrix and the "NewColumns" are the ones of the neighbouring expression matrix we want to build
$NewColumn_i = \Sigma OldColumn_j * L_{ij}$

- **Step 4**: Now we want to compare the old columns with the new columns for each cell (for each $i$). As reminder, these columns are all of lenght `len(gene_names)` each entry of this vector represents the expression of the neighbouring expression of a given gene in a given cell. Our target here is to find a suitable function (that we are gonna call Kernel Function), that given two expression levels $expr_i$ and $neigh_i$ returns:
  - an **high** value (or positive, in general) if both the two entries have an high value
  - a **small** value (or negative, in general) if one of the two entries is much larger than the other
  - a value **close to zero** if thwe two entries are small

  This function is not trivial at all and we don't even know if it exists such a fucntion that will always work for us. For the moment my best candidate is the following function, you can try it [here](https://www.geogebra.org/m/ptjn2z2c):

  $$f(x, y) = - α |x - y | + β (x + y)$$
 
This allows you to get a table that is `n_genes` times `n_genes` for each cell in the table and this prodices a final tensor of dimension `n_genes` times `n_genes` times `n_cells`. You finish this step by taking the average along the `n_cells` dimension

- **Step 5**: Now that we have a table `n_genes` times `n_genes` you can do the following transforamtion to find a sort of enrichment score. for each entry of this final table $k, l$ you substitute it with $log_2(\frac{entry_{k,l}}{meanvalueoverrowk})$

We return the result in the form of a matrix that the researcher can explore interactively and download id needed

<br/><br/>

(**REMARK:** In the next section we will talk about "biological processes" but in practice we don't limit ourselves to that, we in fact consider all the possible GO terms (Gene Ontology terms). The biological processes are one of the three main category of these terms, together with "cellular component " and "molecular function"
### BIOLOGICAL PROCESS ANALYSIS (TYPE 1)
This analysis is aimed for those biologists that are interested in the spatial distribution of one particular biological proces. This data exploration tool aims to plot the probability distribution (probability of presence of a certain biological process) over the image. To do that, the user will upload a file with all the genes involved in his desired biological process (following the instruction in the INPUT section) and the probability of presence of the biological process assciated with the list $K$ for the beam $j$ is given by:
$$P = \dfrac{\sum\limits_{i \in K}^{}(E_{i,j})}{\sum\limits_{i}^{}(E_{i,j})}$$

The pipeline will then build a probability and will plot the gradient map.

### BIOLOGICAL PROCESS ANALYSIS (TYPE 2)
The second is for those users that "agnostically" want to see what biological processes are taking places inside the tissue, without looking for any specific one. The user will be able to specify a number `n` of "most important processes" that he wants the analysis to return. The default (and maximum) value is fixed to four.
Our bioprocess2 algorithm is made of many steps, that are pointed out here:

-**Step 0**: This preprocessing step will allow the user to filter the data.

-**Step 1**: We first of all create a distance matrix between the distributions of all the pairs of genes that remain after the filtering using the Wassertain distance. Notice that the expression profiles are two dimensional distribution on a the same support. Solving this problem in dimension two is highly non trivial and some reference to the transportation problem that needs to be solved ca n be found in the respective [Wikipedia page](https://www.wikiwand.com/en/Wasserstein_metric). This is why we decided to adopt a different approact, using the **sliced** Wasserstain distance instead. This is much easier to calculate as it requires to take multiple times the one dimensional Wassertain distance. A detailed description and a proof of the asymptotic convergence of the two measures is given in [this paper](https://arxiv.org/abs/2106.15427).

-**Step 2**: Having a distance matrix we can now cluster the genes according to their relative distances. The clustering algorithm implemented is the PAM algorithm for k Medoids clustering. This is a variation of k-Means clustering which is better suited to cluster data points given their distances rather than their positions in space. We decided to use a variation of K-means over a hierarchical clustering algorithm because of the dimensionality of the dataset as pointed out [here](https://www.geeksforgeeks.org/difference-between-k-means-and-hierarchical-clustering/). We now create a map from the cluster number to the genes inside that cluster 

-**Step 3**: We now use an API to a database to find the most likely biological process linked to the list of genes present in each cluster

-**Step 4**: We plot the n different resuls each one following the procedure described in BIOLOGICAL PROCESS ANALYSIS (TYPE 2)






