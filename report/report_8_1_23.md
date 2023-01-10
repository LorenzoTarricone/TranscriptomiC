## Group project report due to 8th January 2023

### R&D
Members: 
- Clémence Mottez
- Lorenzo Tarricone 
- Jingai Si
- Samuel Tillier 

Clémence Mottez: I did lots of research on the David data base. This is useful for the next step of our project: the study of the biological processes. This was important to start to work on it since a lot of work needs to be done on that, and it is not possible without research. I tried to understand how this database works, without much information unfortunately. I tried to figure out how we can do an API call from a list of gene, and have access to the biological processes linked to these genes. Unfortunately again, a key functionality of this data base that we need didn't work. Thus I searched for another way to do it. I finally found another database: the gene onthology (GO) database that could work. 

Lorenzo Tarricone: Fine tuned all the methods needed for the two kinds of analysis that can be implemented. A complete description of the algorithm for the colocalization table and the biological process identifier table are available on the R&D branch. Designed the how the user interface for the final product needs to be and shared it with the frontend team. I also made some literature search and provided everyone with a database from 10X genomics with some open access data. The only problem is that not everything we need is there, in particular the table with the location of the beams is missing

### Database
Members:
- Nicolás López Corral
- Clémence Mottez
- Iris Brun

Iris Brun: Wrote a code that takes a gene as input and give its gene Ids gotten from an API as output, wrote a code that does something similar but giving the biological processes of a list of genes. Researched how to install libcurl on windows such that it works in qt.

Clémence Mottez: 
During the hollidays: I start to work on a code that do the API calls for the other part of the project (the one that takes as input a gene and returns all the different names of this gene) since it is a key program for our project and Nicolas didn't manage to do it yet. I first tried to help Nicolas on his code and then started a completely different program since I thought we were kinda stuck. I also wrote an easier program to have access to the different names of the gene given the string returned by the API (the first one was much more longer since we were not sure that the only important information were just in the list where the name of the gene we put as an input is, so we could have access to much more information). Moreover, I wrote a new code (main_bis) to combine all the previous codes (readgenetxt, only_gene_name, api, ...) that read the list of gene from the researcher, call the API for each gene, and output a set with all the different possible names of the genes. This one doesn't completely work since I wasn't able to test it on my machine for some reasons that I couldn't solve. Thus it was a little bit long to correct it. In the meantime, I also worked on a program that take the original matrix file (the one from the researcher, the big table with names of the cells, genes and some integers in it) and the set of all the different names of the genes he is interested in, and output another much smaller file that contains only the lines where the first element (name of the gene) is in the set. This program can take either a matrix file in a txt format or csv format and will of course output a file in the same format. Unfortunately I realized that this last program wasn't useful since the format of our input file changed: it is a mtx file. So the backend/algorithms team will implement this function since they know how to work on this kind of input data. 
During the week after the holidays: During the TD, I work on "main_bis": the code that combine all the program to do the API, to make it works with Nicolas. It finally did!
Then I change the only_gene_name code to add to the set of all the different names of the genes (the ouput of the API code) more information and also include the gene strings in lower case and the gene strings with the first letter in upper case and the following in lower case. I also wrote a code that change the txt file from the researcher, putting only capital letters in the names of the genes. However, this code wasn’t the smarter way to do it, so I forgot this program and I changed again the only_gene_name by adding a function that just upper case the searching parameter read in the txt file, before doing the API searching. Finally, I also changed all the files of the API branch with a proper way to define the strings, to avoid naming conflicts by expliciting the namespaces we are using.

### Algorithms/Backend 
Members:
- Adrian Düsselberg
- Nina Peuker
- Alan Picucci

Alan Picucci: Implemented step 4 in the construction of the colocalisation matrix. This consists in the following: create a new matrix of size n_genes times n_genes times n_cells which, for each cell, compares the column corresponding to that cell from the original expression matrix with the column from the Neighbouring expression matrix. Then we take the mean along the n_cells dimension.

Adrian Düsselberg:
Worked on improving the heatmap. Created a class fake_colocalization_matrix on HeatMap-without-Eigen to optimize the plotting. Wrote a method, which takes  an Eigen:: Matrix M as input and returns a heatmap (i and j are the x,y-coordinates and M(i,j) is z-coordinate). Thereby modified how the data is read.    

Nina Peuker: Implemented filtering and normalisation methods as well as step 5 and 6 of the colocalisation matrix. Organized and took part in project management meetings and assigning of tasks. Created dummy functions to test methods, combined steps to run first iterations of colocalisation computations.


### Frontend 
Members:
- Rita Saraiva
- Leonard Theisler

Leonard Theisler: This will cover the hollidays as well as this week. Implemented saving heatmap functionality (saves as png). File explorer pops up and allows the user to choose where the heatmap should be saved. Implemented csv file upload and parsing for genes of interest in the colocalization window (includes error handling). Also uses the file explorer and the user can choose the file to upload. Implemented text box in the biological process window for user input of process to anaylze (includes error handling). Implemented navigation between windows with buttons. Included the correct makeHeatmap function (from Adrian) into the frontend.

Rita Saraiva: Did not work during the hollidays due to familly related constraints. Refactored main and second window as well as their associated funtions and variables. Previous names were unclear. Improved the style and layouts of multiple windows accoridng to GUI principles. 
