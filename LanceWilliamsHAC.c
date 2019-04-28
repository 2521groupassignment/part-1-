/*Lance-Williams Algorithm for Agglomerative Clustering
  Written by 
  COMP2521 2019 T1
*/
#include <stdlib.h>
#include <stdio.h>
#include "LanceWilliamsHAC.h"
#include "Graph.h"
#include <assert.h>
#define numVertices numVerticies
#define INF 0x7FFFFFFF

/* 
 * Finds Dendrogram using Lance-Williams algorithm (as discussed in the specs) 
   for the given graph g and the specified method for agglomerative clustering.
   Method value 1 represents 'Single linkage', and 2 represents 'Complete linkage'.
   For this assignment, you only need to implement the above two methods. 

   The function returns 'Dendrogram' structure (binary tree) with the required information.
 * 
 */
 
 
static void createDistArray (Graph g){
    int nV = numVerticies(g);
    double dist[nV][nV];   
    int v1, v2;
    
    //initialise everyting in array to INF
    for(v1 =0; v1 <nV; v1 ++) {
        for(v2 =0;v2 <nV;v2 ++) {
            dist[nV][nV] = INF;
        }
    }
    
    AdjList outNode = outIncident (g, v2);
    
    //store reciprical of largest weight to dist array
    v1 = 0;
    while(v1 <nV) {
        while (outNode != NULL) {
            double wt = outNode->w;
            if (1/dist[v1][outNode->w] < wt) {
                dist[v1][outNode->w] = 1/wt;
            }
            outNode = outNode->next;
        }
        v1++;
    }
    
    AdjList inNode = inIncident (g, v1);
    v1 = 0;
    while(v1 <nV) {
        while (inNode != NULL) {
            double wt = inNode->w;
            if (1/dist[v1][inNode->w] < wt) {
                dist[v1][inNode->w] = 1/wt;
            }
            inNode = inNode->next;
        }
        v1++;
    }
} 

//Creates a new dendogram node
DNode *newDendrogramNode(int vertex) {
	DNode *new = malloc(sizeof(DNode));
	new->vertex = vertex;
	new->right = malloc(sizeof(Dendrogram));
	new->left = malloc(sizeof(Dendrogram));
	new->right = NULL;
	new->left = NULL;
	return new;
}

 
Dendrogram LanceWilliamsHAC(Graph g, int method) {
    assert(g!=NULL);
    int nV = numVerticies(g);
    Dendrogram *dendA = calloc(nV,sizeof(Dendrogram));
    
    //Create dendA array
    Vertex v = 0;
    while (v < nV) {
        dendA[v] = newDendrogramNode(v);
        v++;
    }
    
        
        
    createDistArray (g);
    return NULL;
}


void freeDendrogram(Dendrogram d) {

	return;
}   



