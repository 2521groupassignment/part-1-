// Graph ADT interface for Ass2 (COMP2521)
// Part 3 of Assignment 2
// Jing Jing Fan and Sarah Williams 

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// Auxillary functions
static int countInAdjVs(Graph g, Vertex v);
static int countOutAdjVs(Graph g, Vertex); 

static double shortPathDistance(Graph g, Vertex v); 
static double numReachable(Graph G, Vertex v);

// private function that counts the numer of verticies that are directed
// towards the current vertex 
static int countInAdjVs(Graph g, Vertex v) {
    double i = 0;
    AdjList curr = inIncident(g, v);
    while (curr != NULL) {
        i++;
        curr = curr->next;
    } 
       
    return i;

}

// private function that counts the number of verticies that are directed 
// out from the current vertex 
static int countOutAdjVs(Graph g, Vertex v) {

    double i = 0;
    AdjList curr = outIncident(g, v);
    while (curr != NULL) {
        i++;
        curr = curr->next;
    }
    
    return i;

}


NodeValues outDegreeCentrality(Graph g){

	NodeValues GraphOutDegrees = {0};
	int nV = numVerticies(g);
    GraphOutDegrees.noNodes = nV;
    GraphOutDegrees.values = calloc(nV, sizeof(double));
    
    Vertex v;
    v = 0;
    while (v < nV) {
        GraphOutDegrees.values[v] = countOutAdjVs(g, v);
        v++;
    }
    
    return GraphOutDegrees;
}

NodeValues inDegreeCentrality(Graph g){
	NodeValues GraphInDegrees = {0};
	int nV = numVerticies(g);
   
    GraphInDegrees.noNodes = nV;
    GraphInDegrees.values = calloc(nV, sizeof(double));
    
    Vertex v;
    v = 0;
    while (v < nV) {
        GraphInDegrees.values[v] = countInAdjVs(g, v);
        v++;
    }


    return GraphInDegrees;

}

NodeValues degreeCentrality(Graph g) {
    NodeValues GraphDegrees = {0};
   
    int nV = numVerticies(g);
    GraphDegrees.noNodes = nV;
    GraphDegrees.values = calloc(nV, sizeof(double));
    
    Vertex v;
    v = 0;
    while (v < nV) {
        GraphDegrees.values[v] = countOutAdjVs(g, v) + countInAdjVs(g, v);
        v++;
    }

    return GraphDegrees;

}

NodeValues closenessCentrality(Graph g){

    //assert(g != NULL);

    NodeValues GraphCloseness = {0};
       
    int nV = numVerticies(g);
	GraphCloseness.noNodes = nV;
	GraphCloseness.values = calloc(nV,sizeof(double));
	    
    Vertex v;
    double numReach;
    
    // for each of the nodes in the graph need to perform the Wasserman & Faust
    // equation
    
    for( v = 0; v < nV; v++){
    
        numReach = numReachable(g,v);
        double numerator = (numReach - 1) * (numReach - 1);
        double denominator = ((nV)-1)*( shortPathDistance(g, v));
        GraphCloseness.values[v] = (numerator / denominator);
        if(numReach == 0) {
            GraphCloseness.values[v] = 0;
        }
    }
	
	
	return GraphCloseness;
	
}

// private function that finds the sum of the distances from vertex v to 
// all other reachable nodes
static double shortPathDistance(Graph g, Vertex v){

    double shortDistance = 0;
    
    ShortestPaths path;
    path = dijkstra(g, v);
    
    for(int i = 0; i < numVerticies(g); i++){
        shortDistance = shortDistance + path.dist[i];
    }
   
   return shortDistance; 
    
}

// private function that finds the number of nodes reachable from the vertex v
static double numReachable (Graph g, Vertex v){

    ShortestPaths path = dijkstra(g, v);
    double nReachable = 0;
    
    for( int i = 0; i < numVerticies(g); i++){
        if(path.dist[i] != 0){
            nReachable++;
        }
    }
    
    return nReachable;
    
}



NodeValues betweennessCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

NodeValues betweennessCentralityNormalised(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

void showNodeValues(NodeValues values){
    if (values.values == NULL) {
		printf("Invalid Values\n");
		return;
	}
	Vertex v = 0;;
	while (v < values.noNodes) {
	    printf("%d: %f\n", v, values.values[v]);
        v++;
    }

}

void freeNodeValues(NodeValues values){

    free(values.values);
	values.noNodes = 0;
	return;
}
