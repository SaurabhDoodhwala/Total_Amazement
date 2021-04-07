/*
 * CSE 6010 Assignment 5
 * Team: Sarah(Generation) and Saurabh(Solution)
 * Created by Saurabh Doodhwala
 * Last edited on 15 October 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "solve.h"

#define LINEBUF_SIZE 2048

#define FOPEN_ERR 1
#define FILE_FORMAT_ERR 2

#define USAGE_STRING "./<exe name> Generated_Maze_File.txt"




// Buffer for holding lines from adjacency list file
static char line_buffer[LINEBUF_SIZE];




int main(int argc, char const *argv[])
{
	//To check that proper number of arguments are passed 
	if(argc != 2)
	{
		fprintf(stderr, "Error: incorrect number of arguments to program.\n");
		fprintf(stderr, "%s\n", USAGE_STRING);
		return 1;
	}

    //Reading the passed file
	FILE *adjListFile = fopen(argv[1],"r");


	if(adjListFile == NULL)
	{
		fprintf(stderr, "Could not open the file '%s' for reading.\n", argv[1]);
		perror("Error");
		return FOPEN_ERR;
	}

	//Read in the numbers from the first and second lines of the file.
    //First line has Number of Rows and Number of Columns of the maze, separated by whitespace.
    //Second line has index of starting node and ending node of the maze
	int read_in = 0;
	int n_vertices, nrows, ncols, start, finish;

	read_in =  fscanf(adjListFile," %d %d\n",&nrows, &ncols);
	read_in =  fscanf(adjListFile," %d %d\n",&start, &finish);
	n_vertices = nrows*ncols;
    //If loop to check that first two lines are read correctly
	if(!read_in)
	{
		fprintf(stderr, "File format error for either first or second or both the lines.\n");
		return FILE_FORMAT_ERR;
	}

	//Debug here to check whether correct values are read from the file
	//printf("Reading adjacency list for %d vertices...\n",n_vertices);


	// Allocate size for the adjacency list. First, an array of pointers, each
	// pointer will be the start of a linked list constructed for each line of the
	// adjacency list.

	adj_node **adj_list = (adj_node**)malloc(n_vertices * sizeof(adj_node**));

	for (int i = 0; i < n_vertices; i++)
	{
		adj_list[i] = NULL;

		//Reading the adjacent nodes of the node i from the file
		//Remember, this reading starts from the third line of the input file.
        adj_list[i] = read_adjacencies(adjListFile);

        //If we error out of reading the next line, quit.
		if(adj_list[i] == NULL)
		{
			fclose(adjListFile);
			for (int j = 0; j < i; ++j)
			{
				freeAll(adj_list[j]);
			}
			fprintf(stderr, "File format error on adjacencies.\n");
			return FILE_FORMAT_ERR;
		}
	}

	// Print out the adjacency list we read in
	//Can be removed after debug
	/**
	for (int i = 0; i < n_vertices; ++i)
	{
		printf("Vertex %d is adjacent to:\t",i);
		//neighbors will store adjacent nodes of thse node i.
		adj_node *neighbors = adj_list[i];

		//All values should be greater than or equal to 0
		//If it detects no value at the first place, it will go to the next node/vertex and
		//give message that this node has no neighbor outgoing vertex/node
		if(neighbors->vertex == -1)
		{
			printf("No other vertices.\n");
		}
		else
		{	//While loop to check that we go through all nodes in the neighbors
			while(neighbors != NULL)
			{
				printf("%d, ",neighbors->vertex);
				neighbors = neighbors->next;
			}
			printf("\n");
		}
	}
	**/

	//We will close the file after reading it
    fclose(adjListFile);

        
        // ********** Begin BFS loop **********
    //printf("begin BFS loop\n");
    //int currentNode = start;
    //printf("%d\n",currentNode);
    
    //Defining queues to store the nodes we get through BFS
	//BS is queue for basic solution. It will intially store all the node values which BFS loop visits 
	//FS is queue which gives us the final solution path from start to finish.
	//Here, initially there was a requirement for 4 queues to arrive at final solution.
	//But, we will reuse the two queues BS and FS to arrive at final solution, hence saving some memory.
    LLQueue *BS = LLQ_create();
	LLQueue *FS = LLQ_create();

    //printf("%d\n", finish);
	//We will start our BFS from the start node and start storing all nodes visited in BS queue.
    LLQ_insert(BS, start);
    //LLQ_print(BS);
	//printf("%d\n", BS->front->value);
    //printf("%d", LLQ->front);
    //int a = 0;
    //int b = 0;
    //int c = 0;
    LLQ_count(BS);
    
	//adjacent contains the adjacent vertices of the current node/vertex
	adj_node *adjacent = (adj_node*)malloc((n_vertices) * sizeof(adj_node*));
    
	//We will implement the BFS untill we reach the finish node
	while(LLQ_Search(FS, finish) != finish){


        //a = a + 1;
        //printf("a is %d\n",a);
        // Determine adjacent nodes of front element node of Queue BS  
        // Add all the neighbors to the Queue BS and delete the front element
        // If the selected node has already been visited, we will not take that into queue BS again
		
		adjacent = adj_list[BS->front->value];

		LLQ_insert(FS, BS->front->value);

		LLQ_delete(BS);
        //printf("%d\n", adjacent->vertex);
        //printf("%d\n", adjacent->next);
        
        //If the present node has no adjacent neighbors, we will move to the next node 
		if(adjacent->vertex == -1)
		{//c=c+1; printf("c is %d\n",c);
		    LLQ_delete(BS);
            continue;
		}
		else
		{//b =b+1; printf("b is %d\n", b); LLQ_print(BS);
			//We will travel through each and every adjacent node of the current node
			//If any adjacent node is not present in our FS queue, we will insert that node in BS
			//If any adjacent node is there in FS queue, that means BFS has already covered it once, 
			//so we will not add it in BS Queue
			//Hence, at the end of this operation we will have all the nodes visited by 
			//BFS in the queue FS and queue BS will be almost empty.
			
			while(adjacent != NULL)
			{
				if((LLQ_Search(FS, adjacent->vertex) != adjacent->vertex) ){
					LLQ_insert(BS, adjacent->vertex);
				}
				adjacent = adjacent->next;
                //LLQ_print(LLQ);   
                //printf("%d\n", adjacent->vertex);
			}
            //LLQ_print(PQ);
		}
    }

	//LLQ_print(BS);
	//LLQ_print(FS);
	//We will free the queue BS, so that we can use it further to store other results
	LLQ_free(BS);
	//Now we will create a solution path from the queue FS. FS has all nodes BFS visited, 
	//but we only need the nodes connecting start and finish.

	//1. So now we will start from finish node and construct a path in reverse direction till start node
	//2. We will store this path in queue BS
	//3. We will take rear element of queue FS and insert in BS for a start.
	//4. Then, we will find adjacencies of the rear element in BS and try to find it in FS.
	//5. If it's present in FS, then we will delete all the elements from rear in queue FS.
	//6. That means we will set the queues such that rear elements of both are the same.
	//7. After that, we will again find adjancent nodes of the rear element in BS and try to find it in FS.
	//8. Again, we will repeat all the steps from 3 to 6 (as shown above), untill we insert our original start in queue BS
	//9. This way we get our solution in queue BS, but its in reverse direction
	
	// ------Code showing above 9 steps ---------------

	LLQ_insert(BS, FS->rear->value);
	//adj_node *neighbor = (adj_node*)malloc(n_vertices * sizeof(adj_node*));
	int z =0;
	while(LLQ_Search(BS, start) != start){
		//neighbor = adj_list[Q->rear->value];
		//printf("%d\n", Q->rear->value);
		//printf("%d\n", PQ->rear->value);
		//printf("%d \n", neighbor->vertex);

		while(FS->rear->value != BS->rear->value){
			
			//LLQ_print(Q);
			//LLQ_print(PQ);
			
			//printf("1 and %d\n", FS->rear->value);
			LLQ_delete_new(FS);
			//printf("2 and %d\n", FS->rear->value);
			/**
			if(z==1){
				LLQ_delete_new(PQ);
				LLQ_print(PQ);
				break;}
				**/
		}
	
	
		//if(z==1){break;}
		//printf(" %d\n", PQ->rear->value);
		//printf(" %d\n", Q->rear->value);
		//LLQ_print(PQ);
		//LLQ_print(Q);	
		
				//printf("%d \n", adj_list[BS->rear->value]->vertex);
				while(adj_list[BS->rear->value]->vertex != LLQ_Search(FS, adj_list[BS->rear->value]->vertex)){
					adj_list[BS->rear->value] = adj_list[BS->rear->value]->next;
					//printf("%d \n", adj_list[BS->rear->value]->vertex);

				}
			
				LLQ_insert(BS, adj_list[BS->rear->value]->vertex);
			    //LLQ_print(Q);
				//LLQ_print(PQ);
				//free(neighbor);
			z=z+1;
			//printf("%d\n",z);
			//printf("%d\n", PQ->rear->value);
			//printf("%d\n", Q->rear->value);
	}	
	//-------------Code showing those 9 steps ends here-----------------
    
    // Function to display all elements of LLQ
    //LLQ_print(BS);
	//LLQ_print(FS);
	//We will free queue FS, as it can be used ahead
	LLQ_free(FS);

	//This while loop will convert our reverse solution in queueu BS into proper
	//solution in forward direction and store it in queue FS
	//FS is our final solution
	while(LLQ_count(BS) != 0){
		//printf("%d\n", LLQ_count(BS));
		LLQ_insert(FS, BS->rear->value);
		//LLQ_print(S);
		LLQ_delete_new(BS);
	}
	printf("The final solution of the given input maze of %d rows and %d columns, from start till the finish node, is:(NULL states that solution ends there) \n \n", nrows, ncols);
	LLQ_print(FS);

//Freeing the adjacency list after completion of code here  
	for (int i = 0; i < n_vertices; ++i)
	{
		freeAll(adj_list[i]);
	}
	free(adj_list);

}

