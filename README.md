# TranscriptomiC++
##DESCRIPTION
This is the repo for the project TranscriptomiC++ in the context of the course CSE201 at École Polytechnique.

The project aims to build a compeletely working open access platform that can be used by biologists to have new insights on their spatial transcriptomics data. In particular the user will have the possibility to chose a biological process from a menu of possibilities are recive back as output a gradient map of the tissue where the process is associated to each point of the tissue with a given probability.

##INPUT

###FORMAT
The platform will accept files in the following format of the data:

- `.csv`
- `.txt` with the first entries being the header of the table and the indexes needs to be also included 
- `.mtx`

---

###TECHNOLOGIES
The platform will accept files produced with the following technologies:

- SlideSeq: we will adopt the convention that the rows (indices) indicate the `gene` and the columns will indicate the `beam/barcode`. Each entry of the table will be therefore the level of expression of a certain gene registered on a certain beam

- Cartana: we will adopt the convention that the rows (indices) indicate the genes and there will be two columns containing the `X` and the `Y` coordinates for each `gene` 

##ANALYSIS
###VISAULIZATION 

The first thing resurned is an interactive visualization of the data provided. This allows the user to navigate the the reconstruction of the tissue and explore single/multiple gene expression profiles. This is produced internally by the function `show(expression_matrix)`.

###PREPROCESSING: Filtering/Nomralization 

In the meanwhile the platform will already start the processing of the data. This has many steps that account for the limits of the technology and the experimental envirionment that we want to filter out. The user has the possibility to modify the metaparameter of this preprocessing. In particular the function inplemented will be the following:
- `filter(expression_matrix, zeroes = True, min_expr_perc = 0.1 type_of_transcriptome = NULL)`: The `filter` function will by default take the Expression Matrix and eliminate all the genes that are never expressed (`zeroes` parameter) and in general the genes that are expressed in less than 0.1% of the beams (`min_expr_perc` parameter). It will also give you the possibility to choose a certain kind of transcriptome between: `'ribosomal', 'genetic', 'intergenic', 'exonic', 'intronic'` the default is `NULL` that is returning everything

- `normalization(expression_matrix, type_of_normal = 'lognorm_plus_one')`: The `normalization` function will take the Expression Matrix (that is supposed to be already filtered) and preforms a transformation of the data that could be decided between `'lognorm_plus_one', NULL, ...`

(TO BE SPECIFIED)

###GENE CLUSTERING 
The Pipline then performs a clustering according to the similarity of the gene expression (TO BE SPECIFIED)

###DATABASE INTEGRATION
The Pipeline then looks into the database the signature of a certain biological process (in terms of genes involved) and retrives the relative importance of the genes taken by the gene clustered together. (TO BE SPECIFIED)

###REMAPPING
The pipeline will then build a probability distribution (probability of presence of a certain biological process) over the image. And will plot the gradient map required by the user with also some confidence interval summary of the whole analysis.
