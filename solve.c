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

#include <time.h> // for seeding random number generator
#include "solve.h"

#define LINEBUF_SIZE 2048

#define FOPEN_ERR 1
#define FILE_FORMAT_ERR 2

// Buffer for holding lines from adjacency list file
static char line_buffer[LINEBUF_SIZE];


/*
*Function:        read_adjacencies
*---------------------
* Description:

	This function is used for for reading the lines of maze generation file and
	parsing it as an adjacency list. The first line indicates the number of rows (nrows) and number 
    of columns (ncols), second line indicates the starting node and finish node of the maze. From third
    line, we obtain the list of adjacent nodes of node 0, separated by whitespaces and this 
    goes upto the last node, which is nrows*ncols.

	Parameters:

		fp:
			The pointer to the file to read from. The position upon calling this 
			function should be the third line in the file containing nothing but integer numbers
			separated by whitespace. From third line, the integers indicate
            the adjacencies of the current node.

	Return:

		NULL on a failed parse, otherwise a pointer to a linked list with this
		vertex's adjacent vertices.
*/
adj_node *read_adjacencies(FILE *fp)
{
	// Can't read if we've reached end of file
	if(feof(fp))
	{
		return NULL;
	}

	// Read the next line into the buffer. On failure, return null.
	char *line = fgets(line_buffer, LINEBUF_SIZE, fp);
	if(line == NULL)
	{
		return NULL;
	}

    //adjacencies and adj_end are initialised to NULL
	adj_node *adjacencies = NULL;
	adj_node *adj_end = NULL;

	size_t line_length = strlen(line);

	// If this line is just too long to parse, fail
	if( (line_length == LINEBUF_SIZE-1) && (line[LINEBUF_SIZE-2] != '\n')
		 && (!feof(fp)))
	{
		fprintf(stderr, "Encountered a line longer than max allowed size"
			" (%d).\n",LINEBUF_SIZE-1);
		return NULL;
	}

	char *endptr = line;

	// Loop through the line until we've read in all present adjacent vertices.
	while(*endptr != '\0')
	{

		// Skip all whitespace
		while(isspace(*endptr) && (*endptr != '\n'))
		{
			endptr++;
		}

		// If we've skipped to the null-byte or a newline character, then we're
		// done parsing this line.
		if((*endptr == '\n') || (*endptr == '\0'))
		{
			break;
		}

		char *next_num = endptr;

		// Parse a number from the current position in the line, which will be
		// our next adjacent vertex.
		errno = 0;
		int myAdj = strtol(next_num, &endptr, 10);
		if(errno || ( (!isspace(*endptr)) && (*endptr != '\0')))
		{
			return NULL;
		}

		// If this is our first adjacent vertex, initialize the linked list.
		// Otherwise, append to the existing linked list.
		if(adjacencies == NULL)
		{
			adjacencies = (adj_node*)malloc(sizeof(adj_node));
			adj_end = adjacencies;
			adjacencies->next = NULL;
			adjacencies->vertex = myAdj;
		}
		else
		{
			adj_node *tmp = (adj_node*)malloc(sizeof(adj_node));

			tmp->next = NULL;
			tmp->vertex = myAdj;
			adj_end->next = tmp;
			adj_end = tmp;
		}
	}

	// If we didn't encounter any errors, but also didn't parse any numbers,
	// we have no adjacent vertices. In this case, we simply have a node with
	// no outgoing edges. So we make a linked list with one node, and 
	// a sentinel value indicating this.
	if(adjacencies == NULL)
	{
		adj_node *toReturn = (adj_node*)malloc(sizeof(adj_node));
		toReturn->next = NULL;
		toReturn->vertex = NO_ADJACENCIES;
		return toReturn;
	}


	return adjacencies;

}

/*
 * Function:  freeAll
 * --------------------
 * Description:
 *      Frees all nodes in the given linked list.
 * Parameters:
 *      adj_node *list- Linked List whose nodes are to be free'd
 * Returns:
 *      Nothing: All nodes of the list are free'd.
 */
