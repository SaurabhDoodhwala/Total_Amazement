/*
 * CSE 6010 Assignment 5
 * Created by Sarah Bi (sbi30)
 * Last edited on 8 October 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for seeding random number generator
#include "generate.h"
//#include "maze_generation.c"

#define USAGE_STRING "USAGE:./executableName nRows nCols filename"

int main(int argc, char** argv){
// printf("begin code\n");

    /* ********** Code for reading command line inputs **********
    Check the number of inputs passed into the program
    arg[0]: name of the program
    arg[1]: number of rows of the maze (nRows)
    arg[2]: number of columns of the maze (nCols)
    arg[3]: name of the text file to which the maze information should be outputted (filename)
    So there should be 4 inputs passed in */
    if(argc != 4) {
        fprintf(stderr, "%s\nYou must pass your data file as an argument to this program.\n", USAGE_STRING);
        return 1;
    }

    // Declare command line input variables
    // All command line inputs are read as chars (strings)
    // Use atoi to convert chars to ints
    int nRows = atoi(argv[1]); // number of rows of maze graph (arg[1])
//printf("%s %d\n", "nRows:", nRows);
    int nCols= atoi(argv[2]); // number of columns of maze graph (arg[2])
//printf("%s %d\n", "nCols:", nCols);
    char *filename = argv[3]; // name of the textfile to which the maze information should be outputted (arg[3])
    int nNodes= nRows*nCols; // total number of nodes in the maze graph
//printf("%s %d\n", "nNodes:", nNodes);

    /* ********** Initialization of adjacency list **********
    Create array of structs (nodes) to hold adjacency information
    We will create an array of length nRows*nCols (nNodes)
    Each cell of the array will contain a node, which indicates what node that particular node is connected to
    Initially, we will set the visitStatus for all nodes to 0
    We will set the next and prev values to -1, to indicate no nodes are connect yet
    Just logically, we cannot have a connection to a node with number -1
    So we can use -1 to represent no connection */
//printf("initialize adj list\n");
    node *adjList = (node*) malloc((nNodes) * sizeof(node));
    for (int i=0; i<nNodes; i++){
        (adjList)[i].index = i;
        (adjList)[i].visitStatus = 0;
        (adjList)[i].prev = -1;
        for (int j=0; j<3; j++){
            adjList[i].next[j] = -1;
        }
    }

    /* Pick random node to start the maze
    Mark that node as visited
    Since rand() does not allow us to specify a range for our random numbers, we will use the % operator to set our range
    For each number generated by the random number generator, % the number by nNodes will give us a number between 0 to nNodes-1 (inclusive) */
    srand(time(NULL)); // seed the random number generator
    int start = rand() % nNodes; // generate random number between 0 and nNodes
//printf("%s %d\n", "start", start);
//int start = 4; // for testing- keep the same seed
    adjList[start].visitStatus = 1; // change status to 1 to indicate that we have visited the node but we have not visited all its neighbors

    // Declare variables
    int nextNode;
    int currentNode = start;
    int finish = -1;

    // ********** Begin DFS loop **********
//printf("begin DFS loop\n");
    while (1){

        // Randomly determine what next node to visit
        // If the randomly selected node has already been visited, we will keep randomly selecting until we find a node that hasn't been visited
        while(1){
           nextNode = findNextNode(currentNode, nRows, nCols);
           if (adjList[nextNode].visitStatus == 0){ // check to see if node has been visited already
               break;
           }
        }

        // Update the adjacency list
        adjList[nextNode].visitStatus = 1; // update the status of the node

        // Update the in-nodes adjacency list
        adjList[nextNode].prev= currentNode;

        /* Update the out-nodes adjacency list
        Since each node can have multiple out-nodes, we want to find the first empty index of the next array to store the next node
        We keep looping until we have found an empty index of the next array
        We know it is empty if the value inside is -1, which is what we initialized it to
        Just logically thinking, we cannot have a connection to a node that is numbered -1 */
        for (int i=0; i<3; i++){
            if (adjList[currentNode].next[i] == -1) { // if the value equals -1, that means it is empty
                adjList[currentNode].next[i] = nextNode;
                break;
            }
        }

        currentNode = nextNode; // update the current node
//printf("%d\n", currentNode);

        /* Check if all nodes are visited
        This is our termination condition
        If we hae visited all nodes, we have finished generating our maze
        We can break out of the DFS loop and print out the results */
        if (allNodesVisited(&adjList, nRows, nCols) ==  1){
            finish = currentNode; // keep track of the node that we finished on
            break; // leave the while loop once we have visited every node in the maze
        }

        // Check if currentNode has any available neighbors to connect to
        // If the currentNode has no neighbors, continue backtracking until a neighbor with a node is found
        while(1){
            if ((availableNeighbors(&adjList, currentNode, nRows, nCols)) == 1){
                break; // the currentNode has available neighbors, continue through the DFS loop
            }
            else { // the currentNode has no available neighbors
                adjList[currentNode].visitStatus = 2; // set the status to 2 to indicate that the node itself, and all neighbors has been visited (this is not technically necessary, but it helped me keep track of things
                currentNode = adjList[currentNode].prev; // backtrack to the previous node
//printf("%d\n", currentNode);
            }
        }
    }


    // ********** Print adjacency list to textfile **********
    FILE *file;
    file = fopen(filename, "w"); // write to a textfile with the name as specified in the command line input
    fprintf(file, "%d %d \n", nRows, nCols); // print number of rows and columns
    fprintf(file, "%d %d \n", start, finish); // print starting node and finishing node

    // Print the rest of the adjacency list
    for (int i=0; i<nNodes; i++){

        // Print prev array, starting at index 1 of the array
        // This contains nodes that come into the node (in-nodes)
        if (adjList[i].prev != -1){
            fprintf(file, "%d %s", adjList[i].prev, "");
        }

        // Print next array, starting at index 1 of the array
        // This contains nodes that this node goes to (out-nodes)
        for (int j=0; j<3; j++){
            if (adjList[i].next[j] != -1){ // if it equals -1, that means that index of the next array is empty
                fprintf(file, "%d %s", adjList[i].next[j], "");
            }
        }

        fprintf(file, "\n");
    }

    fclose(file); // close file once we are done writing

//printf("finish\n");

    free(adjList); // free all the space that we dynamically allocated for the adjacency list

    return 0;

}