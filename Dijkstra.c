// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


// define a very big number to set all initial dist to
#define INF 0x7FFFFFFF

// auxillary function
static void add_pred(ShortestPaths *path, Vertex w, Vertex v);

ShortestPaths dijkstra(Graph g, Vertex v) {
    
    assert(g != NULL);
    // set up the struct for the shortest path and initialise the variables
    // we know so far
    ShortestPaths *short_p = malloc(sizeof(ShortestPaths));
    short_p->src = v;
    short_p->noNodes = numVerticies(g);   
	// initialise the distance array
	short_p->dist = malloc(numVerticies(g) * sizeof(int));
	assert(short_p->dist != NULL);
	// initialise the predecessor array
	short_p->pred = malloc(numVerticies(g) * sizeof(PredNode *));
	assert(short_p->pred != NULL);
	
	
	// initialise an array to hold the nodes that have been visited in the graph
	int seen_set[numVerticies(g)];
	
	// assign the necessary values to the variables in the arrays
	for( int i = 0; i < numVerticies(g); i++) {
	    // initial dist from src for all nodes in infinity
	    short_p->dist[i] = INF;
	    // the pred for each node is currently unknown, so set to NULL
	    short_p->pred[i] = NULL;
	    // every vertex is currently unseen
	    seen_set[i] = -1;
	}

	// we already known the distance to the src is 0
	short_p->dist[v] = 0;
	
	// set up a new priority queue which will aid in traversing graph g
	PQ vertex_set = newPQ();
	// create a new pqnode, type ItemPQ and set its values
	ItemPQ new_pqnode;
	new_pqnode.key = v;
	new_pqnode.value = short_p->dist[v];
	addPQ(vertex_set, new_pqnode);
	
	
	// Implementation of Dijkstra's Algorithm
	
	// i.e. while the priority queue isn't empty
	while(PQEmpty(vertex_set) != 1){
	    // dequeue the item with the smallest distance
	    ItemPQ curr_node = dequeuePQ(vertex_set);
	    // ensure the vertex has not been seen before
	    if(seen_set[curr_node.key] != -1) continue;
	    
	    // then change the unseen vertex to the seen set, by changing
	    // its value in the array to 1 (this could be any value)
	    seen_set[curr_node.key] = 1;
	    
	    // get all the neighbours of the current node
	    AdjList neighbours = outIncident(g, curr_node.key);
	    // check all of the neighbours to the vertex, for the shortest distance
	    // as neighbours is a linked list, we are simply performing a linked
	    // list traversal 
	    while(neighbours != NULL) {
	        neighbours = neighbours->next;
	        // need to deal with the cases of distance less than and distance 
	        // equal to
	        // i.e. if the distance so far to the curr node plus the weight to the neighbour
	        // if less than the weight previously set to this neighbouring node
	        // update the distance
	        if((short_p->dist[curr_node.key] + neighbours->weight) < short_p->dist[neighbours->w]){
	            // update the distance array
	            short_p->dist[neighbours->w] = (short_p->dist[curr_node.key] + neighbours->weight);
	            // update the pred list
	            // maybe make this it's own function
	            short_p->pred[neighbours->w] = malloc(sizeof(PredNode));
	            short_p->pred[neighbours->w]->v = curr_node.key;
	            short_p->pred[neighbours->w]->next = NULL;
	        } else if((short_p->dist[curr_node.key] + neighbours->weight) == short_p->dist[neighbours->w]){
	            // update the distance array
	            short_p->dist[neighbours->w] = (short_p->dist[curr_node.key] + neighbours->weight);
	            // update the pred list
	            add_pred(short_p, neighbours->w, curr_node.key);
	            
	            
	            
	        }
	        new_pqnode.key = neighbours->w;
	        new_pqnode.value = neighbours->weight;
	        addPQ(vertex_set, new_pqnode);
	    }
	    
	    neighbours = neighbours->next;
	    
	}
	
	// case: distances to some nodes are still set to inf
	// need to make them equal to 0
	int k;
	for(k = 0; k < numVerticies(g); k++){
	    if(short_p->dist[k] == INF) {
	        short_p->dist[k] = 0;
	    }
	}
	
	free(seen_set);

	return *short_p;
}

void showShortestPaths(ShortestPaths paths) {

    int i = paths.src;
    //int i;
    for(i = 0; i < paths.noNodes; i++){
        printf("%d", paths.dist[i]);
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

static void add_pred(ShortestPaths *path, Vertex w, Vertex v){
    
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