void freeAll(adj_node *list)
{
	adj_node *toFree = list;
	adj_node *next = NULL;

	while(toFree != NULL)
	{
		next = toFree->next;
		free(toFree);
		toFree = next;
	}
}


/*
 * Function:  LLQ_create
 * --------------------
 * Description:
 *      Function to create a new Linked List Queue. LLQueue is required to
 *      store output of BFS
 * Parameters:
 *      Nothing: Just call the function
 * Returns:
 *      Linked List Queue with 0 elements is created, else will return NULL because of 
 *      lack of memory
 */

LLQueue *LLQ_create(){

    //Queue LLQ to be created is defined with appropriate size
    LLQueue *LLQ = (LLQueue*)malloc(sizeof(LLQueue));

    //If LLQ remains NULL after assigning memory, it means there is not enough memory 
    //to assign LLQ and function will return NULL.
    if (LLQ == NULL) {
        //printf("\nUnable to allocate due to lack of memory.\n");
        return NULL;
    } 

    //Initialise LLQ as empty queue, if created.
	LLQ->front = LLQ->rear = NULL; 
	return LLQ; 

    //printf statement to ensure that queue is created.
    //for debugging only, can be removed later.   
    //printf("\nEmpty queue created successfully !\n");
    
}   


/*
 * Function:  LLQ_insert
 * --------------------
 * Description:
 *      Function to insert data in LLQ
 * Parameters:
 *      LLQ: The name of the queue in which data is to be inserted.
 *      data: an integer which is to be inserted in queue
 * Returns:
 *      Linked List Queue with the added element is returned. -1 is returned if there
 *      is no space to store addditional element. 
 *     
 */
int LLQ_insert(LLQueue *LLQ, int data) 
{ 
    
    //temp is the new node for the queue
    LLNode *temp = (LLNode*)malloc(sizeof(LLNode));

    //If unable to grant memory to temp, return error(-1)
    if (temp == NULL) {
        printf("Not enough memory for new element\n");
        return -1;
    }

    //Assigning values to temp
    temp->value = data;
    temp->next = NULL;

    //If Queue is empty, front and rear elements are same 
    if(LLQ->front == NULL){
        LLQ->front = temp;
        LLQ->rear = temp;
    }

    //If Queue has elements, then new element will be stored after last element
    else{
        LLQ->rear->next = temp;
        LLQ->rear = temp;
    }

    //printf statement to ensure that new element is added.
    //for debugging only, can be removed later.
    //printf("\nInsertion successful !\n");
 
} 

/*
 * Function:  LLQ_delete
 * --------------------
 * Description:
 *      Function to delete oldest element from queue
 * Parameters:
 *      LLQ: The name of the queue from which element is to be removed.
 * Returns:
 *      Linked List Queue with the removed element is returned. -1 is returned if the
 *      queue is already empty because there is nothing to remove.
 * 
 */

int LLQ_delete(LLQueue *LLQ)
{
   //If queue is empty, return error(-1)
   if(LLQ->front == NULL){
      printf("\nError !! Queue is Empty!!!\n");
      return -1;
   }

   //If queue has elements, oldest element will be removed
   else{
       
      //temp will be created to temporarily store first element of queue 
      LLNode *temp = (LLNode*)malloc(sizeof(LLNode)); 
      temp = LLQ->front;

      //Second element is made the First element and temp is removed.
      LLQ->front = LLQ->front->next;

      //printf for debugging to see correct element is removed
      //printf("\nDeleted element: %d\n", temp->value);
      free(temp);
   }
}

/*
 * Function:  LLQ_delete_new
 * --------------------
 * Description:
 *      Function to delete newest element from queue
 * Parameters:
 *      LLQ: The name of the queue from which element is to be removed.
 * Returns:
 *      Linked List Queue with the removed element is returned. -1 is returned if the
 *      queue is already empty because there is nothing to remove.
 * 
 */
