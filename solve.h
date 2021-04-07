/*
 * CSE 6010 Assignment 5
 * Team: Sarah(Generation) and Saurabh(Solution)
 * Created by Saurabh Doodhwala
 * Last edited on 15 October 2020
 */

#ifndef ASSIGNMENT5_SOLVE_H
#define ASSIGNMENT5_SOLVE_H

// Sentinel value for adjacency linked list with no outward edges
#define NO_ADJACENCIES -1


/*
	Linked-list struct for adjacency list representation of a graph
*/
typedef struct adj_node
{
    //Vertex represents the current neighbor the adjacency list is pointing to.
    //Suppose there are 2 neighbors of a node, then by default vertex will point to first element.
    //We can use next to go to next element in the list
	int vertex;

    //To indicate the upcoming values, we use pointer next of type struct adj_node
	struct adj_node *next;   

}adj_node;



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
adj_node *read_adjacencies(FILE *fp);

//Defining struct Node
typedef struct Node { 
    //Value refers to the value of the node of LL where pointer is pointing
	int value; 
    //Next refers to the next element/node from the current node in LL
	struct Node *next;
} LLNode; 

// Creating a Queue structure, as a linked list made of nodes
typedef struct LLQueue { 
    //front represents the first element in the queue
    //rear represents the last element of the queue
	LLNode *front, *rear; 
} LLQueue; 




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
LLQueue *LLQ_create();

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
int LLQ_insert(LLQueue *LLQ, int data) ;

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
int LLQ_delete(LLQueue *LLQ);

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
int LLQ_delete_new(LLQueue *LLQ);

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
void LLQ_print(LLQueue *LLQ);

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
unsigned int LLQ_count(LLQueue* LLQ);

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
int LLQ_Search(LLQueue *LLQ, int data);

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
void LLQ_free(LLQueue *LLQ);



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
void freeAll(adj_node *list);


#endif //ASSIGNMENT5_MAZE_SOLUTION_H
