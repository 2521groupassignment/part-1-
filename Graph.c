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
static AdjList makeNode (Vertex n, int weight);
// inLL
static bool inAL(AdjList aList, Vertex vert);
// showAL
static void showAL(AdjList L);
// maybe make a valid checker for edges
static bool validV(Graph g, Vertex V);

//correct
// create a new graph
Graph newGraph(int noNodes)
{

    assert(noNodes >= 0);
    int i;
    
    Graph new_graph = malloc(sizeof(GraphRep));
    //assert(new_graph != NULL);
    new_graph->nV = noNodes;
    new_graph->nE = 0;
    
    // allocate memory for the array of lists
    new_graph->edges = malloc(noNodes * sizeof(AdjList)); 
    //assert(new_graph->edges != NULL);    
    new_graph->inedges = malloc(noNodes * sizeof(AdjList));
    for(i = 0; i < noNodes; i++){
        new_graph->edges[i] = NULL;
        new_graph->inedges[i] = NULL;
    }
        
    return new_graph; 
}

//correct  
void insertEdge(Graph g, Vertex src, Vertex dest, int weight){

    assert(g != NULL && validV(g, src) && validV(g, dest));
    
    if(!inAL(g->edges[src], dest)){
        AdjList newOut = makeNode(dest, weight);
        newOut->next = g->edges[src];
        g->edges[src] = newOut;

    }
    
    if(!inAL(g->inedges[dest], src)){
        AdjList newIn = makeNode(src, weight);
        newIn->next = g->inedges[dest];
        g->inedges[dest] = newIn;

    }

    g->nE++;       
}
//correct
void removeEdge(Graph g, Vertex src, Vertex dest){

    assert(g != NULL && validV(g, src) && validV(g, dest)); 
    
    if(inAL(g->edges[src], dest)) {
        AdjList curr = g->edges[src]->next;
        AdjList prev = g->edges[src];
        if (curr == NULL) {
            free(prev);
            g->edges[src] = NULL;
        } else if 
        while (curr != NULL) {
            if (dest == curr->w) {
                prev->next = curr->next;
                free(curr);
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    
    if(inAL(g->inedges[dest], src)){
        AdjList curr = g->inedges[dest]->next;
        AdjList prev = g->inedges[dest];
        if (curr == NULL) {
            free(prev);
            g->inedges[dest] = NULL;
        }
        while (curr != NULL) {
            if (src == curr->w) {
                prev->next = curr->next;
                free(curr);
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    g->nE--;
}

//correct
//checks if dest and src are adj to each other
bool adjacent(Graph g, Vertex src, Vertex dest){

    assert(g!= NULL && validV(g, src) && validV(g, dest));
    
    return (inAL(g->edges[src], dest));
}


//correct
int  numVerticies(Graph g){
    
    assert(g != NULL);
    
    return g->nV;

}

//correct
//  Returns a list of adjacent vertices
// on outgoing edges from a given vertex
AdjList outIncident(Graph g, Vertex v){
   
    assert(g != NULL && validV(g, v));
    
    return (g->edges[v]);
      
}

//correct
// Returns a list of adjacent vertices
// on incoming edges from a given vertex.

AdjList inIncident(Graph g, Vertex v){
    
    assert(g != NULL && validV(g, v));
    
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
    int counter = 0;
    AdjList curr = g->edges[counter]->next;
    AdjList prev = g->edges[counter];
    while (counter < g->nV) {
        while (curr != NULL) {
            AdjList temp = prev;
            prev = curr;
            curr = curr->next;
            free(temp);        
        }
        counter++;    
    }
        
    free(g->edges);
    free(g->inedges);   
    free(g);
        
}

// Auxillary Functions - 

//correct
static bool validV(Graph g, Vertex v){
    return(g != NULL && v >= 0 && (v < g->nV));
}

//correct
// function to make new nodes
static AdjList makeNode (Vertex n, int weight) { 

    AdjList new = malloc(sizeof(adjListNode)); 
    assert(new != NULL);
    new->w = n;
    new->weight = weight;
    new->next = NULL;
    return new;
}



// private function that check if an edge is already in the graph
static bool inAL(AdjList aList, Vertex vert) {

    AdjList curr = aList;
    int inAL = false;

    while (curr != NULL) {
        if (vert == curr->w) {
            inAL = true;
            break;
        }
        curr = curr->next;
    }
    
    return inAL;
}


static void showAL(AdjList L) {
    if(L == NULL) 
        printf("\n");
    else {
        printf("%d, ", L->w);
        showAL(L->next);
    }
}

