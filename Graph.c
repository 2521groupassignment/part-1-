// Graph.c 
// Part 1 of assignment 2
// implement all of the functions in Graph.h
// Jing Jing Fan and Sarah Williams

// use of adjacency list representation 

#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "Graph.h"

typedef struct GraphRep {
    AdjList *edges;
    AdjList *inedges;
    int nV;
    int nE;  
} GraphRep;


// Auxillary functions:

// makeNode
static AdjList makeNode (Vertex v, int weight);
// inAl
static bool inAL(AdjList L, Vertex v);
// showAL
static void showAL(AdjList L);
// maybe make a valid checker for edges
static bool validV(Graph g, Vertex v);


// create a new graph
Graph newGraph(int noNodes)
{

    assert(noNodes >= 0);
    int i;
    
    Graph newGraph = malloc(sizeof(GraphRep));
    assert(newGraph != NULL);
    newGraph->nV = noNodes;
    newGraph->nE = 0;
    
    // allocate memory for the array of lists
    
    newGraph->edges = malloc(noNodes * sizeof(AdjList)); 
    assert(newGraph->edges != NULL);
    newGraph->inedges = malloc(noNodes * sizeof(AdjList));
    assert(newGraph->inedges != NULL);
    
    // initialise the values in the lists
    for(i = 0; i < noNodes; i++){
        newGraph->edges[i] = NULL;
        newGraph->inedges[i] = NULL;
    }
        
    return newGraph; 
}

//insert an edge from src to dest in graph, g 
void insertEdge(Graph g, Vertex src, Vertex dest, int weight){

    assert(g != NULL && validV(g, src) && validV(g, dest));
    
    // checks the edge is not in the list, then add the edge
    // to both the edges and inedges lists
    
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

//remove the edge from src to dest in graph, g
void removeEdge(Graph g, Vertex src, Vertex dest){

    assert(g != NULL && validV(g, src) && validV(g, dest)); 
    
    // checks that an edge exists between the src and dest nodes
    // if an edge exists, remove it from both the edges and inedges lists
    
    if(inAL(g->edges[src], dest)) {
        AdjList curr = g->edges[src]->next;
        AdjList prev = g->edges[src];
        if (prev->w == dest) {
            free(prev);
            g->edges[src] = curr;
        }
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
        AdjList curr1 = g->inedges[dest]->next;
        AdjList prev1 = g->inedges[dest];
        if (prev1->w == src) {
            free(prev1);
            g->inedges[dest] = curr1;
        }
        while (curr1 != NULL) {
            if (src == curr1->w) {
                prev1->next = curr1->next;
                free(curr1);
                break;
            }
            prev1 = curr1;
            curr1 = curr1->next;
        }
    }
    g->nE--;
}


//checks if dest and src are adj to each other
bool adjacent(Graph g, Vertex src, Vertex dest){

    assert(g!= NULL && validV(g, src) && validV(g, dest));
    
    return (inAL(g->edges[src], dest));
}


//returns the number of vertices in graph, g
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
    
    assert(g != NULL && validV(g, v));
    
    return (g->inedges[v]);
}

// displays the graph 
void  showGraph(Graph g){

    assert(g != NULL);
    int i;
    
    printf("Number of verticies: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    
    for(i = 0; i < g->nV; i++){
        printf("[%d] - ", i);
        showAL(g->edges[i]);
    }
        
}

// frees all the memory associated with the graph
void  freeGraph(Graph g){

    assert(g != NULL);
    int counter = 0;
    
    while (counter < g->nV) {
    
        AdjList currEdges = g->edges[counter];
        AdjList currInEdges = g->inedges[counter];
        
        AdjList prevEdges = currEdges;
        AdjList prevInEdges = currInEdges;
        
        while (currEdges != NULL) {
        
            prevEdges = currEdges;
            currEdges = currEdges->next;        
            free(prevEdges);
        
        }    
                
        while (currInEdges != NULL) {
        
            prevInEdges = currInEdges;
            currInEdges = currInEdges->next;        
            free(prevInEdges);
        
        }    
        counter++;
    }    
        
    free(g);
        
}

// Auxillary Functions - 

// returns whether a vertex is valid
// conditions: vertex's value needs to be greater than
// zero and less than the total number of vertices in the graph
static bool validV(Graph g, Vertex v){
    return(g != NULL && v >= 0 && (v < g->nV));
}


// function to make new nodes
static AdjList makeNode (Vertex v, int weight) { 

    AdjList new = malloc(sizeof(adjListNode)); 
    assert(new != NULL);
    new->w = v;
    new->weight = weight;
    new->next = NULL;
    return new;
}



// checks if a node is already in the edge list
// i.e. if there is already an edge between two nodes
// adapted from the week 4 exercises, from the file list.c 
static bool inAL(AdjList L, Vertex v) {

    AdjList curr = L;
    int inAL = false;

    while (curr != NULL) {
        if (v == curr->w) {
            inAL = true;
            break;
        }
        curr = curr->next;
    }
    
    return inAL;
}

// displays the destination nodes from a given source vertex
// used in the showGraph function
// adapted from the week 4 exercises, from the file list.c 
static void showAL(AdjList L) {
    if(L == NULL) 
        printf("\n");
    else {
        printf("%d, ", L->w);
        showAL(L->next);
    }
}
