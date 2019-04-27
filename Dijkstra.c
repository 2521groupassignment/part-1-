 // Dijkstra ADT interface for Ass2 (COMP2521)
// Part 2 of Assignment 2
// Jing Jing Fan and Sarah Williams

#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


// define a very big number to set all initial dist to
#define INF 0x7FFFFFFF

#define LESS 1
#define EQUAL 2

// auxillary function
static void addPredMultiple(ShortestPaths *path, Vertex w, Vertex v);
static void addPred(ShortestPaths *path, Vertex w, Vertex v);
static int lessEqual (ShortestPaths *path, ItemPQ node, int weight, Vertex w);

/* Finds shortest paths from a given vertex to all other vertices, as discussed in the lectures.
 * Returns 'ShortestPaths' structure with the required information
 * (i.e. 'distance' array, 'predecessor' arrays, source and no_of_nodes in the graph)
 */
ShortestPaths dijkstra(Graph g, Vertex v) {
    
    assert(g != NULL);
    // set up the struct for the shortest path and initialise the variables
    // we know so far
    ShortestPaths *shortP = malloc(sizeof(ShortestPaths));
    shortP->src = v;
    shortP->noNodes = numVerticies(g); 
      
    // initialise the distance array
    shortP->dist = malloc(numVerticies(g) * sizeof(int));
    assert(shortP->dist != NULL);
    
    // initialise the predecessor array
    shortP->pred = malloc(numVerticies(g) * sizeof(PredNode *));
    assert(shortP->pred != NULL);
    
    
    // initialise an array to hold the nodes that have been visited in the graph
    int *seenSet = malloc(sizeof(int)*numVerticies(g));
    
    // assign the necessary values to the variables in the arrays
    for( int i = 0; i < numVerticies(g); i++) {
        // initial dist from src for all nodes in infinity
        shortP->dist[i] = INF;
        // the pred for each node is currently unknown, so set to NULL
        shortP->pred[i] = NULL;
        // every vertex is currently unseen
        seenSet[i] = -1;
    }
    
    // we already known the distance to the src is 0
    shortP->dist[v] = 0;
    
    // set up a new priority queue which will aid in traversing graph g
    PQ vertexSet = newPQ();
    // create a new pqnode, type ItemPQ and set its values
    ItemPQ newNode;
    newNode.key = v;
    newNode.value = shortP->dist[v];
    addPQ(vertexSet, newNode);
    
    
    // Implementation of Dijkstra's Algorithm
    
    // loop while the priority queue isn't empty
    while(PQEmpty(vertexSet) != 1){
        // dequeue the item with the smallest distance
        ItemPQ currNode = dequeuePQ(vertexSet);
        // ensure the vertex has not been seen before
        if(seenSet[currNode.key] != -1) continue;
        
        // then change the unseen vertex to the seen set, by changing
        // its value in the array to 2 (this could be any value)
        seenSet[currNode.key] = 2;
        
        // get all the neighbours of the current node
        AdjList neighbours = outIncident(g, currNode.key);
        
        // check all of the neighbours to the vertex, for the shortest distance
        // as neighbours is a linked list, we are simply performing a linked
        // list traversal 
        while(neighbours != NULL) {
           
            int lessOrEqual = lessEqual(shortP, currNode, neighbours->weight, neighbours->w);
            
            // case: distance found between curr node and neighbour is less than the
            // distance already set for that neighbouring node
            if(lessOrEqual == LESS){
                // update the distance array
                shortP->dist[neighbours->w] = (shortP->dist[currNode.key] + neighbours->weight);
                // update the pred list
                addPred(shortP, neighbours->w, currNode.key);
                // add the neighbouring node to the PQ
                newNode.key = neighbours->w;
                newNode.value = shortP->dist[currNode.key] + neighbours->weight;
                addPQ(vertexSet, newNode);
            // case: distance found between curr node and neighbour is the same
            // distance already set for that neighbouring node
            // this means there are multiple predeccesors to this neighbour
            } else if(lessOrEqual == EQUAL){
                // update the distance array
                shortP->dist[neighbours->w] = (shortP->dist[currNode.key] + neighbours->weight);
                // update the pred list
                addPredMultiple(shortP, neighbours->w, currNode.key);
                // add the neighbouring node to the PQ
                newNode.key = neighbours->w;
                newNode.value = shortP->dist[currNode.key] + neighbours->weight;
                addPQ(vertexSet, newNode);

            }
            neighbours = neighbours->next;
        }
                
    }
                
    // case: distances to some nodes are still set to inf
    // need to make them equal to 0
    int k;
    for(k = 0; k < numVerticies(g); k++){
        if(shortP->dist[k] == INF) {
        shortP->dist[k] = 0;
        }
    }


    return *shortP;
}

            
void showShortestPaths(ShortestPaths paths) {

    // print the distance to a node from the source node
    int i = paths.src;
    while(i < paths.noNodes){
        printf("%d", paths.dist[i]);
        i++;
    }
    printf("\n");

    // print the pred list

    PredNode *curr = paths.pred[paths.src];
    while(curr != NULL){
        printf("%d, ", curr->v);
        curr = curr->next;
    }
    printf("\n");


}


void  freeShortestPaths(ShortestPaths paths) {

    free(paths.pred);
    free(paths.dist);
}

// private function that adds a node to the predeccesor list when 
// there are multiple predeccesors

static void addPredMultiple(ShortestPaths *path, Vertex w, Vertex v){

    PredNode *new = malloc(sizeof(PredNode));
    new->v = v;
    new->next = NULL;

    PredNode *curr = path->pred[w];

    while(path->pred[w]->next != NULL) {
    path->pred[w] = path->pred[w]->next;
    }
    path->pred[w]->next = new;
    path->pred[w] = curr;


}
// private function that adds a node to the pred list, when this is
// the only predeccesor found
static void addPred(ShortestPaths *path, Vertex w, Vertex v){

    path->pred[w] = malloc(sizeof(PredNode));
    path->pred[w]->v = v;
    path->pred[w]->next = NULL;
    
}

//private function that determines if distance between the curr node and 
// a neighbouring node is less than or equal to the distance from the source
// node already set for this neighbouring node
static int lessEqual (ShortestPaths *path, ItemPQ node, int weight, Vertex w){

    if(path->dist[node.key] + weight < path->dist[w]){
        return LESS;
    } else if(path->dist[node.key] + weight == path->dist[w]){
        return EQUAL;
    }
    
    return 0;
    
}
