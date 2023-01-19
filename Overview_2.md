# Overview_2

## Intro

This second overview file deals with the algorithm and the workflow for the second kind of analysis offered the platform, the so called "biological processes analysis*. There will basically be two kinds of such analyses. The first one is for those users who want to see where a biological process of their interest il located inside the tissue. The second is for those users that "agnostically" want to see what biological processes are taki places inside the tissue, without looking for any specific one.

Note: here we talk about "biological processes" but in practice we don't limit ourselves to that, we in fact consider all the possible GO terms (Gene Ontology terms). The biological processes are one of the three main category of these terms, together with "cellular product " and "__"

## First type: Specific Biological process 

### INPUT: the two tables of the spatial transcriptomic data, a specified GO term 


### ALGORITHM:
1-(BACKEND or DATABASE) First we need to pass from the biological process selected by the user from the search tool to the respective GO term id, that is an id of the form GO:XXXX, because this is what the database will need in the next step
2- (DATABASE) The second step is the of connecting to a database that given a GO term id will then retrive all the genes involved in such a a process
3- (BACKEND) Now that we have a list of genes for each bead we see what is the proportion of these genes with respect to the total expression.
(Example: The total expression for a bead is 240 (sum over a given column of the expression matrix) and the total expression for the genes in the list sums up to 60 (sum just of the entries of the column corresponding
to genes in the list). Therefore the desired result for this single bead is gonna be 60/240 = 25%.)
4-(FRONTEND): We do the same operation for each single bead and we plot the results again as a sort of scatter plot

### OUTPUT: the scatter plot described in the example above 

## Second type: Biological processes search

### INPUT: The two tables of the spatial transcriptomic data, a given resolution (i.e. a given number from 1 to 100 that is asking the percentage of genes to keep in the analysis), the number of processes the user wants to see (from 1 to 5?). [Note: maybe the optimal number of processes to find can be computed somehow seeing the elbow of the plot (distance vs number of clusters) for the dendrogram, but we will work on it just if we will have time]

### ALGORITHM:
1-(BACKEND First we need to perform the above mentioned filtering. Suppose the user selects a resolution of 5%, that is gonna be the default one. The table needs to retain just the raws which sum is in the top 5% overall
2-(BACKEND) Now it's time to calculate the MD table from the distribution of the remaining genes. We start from 2D distribution on a fixed support and we want to calculate the MD. To do that we will probably need to use the "Sliced MD distance. What you do here is to take a random direction in the 2D space where the beams coordinate live and then project the position of the beams onto this line. This new positions for the beams will be not anymore in a 2D space (a plane) but on a 1D space (a line) now we can calculate the EMD distance for the 1D distribution, which is a much easier task computationally and many packages already exist that are able to do that. Then you need to repeat this process of projecting on a random direction a number n of times (maybe 100? we will see how much it takes) and take the mean of the resulting EMDs.
3-(BACKEND)Now that you've a table of distances you can build a dendrogram (I guess there exist some packages that already do that) and you can cut it where you need (depending on how many clusters the user wants to have at the end let's call the resulting number of clusters k
4-(DATABASE) We run each list of genes on the DAVID database to see which is the biological process (GO term in general) that is more likely to happen given that list and we therefore assign a biological process to each cluster.
5- (BACKEND) Now for each list of genes/cluster and for each bead we see what is the proportion of these genes with respect to the total expression. (This is Exactly what we have done in the step 3 of before) but now we do it k times
6-(FRONTEND) Produce the k plots as and we plot them with he title that is something like "the XXXX process on your tissue" and the possibility for the user to navigate through them
