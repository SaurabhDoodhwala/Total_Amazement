/*
 * CSE 6010 Assignment 5
 * Created by Sarah Bi (sbi30)
 * Last edited on 8 October 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for seeding random number generator
#include "generate.h"


/*
 * Function:  findNextNode
 * --------------------
 * Description:
 *      Randomly determines a direction for the maze to go
 * Params:
 *      int currentNode- index of the currentNode
 *      int nRows- number of rows in the maze
 *      int nCols- number of columns in the maze
 * Returns:
 *      int nextNode- the index of the next node that the maze should connect to
 */
int findNextNode(int currentNode, int nRows, int nCols){

    // Initialize the value of next node
    // If we find a next node to go to, the value of nextNode will be updated
    // If, for some reason, we do not enter any of if, else if, or else loops, we will fall straight to the return statement
    // In this case, we just return the location of the node that we were already at
    int nextNode = currentNode;
    int direction;

    // If currentNode is at top left of the maze
    // The only options for nodes to go to are:
    // 1. To the right (0)
    // 2. Below (1)
    if (currentNode == 0){ // it is in the top left of the maze
        direction = rand() % 2; // generate random number between 0  and 1
        if (direction == 0){ // go to the right
            nextNode = currentNode + 1;
        }
        else if (direction == 1){ // go down
            nextNode = currentNode + nCols;
        }
    }

    // If currentNode is at the top right corner of the maze
    // The only options for nodes to go to are:
    // 1. To the left (0)
    // 2. Below (1)
    else if (currentNode == nCols-1){
        direction = rand() % 2; // generate random number between 0 and 1
        if (direction == 0){ // go to the left
            nextNode = currentNode - 1;
        }
        else if (direction == 1){ // go down
            nextNode = currentNode + nCols;
        }
    }

    // If currentNode is at the bottom left corner of the maze
    // The only options for nodes to go to are:
    // 1. Above (0)
    // 2. To the right (1)
    else if (currentNode == (nRows*nCols-nCols)){ // it is at bottom left corner of maze
        direction = rand() % 2; // generate random number between 0 and 1
        if (direction == 0){ // go above
            nextNode = currentNode - nCols;
        }
        else if (direction == 1){ // go to the right
            nextNode = currentNode + 1;
        }
    }

    // If currentNode is at the bottom right corner of the maze
    // The only options for node to go to are:
    // 1. Above (0)
    // 2. To the left (1)
    else if (currentNode == nRows*nCols-1){ // it is at bottom right corner of the maze
        direction = rand() % 2; // generate random number between 0 and 1
        if (direction == 0){ // go above
            nextNode = currentNode - nCols;
        }
        else if (direction == 1){ // go to the left
            nextNode = currentNode - 1;
        }
    }

    // If currentNode is on the top row of the maze
    // The only options for nodes to go to are:
    // 1. To the right (0)
    // 2. Below (1)
    // 3. To the left (2)
    else if ((currentNode > 0) && (currentNode < nCols)){ // it is in the top row of the maze
        direction = rand() % 3; // generate random number between 0 and 2
        if (direction == 0){ // go to the right
            nextNode = currentNode + 1;
        }
        else if (direction == 1){ // go down
            nextNode = currentNode + nCols;
        }
        else if (direction == 2){ // go to the left
            nextNode = currentNode - 1;
        }
    }

    // If currentNode is on the bottom row of the maze
    // The only options for nodes to go to are:
    // 1. Above (0)
    // 2. To the right (1)
    // 3. To the left (2)
    else if ((currentNode > nRows*nCols-nCols) && (currentNode < nRows*nCols-1)){ // it is in the bottom row of the maze
        direction = rand() % 3; // generate random number between 0 and 2
        if (direction == 0){ // go to the above
            nextNode = currentNode - nCols;
        }
        else if (direction == 1){ // to the right
            nextNode = currentNode + 1;
        }
        else if (direction == 2){ // go to the left
            nextNode = currentNode - 1;
        }
    }

    // If currentNode is on the left edge of the maze
    // The only options for nodes to go to are:
    // 1. Above (0)
    // 2. To the right (1)
    // 3. Below (2)
    else if (currentNode % nCols == 0){ // it is on the left edge of the maze
        direction = rand() % 3; // generate random number between 0 and 2
        if (direction == 0){ // go above
            nextNode = currentNode - nCols;
        }
        else if (direction == 1){ // to the right
            nextNode = currentNode + 1;
        }
        else if (direction == 2){ // go below
            nextNode = currentNode + nCols;
        }
    }

    // If currentNode is on the right edge of the maze
    // The only options for the nodes to go to are:
    // 1. Above (0)
    // 2. Below (1)
    // 3. To the left (2)
    else if ((currentNode+1)%nCols == 0){ // it is on the right edge of the maze
        direction = rand() % 3; // generate random number between 0 and 2
        if (direction == 0){ // go to the above
            nextNode = currentNode - nCols;
        }
        else if (direction == 1){ // go below
            nextNode = currentNode + nCols;
        }
        else if (direction == 2){ // go to the left
            nextNode = currentNode - 1;
        }
    }

    // If currentNode is anything else
    // The nodes that it can go to are
    // 1. Above (0)
    // 2. To the right (1)
    // 3. Below (2)
    // 4. To the left (3)
    else {
        direction = rand() % 4; // generate random number between 0 and 2
        if (direction == 0) { // go to the above
            nextNode = currentNode - nCols;
        } else if (direction == 1) { // go to the right
            nextNode = currentNode + 1;
        } else if (direction == 2) { // go below
            nextNode = currentNode + nCols;
        } else { // go to the right
            nextNode = currentNode - 1;
        }
    }
    return nextNode;
}

