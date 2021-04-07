# Total_Amazement

Authors:

Sarah Bi 
Saurabh Parimal Doodhwala 

Program description:
This program will generate and solve a maze using an MxN graph. This program is divided into two parts. 

The maze generation program will create a maze for a MxN graph representation using a depth first search (DFS) algorithm. The command line input parameters for maze generation are: 

1. Number of rows of the graph 
2. Number of columns of the graph 
3. Filename of the .txt output to which the maze generation information should be written to. 

The maze solution program will solve the maze generated in the previous step using a breadth first search (BFS) algorithm and construct a path from start to finish. The path will be printed to the screen when the maze is solved. The maze solution program will take a single command line input: 

1. The name of the textile that was generation from the maze generation program


Maze Generation:
The maze generation code was written on a computer with: 
1) Operating system : macOS Catalina Version 10.15.6
2) Compiler: Clang Version 11.0.3
3) C IDE: CLion Version 2020.2 
4) Testing: Linux Darwin 19.5.0

How to compile and run (in Linux): 
1. Navigate to the directory containing the files main_generate.c, generate.c, and generate.h 
2. Ensure that the file titled "makefile" is also in the same directory
3. Type the following command to compile the program: make
4. Type the following command to run the program: ./main_generate nRows nCols filename.txt 

	nRows is the number of rows in the maze graph
	nCols is the number of columns in the maze graph 
	filename.txt is the name of the textile to which the maze information will be output (remember to include the .txt extension in the filename. Failure to do so may create an unreadable output file). If only the filename is specified, the text file will be saved to the working directory. If the user wishes to save the text file to a different directory, please specify the entire directory path in the command line argument. 

5. The program will output the results of the maze generation to the text file. The text file will always be organized in the same manner. The first row indicates the number of rows and number of columns of the maze. The second row indicates the starting and ending node of the maze generation. Every single subsequent line indicates node connections for each node of the maze, starting at node of index 0 and going to node of index nRows*nCols-1 

An example is shown below for a 2x2 matrix: 

Line 1 (nRows nCols)            	2 2 
Line 2 (startNode endNode)     		3 2 
Line 3 (connections for node 0) 	1 2 
Line 4 (connections for node 1) 	3 0 
Line 5 (connections for node 2) 	0 
Line 6 (connections for node 3) 	1 


Maze Solution:
The maze solution code was written on a computer with: 
1) Operating system: Windows 10
2) compiler used: GCC
3) C IDE: VS Code
4) Testing: Linux Darwin 19.5.0

How to compile and run (in Linux): 

1. Navigate to the directory containing the files main_solve.c, solve.c, and solve.h 
2. Ensure that the file titled "makefile" is also in the same directory
3. Type the following command to compile the program: make
4. Type the following command to run the program: ./main_solve filename.txt 

	filename.txt is the name of the text file containing the maze information outputted from the maze generation program 

5. The program will output the results of the maze solution to the screen by indicating the sequence of node indices from start to finish 
