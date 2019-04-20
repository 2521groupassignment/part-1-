// Graph.c 
// Part 1 of assignment 2
// implement all of the functions in Graph.h
// Sarah Williams and Jing Jing Fan

// use of adjacency list representation 

#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "Graph.h"

// Put in the rep of a graph (node is already in graph.h ??)
typedef struct GraphRep {
    AdjList *edges;
    AdjList *inedges;
    int nV;
    int nE;  
} GraphRep;


// need to add in static functions relating to the adjancency list
// these functions are modified from the week 4 lecture exercises 

// make a new node
static adjListNode *makeNode (Vertex n);
// inLL
static bool inAL(AdjList aList, Vertex vert);
// insertLL
static AdjList insertAL(AdjList L, Vertex vert);
// deleteLL
static AdjList deleteAL(AdjList L, Vertex vert);
// freeLL
static void freeAL(AdjList L);
// showAL
static void showAL(AdjList L);
// maybe make a valid checker for edges
static bool validV(Graph g, Vertex V);

// create a new graph
Graph newGraph(int noNodes)
{

    assert(noNodes >= 0);
    int i;
    
    Graph new_graph = malloc(sizeof(GraphRep));
    assert(new_graph != NULL);
    new_graph->nV = noNodes;
    new_graph->nE = 0;
    
    // allocate memory for the array of lists
    new_graph->edges = malloc(noNodes * sizeof(AdjList)); 
    assert(new_graph->edges != NULL);
    
    new_graph->inedges = malloc(noNodes * sizeof(AdjList));
    for(i = 0; i < noNodes; i++){
        new_graph->edges[i] = NULL;
        new_graph->inedges[i] = NULL;
    }
        
    return new_graph; 
}
  
void insertEdge(Graph g, Vertex src, Vertex dest, int weight){

    assert(g != NULL && validV(g, src) && validV(g, dest));
    
    if(!inAL(g->edges[src], dest)){
        g->edges[src] = insertAL(g->edges[src], dest); 
        g->edges[src]->weight = weight; // get this checked
        g->nE++;
    }
    
    if(!inAL(g->inedges[dest], src)){
        g->inedges[dest] = insertAL(g->inedges[dest], src);
    }
       
}

void removeEdge(Graph g, Vertex src, Vertex dest){

    assert(g != NULL && validV(g, src) && validV(g, dest)); 
    
    if(inAL(g->edges[src], dest)) {
        g->edges[src] = deleteAL(g->edges[src], dest);
        g->nE--;
    }
    
    if(inAL(g->edges[dest], src)){
        g->inedges[dest] = deleteAL(g->inedges[dest], src);
    }
}

bool adjacent(Graph g, Vertex src, Vertex dest){

    assert(g!= NULL && validV(g, src) && validV(g, dest));
    
    return (inAL(g->edges[src], dest));
}


int  numVerticies(Graph g){
    
    assert(g != NULL);
    
    return g->nV;

}

//  Returns a list of adjacent vertices
// on outgoing edges from a given vertex
AdjList outIncident(Graph g, Vertex v){
   
    assert(g != NULL && validV(g, v));
    
    return (g->edges[v]);
      
}

// Returns a list of adjacent vertices
// on incoming edges from a given vertex.

AdjList inIncident(Graph g, Vertex v){
    
    assert(g != NULL && validV(g,v));
    
    return (g->inedges[v]);
}

// displays the graph (any implementation)
void  showGraph(Graph g){

    assert(g != NULL);
    int counter;
    
    for(counter = 0; counter < g->nV; counter++){
        printf("[%d] - ", counter);
        showAL(g->edges[counter]);
    }
        
}

// frees all the memory associated with the graph
void  freeGraph(Graph g){

    assert(g != NULL);
    int counter;
    
    for (counter = 0; counter < g->nV; counter++)
        freeAL(g->edges[counter]); // add in aux function
    free(g->edges);   
    free(g);
        
}

// Auxillary Functions - 

static bool validV(Graph g, Vertex v){
    return(g != NULL && v >= 0 && (v < g->nV));
}

// function to make new nodes
static adjListNode *makeNode (Vertex n) { 

    adjListNode *new = malloc(sizeof(adjListNode)); 
    assert(new != NULL);
    new->w = n;
    new->weight = 0;
    new->next = NULL;
    return new;
}



// private function that check if an edge is already in the graph
static bool inAL(AdjList aList, Vertex vert) {
    
    if(aList == NULL) 
        return false;
    if (aList->w == vert) 
        return true;
        
    
    return inAL(aList->next, vert);
}

// need to do something with weights??
// probably change this 
static AdjList insertAL(AdjList L, Vertex vert) { // change this to an int ??
 
    adjListNode *new = makeNode(vert);
    new->w = vert;
    new->next = L;
    
    return new;
   
}

static AdjList deleteAL(AdjList L, Vertex vert) {

    if(L == NULL) 
        return L;
    if(L->w == vert) 
     return L->next;
    
    L->next = deleteAL(L->next, vert);
    return L;

}

static void showAL(AdjList L) {
    if(L == NULL) 
        printf("\n");
    else {
        printf("%d, ", L->w);
        showAL(L->next);
    }
}

static void freeAL(AdjList L) {
    if(L != NULL) {
        freeAL(L->next);
        free(L);
    }  
}
