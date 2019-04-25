// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>


NodeValues outDegreeCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}
NodeValues inDegreeCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}
NodeValues degreeCentrality(Graph g) {
	NodeValues throwAway = {0};
	return throwAway;
}
// WORK ON THIS FUNCTION
NodeValues closenessCentrality(Graph g){
/
    assert(g != NULL);
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
	
	return *new;
	//NodeValues throwAway = {0};
	//return throwAway;
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

}

void freeNodeValues(NodeValues values){

}