int LLQ_delete_new(LLQueue *LLQ)
{
   //If Queue is empty, return error(-1) 
   if(LLQ->front == NULL){
      printf("\nError !! Queue is Empty!!!\n");
      return -1;
   }

   //If Queue has only one element, remove that and return empty queue         
    else if (LLQ->front->next == NULL) { 
        free(LLQ->front);  
        LLQ->rear = LLQ->front = NULL;
        } 
  
    //If queue has more than 1 element
    else{
        //temp is created to find the second last element of the queue using while loop
        LLNode *temp = LLQ->front; 
        while (temp->next->next != NULL)
        { 
        temp = temp->next; 
        }
    //temp is now second last element, hence next element to that will be removed
    //printf to check that correct element is removed. Can be removed after debugging
    //printf("\nDeleted element: %d\n", temp->next->value);
    free(temp->next); 
  
    //Making next element of temp as NULL and making temp as rear element of queue
    temp->next = NULL; 
    LLQ->rear = temp;
  
   }
}

/*
 * Function:  LLQ_print
 * --------------------
 * Description:
 *      Function to display all elements of LLQ
 * Parameters:
 *      LLQ: The name of the queue which is to be displayed
 * Returns:
 *      Linked List Queue will be shown. If no element exists, message of empty queue
 *      will be shown.
 * 
 */

void LLQ_print(LLQueue *LLQ)
{
   //temp is used here to travel to every element of queue and display it
   LLNode *temp = (LLNode*)malloc(sizeof(LLNode*)); 

   //If queue is empty, empty message will be shown
   if(LLQ->front == NULL)
      printf("\nQueue is Empty!!!\n");
   
   else{
      //temp starts from first element and goes upto the last one using while loop
      temp = LLQ->front;      

      while(temp->next != NULL){
	    printf("%d--->",temp->value);
	    temp = temp -> next;
      }
      printf("%d--->NULL\n",temp->value);
   }
}


/*
 * Function:  LLQ_count
 * --------------------
 * Description:
 *      Function to count number of element in queue
 * Parameters:
 *      LLQ: The name of the queue whose elements are to be counted
 * Returns:
 *      Will give an integer value greater than or eqaul to 0, which is count
 *      of elements in queue
 * 
 */
unsigned int LLQ_count(LLQueue* LLQ)
{
    //count to keep track of number of elements
    int count = 0;
    //temp will travel to every element through while loop and increase count value 
    //when it passes through a new element

    LLNode *temp = (LLNode*)malloc(sizeof(LLNode*)); 
    
    //temp starts from first value
    temp = LLQ->front;

    //while loop will run untill NULL is reached
    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

/*
 * Function:  LLQ_Search
 * --------------------
 * Description:
 *      Function to search an element in the queue
 * Parameters:
 *      LLQ: The name of the queue in which the element is to be searched
 *      data: an integer value of the element to be searched
 * Returns:
 *      Will give value of the element itself if it's present in the queue
 *      If the element is not present, it will return -1 (indicating element is not present)
 * 
 */
int LLQ_Search(LLQueue *LLQ, int data) {
    //temp will go through whole queue to search for the element
    //temp will start from first element
    LLNode* temp = LLQ->front;  
    //while loop to search through whole queue
    while (temp != NULL) { 
        if (temp->value == data){
            return data; 
        }
        temp = temp->next; 
    } 
    //return -1 if element not present
    return -1; 
}


/*
 * Function:  LLQ_free
 * --------------------
 * Description:
 *      Function to delete all the elements in the queue at once
 * Parameters:
 *      LLQ: The name of the queue which has to be deleted
 * Returns:
 *      Will print the message that queue is deleted successfully. If queue was already empty, it will
 *      throw a message that queue is empty.
 * 
 */
void LLQ_free(LLQueue *LLQ)
{
    //temp used to go through every element of queue
    LLNode *temp;

    //If queue is empty, return the error message
    if(LLQ->front == NULL){
        //printf("\n Error !! Queue is empty.\n");
        return;
    }
    //If queue has elements
    //while loop will run untill every element is deleted
    while(LLQ->front != NULL)
    {
        //temp starts from first element of the queue
        //then front element is changed to second element and
        //temp is deleted.
        temp = LLQ->front;
        LLQ->front = LLQ->front->next;

        free(temp);
    }
   // printf("\nDeleted All elements of Linked List Queue, one after another, finally deleting the queue.\n");
}

