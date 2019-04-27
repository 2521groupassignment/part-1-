// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

// Auxillary functions
static double shortPathDistance (Graph g, Vertex v); 
static double numReachable (Graph G, Vertex v);

int countInAdjVs(Graph g, Vertex v) 
{
    double i = 0;
    AdjList curr = inIncident(g, v);
    while (curr != NULL) {
        i++;
        curr = curr->next;
    }
    //printf("hello %f\n", i);
    
    return i;

}

int countOutAdjVs(Graph g, Vertex v) {

    double i = 0;
    AdjList curr = outIncident(g, v);
    while (curr != NULL) {
        i++;
        curr = curr->next;
    }
    
    //printf("hello %d\n", i);
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
   
    /*int nV = numVerticies(g);
    GraphDegrees.noNodes = nV;
    GraphDegrees.values = calloc(nV, sizeof(double));
    
    Vertex v;
    v = 0;
    while (v < nV) {
        GraphDegrees.values[v] = countOutAdjVs(g, v) + countInAdjVs(g, v);
        v++;
    }*/

    return GraphDegrees;

}

NodeValues closenessCentrality(Graph g){

    assert(g != NULL);

    NodeValues GraphCloseness = {0};
       
    int nV = numVerticies(g);
	GraphCloseness.noNodes = nV;
	GraphCloseness.values = calloc(nV,sizeof(double));
	    
    Vertex v;
    double num_reach;
    
    // for each of the nodes in the graph need to perform the Wasserman & Faust
    // equation
    
    for( v = 0; v < nV; v++){
    
        num_reach = numReachable(g,v);
        double numerator = (num_reach - 1) * (num_reach - 1);
        double denominator = (numVerticies(g)-1)*( shortPathDistance(g, v));
        GraphCloseness.values[v] = (numerator / denominator);
        
        if(num_reach == 0) {
            GraphCloseness.values[v] = 0;
        }
    }
	
    return GraphCloseness;
	
}

static double shortPathDistance(Graph g, Vertex v){

    double shortDistance = 0;
    
    ShortestPaths path;
    path = dijkstra(g, v);
    for(Vertex i = 0; i < numVerticies(g); i++){
        shortDistance += path.dist[i];
    }
   
   return shortDistance; 
    
}

static double numReachable (Graph g, Vertex v){
    ShortestPaths path = dijkstra(g, v);
    double n_reachable = 0;
    
    for( int i = 0; i < numVerticies(g); i++){
        if(path.dist[i] != 0){
            n_reachable++;
        }
    }
    
    return n_reachable;
    
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
