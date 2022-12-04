## Group project report due to 5th December 2022

### R&D
Members: 
- Clémence Mottez

Clémence Mottez: working on a python program to check the implementation of the algorithm we will use for the colocalization table (to be sure it works before implementing it in C++) 

### Algorithms/Backend 
Members:
- Jingai Si
- Samuel Tillier 
- Adrian Düsselberg
- Clémence Mottez
- Nina Peuker


Jingai Si; Samuel Tillier; Adrian Düsselberg: Testing out the QCustomPlots library, which allows the generation of plots (including heat maps) within the Qt interface using widgets. We are currently working on the implementation of QCustomPlots into our main project, but the project may have to be reconfigured differently for this to work. Determined the calculation of the matrix column sum for gene expression, which will give a value corresponding to the intensity on the heat map. We are currently optimising this calculation based on its complexity. Conducted research on sparse matrices and their representations as arrays with zero entries excluded.

Clémence Mottez and Nina Peuker: Last week, we wrote a program that takes a matrix.tkt file and log2 all the value and rewrite it in another txt file of the same form as the matrix one. We realized that it would be much easier for all our computations to just have a matrix object. Thus, we wrote a program that can take either a matrix or coordinates file, either in txt or csv form, and convert the values inside the file into a matrix object (of size nb of cells times nb of genes for the matrix one and 2 times nb of genes for the coordinate one.) 


### Frontend 
Members:
- Rita Saraiva
- Leonard Theisler

Leonard Theisler: Wrote a script that takes user input and opens the file. User writes the file location in a text editor in the GUI, a window pops up if the file is not found and if it is found it reads it. Also managed to print the data in a popup window, how ever it prints data point by datapoint. Investigated QCustomPlots library and attempted to add it to the project, came to the same conclusion as the backend team.

Rita Saraiva: Researched and implemented how to make new windows open. Wrote a script where the main window closes upon successful file upload and a new main window appears.
