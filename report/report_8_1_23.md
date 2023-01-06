## Group project report due to 8th January 2023

### R&D
Members: 
- Clémence Mottez
- Lorenzo Tarricone 
- Jingai Si
- Samuel Tillier 

Clémence Mottez: I did lots of research on the David data base. This is useful for the next step of our project: the study of the biological processes. This was important to start to work on it since a lot of work needs to be done on that, and it is not possible without research. I tried to understand how this database works, without much information unfortunately. I tried to figure out how we can do an API call from a list of gene, and have access to the biological processes linked to these genes. Unfortunately again, a key functionality of this data base that we need didn't work. Thus I searched for another way to do it. I finally find another database: the gene onthology (GO) database that could work. 


### Database
Members:
- Nicolás López Corral
- Clémence Mottez
- Iris Brun

Iris Brun: Wrote a code that takes a gene as input and give its gene Ids gotten from an API as output, wrote a code that does something similar but giving the biological processes of a list of genes. Researched how to install libcurl on windows such that it works in qt.

Clémence Mottez: During the hollidays: I start to work on a code that do the API calls for the other part of the project (the one that takes as input a gene and returns all the different names of this gene) since it is a key program for our project and Nicolas didn't manage to do it yet. I first tried to help Nicolas on his code and then started a completely different program since I thought we were kinda stuck. I also wrote an easier program to have access to the different names of the gene given the string returned by the API (the first one was much more longer since we were not sure that the only important information were just in the list where the name of the gene we put as an input is, so we could have access to much more information). Moreover, I wrote a new code (main_bis) to combine all the previous codes (readgenetxt, only_gene_name, api, ...) that read the list of gene from the researcher, call the API for each gene, and output a set with all the different possible names of the genes. This one doesn't completely work since I wasn't able to test it on my machine for some reasons that I couldn't solve. Thus it was a little bit long to correct it. In the meantime, I also worked on a program that take the original matrix file (the one from the researcher, the big table with names of the cells, genes and some integers in it) and the set of all the different names of the genes he is interested in, and output another much smaller file that contains only the lines where the first element (name of the gene) is in the set. This program can take either a matrix file in a txt format or csv format and will of course output a file in the same format. Unfortunately I realized that this last program wasn't useful since the format of our input file changed: it is a mtx file. So the backend/algorithms team will implement this function since they know how to work on this kind of input data. 

### Algorithms/Backend 
Members:
- Adrian Düsselberg
- Nina Peuker
- Alan Picucci


### Frontend 
Members:
- Rita Saraiva
- Leonard Theisler