/*
 * Function:  allNodesVisited
 * --------------------
 * Description:
 *      Checks to see if all nodes have been visited
 * Params:
 *      node **adjList- array containing each of the nodes of the maze
 *      int nRows- number of rows in the maze
 *      int nCols- number of columns in the maze
 * Returns:
 *      int 0- if not all nodes have been visited
 *      int 1- if all nodes have been visited
 */
int allNodesVisited(node **adjList, int nRows, int nCols){
    for (int i=0; i<nRows*nCols; i++){
        if ((*adjList)[i].visitStatus == 0){ // if at least 1 node has not been visited, then we know immediately we have not visited all nodes
            return 0;
        }
    }
    return 1; // return 1 if all nodes have been visited (none have visitStatus of 0)
}

/*
 * Function:  availableNeighbors
 * --------------------
 * Description:
 *      Checks to see if the current node has any neighboring nodes that it can visit
 *      For currentNode, check the surrounding neighbor's visitStatus value
 *      If at least one neighbor has a visitStatus == 0, it means that neighbor has not been visited
 *      Then we automatically know that currentNode has available neighbor(s) to visit
 * Params:
 *      int currentNode- index of the currentNode
 *      int nRows- number of rows in the maze
 *      int nCols- number of columns in the maze
 * Returns:
 *      int 0- no available neighbors (all neighbors have been visited already)
 *      int 1- there are available neighbors
 */
int availableNeighbors(node **adjList, int currentNode, int nRows, int nCols){

    int available=0; // determines if the node has any neighboring nodes to go to that have not already been visited

    // If currentNode is at the top left corner of the maze
    // The neighbors that need to be checked are:
    // 1. To the right
    // 2. Below
    if (currentNode == 0){
        if (((*adjList)[currentNode+1].visitStatus == 0) || ((*adjList)[currentNode+nCols].visitStatus == 0)){ // check to the right and below
            available = 1;
        }
    }

    // If currentNode is at the top right corner of the maze
    // The neighbors that need to be checked are:
    // 1. To the left
    // 2. Below
    else if (currentNode == nCols-1){
        if (((*adjList)[currentNode-1].visitStatus == 0) || ((*adjList)[currentNode+nCols].visitStatus == 0)){ // check to the left and below
            available = 1;
        }
    }

    // If currentNode is at the bottom left corner of the maze
    // The neighbors that need to be checked are:
    // 1. To the right
    // 2. Above
    else if (currentNode == nRows*nCols - nCols){
        if (((*adjList)[currentNode+1].visitStatus == 0) || ((*adjList)[currentNode-nCols].visitStatus == 0)){ // check to the right and above
            available = 1;
        }
    }

    // If currentNode is at the bottom right corner of the maze
    // The neighbors that need to be checked are:
    // 1. To the left
    // 2. Above
    else if (currentNode == nRows*nCols-1){
        if (((*adjList)[currentNode-1].visitStatus == 0) || ((*adjList)[currentNode-nCols].visitStatus == 0)){ // check to the left and above
            available = 1;
        }
    }

    // If currentNode is on the top row of the maze
    // The neighbors that need to be checked are:
    // 1. To the left
    // 2. To the right
    // 3. Below
    else if ((currentNode > 0) && (currentNode < nCols-1)){
        if (((*adjList)[currentNode-1].visitStatus == 0) || ((*adjList)[currentNode+1].visitStatus == 0)
        || ((*adjList)[currentNode+nCols].visitStatus == 0)) { // check left, right, and below
            available = 1;
        }
    }

    // If currentNode is on the bottom row of the maze
    // The neighbors that need to be checked are:
    // 1. To the left
    // 2. To the right
    // 3. Above
    else if ((currentNode > nRows*nCols-nCols) && (currentNode < nRows*nCols-1)){
        if (((*adjList)[currentNode-1].visitStatus == 0) || ((*adjList)[currentNode+1].visitStatus == 0)
            || ((*adjList)[currentNode-nCols].visitStatus == 0)) { // check left, right, and above
            available = 1;
        }
    }

    // If currentNode is on the left edge of the maze
    // The neighbors that need to be checked are:
    // 1. Above
    // 2. To the right
    // 3. Below
    else if (currentNode % nCols == 0){
        if (((*adjList)[currentNode-nCols].visitStatus == 0) || ((*adjList)[currentNode+1].visitStatus == 0)
            || ((*adjList)[currentNode+nCols].visitStatus == 0)) { // check above, right, and below
            available = 1;
        }
    }

    // If currentNode is on the right edge of the maze
    // The neighbors that need to be checked are:
    // 1. Above
    // 2. To the left
    // 3. Below
    else if ((currentNode+1) % nCols == 0){
        if (((*adjList)[currentNode-nCols].visitStatus == 0) || ((*adjList)[currentNode-1].visitStatus == 0)
            || ((*adjList)[currentNode+nCols].visitStatus == 0)) { // check above, left, and below
            available = 1;
        }
    }

    // If currentNode is anywhere else in the maze
    // The neighbors to check are:
    // 1. Above
    // 2. To the right
    // 3. Below
    // 4. To the left
    else {
        if (((*adjList)[currentNode-nCols].visitStatus == 0) || ((*adjList)[currentNode+1].visitStatus == 0)
            || ((*adjList)[currentNode+nCols].visitStatus == 0) || ((*adjList)[currentNode-1].visitStatus == 0)) { // check above, right, below, and left
            available = 1;
        }
    }

    return available;
}
