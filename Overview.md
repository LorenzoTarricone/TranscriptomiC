Here I provide an explicit decription of the problem and the idea behing this algorithm. If anything is not **crystal clear** please tell me so that I can rephrase/add some more details. 

###Introduction: why are we interest in a colocalization table?
Biologists are interested in this kind of table because they want to be able to assess if two genes express themselves in the same parts of the tissue. They are in general interested in the relation and dependencies between genes (what happens to the other if I "turn off" one of them?), but it have been proven that the space organization is also fundamental. 

###Input: where do we start?
From the user we first of all get the data about the transcriptomic. These are the data that come out from the sequencing facility and that we will use as basis for our analysis

- Expression matrix: This matrix is the biggest one and has `n_genes` rows, `n_cells` columns. Each entry of the table is saying: "how many times the transcript X (a certain row) has been found in the cell Y (a certain column)?"
- Location matrix: this has dimension `n_cells` rows times 3 columns (name of the cell, x coordinate, y coordinate). This is what contains the spatial location of each of the cells in the first matrix. For each cell it's telling you where this cell is located inside the tissue 

On top of this we also may have some data from the input telling us what are the genes our researcher is interested in, that in this code are called `gene_names`. This allow us to resctrict our attention to just this list of genes and discard all the others (we pass from 23k genes to around 300) a major imporvement in terms of computational resources. 

###Our algorithm: a general idea
The general idea of the algorithm we are developing is the one of trying to build an expression matrix but not for the single cells but of the neighbors of the single cells. Once we do that we want to see how much this new table and the original table we got are similar entry-wise. To do that we make use of a sort of "kernel function" that needs to be establish and that I will explain later.


###Our algorithm: the steps 
- **Step 1**: This step is simply building a distance matrix between cells $i$ and $j$ , once you have the coordinates it's trivially done with the formula of the Euclidean distance between two points:

$$
d_{i,j} = \sqrt{(x_i - x_j)^2 +(y_i - y_j)^2}
$$
- **Step 2**: Construct the linkage matrix starting by the distance matrix and by substituting each entry $d$ with (where $M$ and $p$ are hyperparameters) :

$$
L_{i,j} = (\frac{max(0, M - d_{i,j})}{M})^p 
$$

- **Step 3**: In this step we build the Neighbouring expression matrix as follows. In the column where in the orinal expression matrix we had the expression of the cell $i$ now we insert a linear combination of all the other cells with weight that are the linkage scores $L_{i,j}$. Here the "OldCOlumns" are the ones of the original expression matrix and the "NewColumns" are the ones of the neighbouring expression matrix we want to build
$$
NewColumn_i = \Sigma OldColumn_j * L_{ij}
$$

- **Step 4**: Now we want to compare the old columns with the new columns for each cell (for each $i$). As reminder, these columns are all of lenght `len(gene_names)` each entry of this vector represents the expression of the neighbouring expression of a given gene in a given cell. Our target here is to find a suitable function (that we are gonna call Kernel Function), that given two expression levels $expr_i$ and $neigh_i$ returns:
  - an **high** value (or positive, in general) if both the two entries have an high value
  - a **small** value (or negative, in general) if one of the two entries is much larger than the other
  - a value **close to zero** if thwe two entries are small

  This function is not trivial at all and we don't even know if it exists such a fucntion that will always work for us. For the moment my best candidate is the following function, you can try to plot it on geogebra:

  $$
  f(x, y) = - α |x - y | + β (x + y)
  $$

Please try to think of this function and expreriment with it. This allows you to get a table that is `n_genes` times `n_genes` for each cell in the table and this prodices a final tensor of dimension `n_genes` times `n_genes` times `n_cells`. You finish this step by taking the average along the `n_cells` dimension
- **Step 5**: now that we have a table `n_genes` times `n_genes` you can do the following transforamtion to find a sort of enrichment score. for each entry of this final table $k, l$ you substitute it with $$log_2(\frac{entry_{k,l}}{meanvalueoverrowk})$$

Also here there are some non clear issues on how to deal with the zero values that become minus infinity 
