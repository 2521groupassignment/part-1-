// Graph.c 
// Part 1 of assignment 2
// implement all of the functions in Graph.h
// Sarah Williams and Jing Fan

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
    Adjlist *inedges;
    int nV;
    int nE;  
} GraphRep;

// dont know if we need ?? for inIncident and outIncident

typedef struct adjListRep{
    AdjList first;
    AdjList last; // maybe dont need
    AdjList curr; 
} adjListRep;


// need to add in static functions relating to linked list
// these functions are modified from the week 4 lecture exercises 
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

// make an adjlist
static AdjList newAdjList(void);


// create a new graph
Graph newGraph(int noNodes)
{

    assert(noNodes >= 0);
    int counter = 0;
    
    Graph new_graph = malloc(sizeof(GraphRep));
    assert(new_graph != NULL);
    new_graph->nV = noNodes;
    new_graph->nE = 0;
    
    // allocate memory for the array of lists
    new_graph->edges = malloc(sizeof (AdjList)); // this may need to change 
    for(counter = 0; counter < noNodes; counter++)
        new_graph->edges[counter] = NULL;
        
    return new_graph; 
}
  
void insertEdge(Graph g, Vertex src, Vertex dest, int weight){
    
    if(!inAL(g->edges[src], dest)){
        g->edges[src] = insertAL(g->edges[src], dest); // one way?
        g->edges[src]->weight = weight;
        g->nE++;
    }
       
}

void removeEdge(Graph g, Vertex src, Vertex dest){

    if(inAL(g->edges[src], dest)) {
        g->edges[src] = deleteAL(g->edges[src], dest);
        g->nE--;
    }
}

bool adjacent(Graph g, Vertex src, Vertex dest){
    assert(g!= NULL);
    
    return inAL(g->edges[src], dest);
}

// too simple??? nsh its fine
int  numVerticies(Graph g){
    
    return g->nV;

}

//  Returns a list of adjacent vertices
// on outgoing edges from a given vertex
AdjList outIncident(Graph g, Vertex v){
    assert(g != NULL);
    
   // AdjList outEdges = newAdjList();// need to set up a function that creates a new list
   
    return g->edges[v];
}

// Returns a list of adjacent vertices
// on incoming edges from a given vertex.

AdjList inIncident(Graph g, Vertex v){

    assert(g != NULL);
    
     return g->inedges[v];
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
        
    free(g);
        
}

// Auxillary Functions - 


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
static AdjList insertAL(AdjList L, Vertex vert) {

    adjListNode *new = malloc(sizeof(adjListNode));
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


static AdjList newAdjList (void) {

    adjListRep *new = malloc(sizeof(*new));
    *new = (adjListRep) { };
    return new;

}

