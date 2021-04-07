/*
 * CSE 6010 Assignment 5
 * Created by Sarah Bi (sbi30)
 * Last edited on 8 October 2020
 */

#ifndef ASSIGNMENT5_GENERATE_H
#define ASSIGNMENT5_GENERATE_H

typedef struct node{

    int index; // number indicating the index of the node in the maze graph

    /* Number indicating whether node has been visited or not
    0- node has not been visited
    1- node has been visited
    2- node and all its neighbors have been visited */
    int visitStatus;

    /* The way this particular assignment is set up, you can only move up, down, left, or right from each node
    Which means that each node can have 4 connections at maximum
    Each node can have one (and only one) previous node, meaning that each node can only come one (and only one) node
    This leaves a maximum of 3 nodes that each node can go to (these are the next nodes) */
    int prev; // number indicating index of node that it came from
    int next[3]; // array containing the indices of the nodes that are out-nodes
    //int numberOfNextElements; // counter to keep track of how many out-nodes there are s

} node;

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
int findNextNode(int currentNode, int nRows, int nCols);

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
int allNodesVisited(node **adjList, int nRows, int nCols);

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
int availableNeighbors(node **adjList, int currentNode, int nRows, int nCols);

#endif //ASSIGNMENT5_GENERATE_H
