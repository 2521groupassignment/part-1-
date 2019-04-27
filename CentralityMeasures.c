// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

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
    /*assert(g != NULL);
	NodeValues *new = malloc(sizeof(NodeValues));
	new->noNodes = numVerticies(g);
	new->values = malloc(numVerticies(g) * sizeof(double));
	
	
	// this initialises all of the values to 0
	// in the case that the node has no reachable edges, the value (closeness
	// centrality) will stay at 0
	for(int i = 0; i < numVerticies(g); i++){
        new->values[i] = 0;
    }
    
    Vertex v;
    double num_reach;
    
    // for each of the nodes in the graph need to perform the Wasserman & Faust
    // equation
    
    for( v = 0; v < numVerticies(g); v++){
        num_reach = // add in function here to find nodes reachable 
        double numerator = (num_reach - 1) * (num_reach - 1);
        double denominator = (numVerticies(g)-1)*(//find variable for the dist. total);
        new->values[v] = numerator / denominator;
    }
	
	return *new;*/
	NodeValues throwAway = {0};
	return throwAway;

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
