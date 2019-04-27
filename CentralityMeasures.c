
// Graph ADT interface for Ass2 (COMP2521)
// Part 3 of Assignment 2
// Jing Jing Fan and Sarah Williams

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

// auxillary functions
static double shortPathDistanceSum(Graph g, Vertex v); 
static double numReachable(Graph G, Vertex v);
static double count_path(ShortestPaths p, Vertex s, Vertex t);
static double count_vpath(ShortestPaths p, Vertex s, Vertex t, Vertex v);
static int countInAdjVs(Graph g, Vertex v);
static int countOutAdjVs(Graph g, Vertex v);

// private function that counts the number of paths from vertex s to t
static double count_path(ShortestPaths p, Vertex s, Vertex t) {
    if (s == t) {
        return 1.0;
    }

    double count = 0.0;
    PredNode *pred = p.pred[t];
    while (pred) {
        count += count_path(p, s, pred->v);
        pred = pred->next;
    }
    return count;
}

static double count_vpath(ShortestPaths p, Vertex s, Vertex t, Vertex v) {

    if (s == t) return 0.0;

    if (t == v) return count_path(p, s, v); 

    double count = 0.0;
    PredNode *pred = p.pred[t];
    while (pred) {
        count += count_vpath(p, s, pred->v, v);
        pred = pred->next;
    }
    return count;
}

// private function that returns the number of nodes directed towards vertex v
static int countInAdjVs(Graph g, Vertex v) {

    double i = 0.0;
    AdjList curr = inIncident(g, v);
    while (curr != NULL) {
        i++;
        curr = curr->next;
    }
   
    return i;

}

// private function that returns the number of edges directed outwards from vertex v
static int countOutAdjVs(Graph g, Vertex v) {

    double i = 0.0;
    AdjList curr = outIncident(g, v);
    while (curr != NULL) {
        i++;
        curr = curr->next;
    }
    
    return i;

}

// calculates the number of nodes directed out from the vertex 
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

// calculates the number of nodes directed towards the vertex 
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

// calculate the degree centrality of each vertex in a graph, this is the 
// sum of nodes directed towards and from each vertex
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

// calculates the centrality of a vertex, dependent upon its distance to 
// all other vertices in the graph 
NodeValues closenessCentrality(Graph g){

    NodeValues GraphCloseness;
       
    int nV = numVerticies(g);
	GraphCloseness.noNodes = nV;
	GraphCloseness.values = calloc(nV, sizeof(double));
	    
    Vertex v;
    double numReach;
    
    // for each of the nodes in the graph need to perform the Wasserman & Faust
    // equation
    
    for(v = 0; v < nV; v++){
    
        numReach = numReachable(g,v);

        double numerator = (numReach - 1) * (numReach - 1);
        double denominator = ((nV)-1)*(shortPathDistanceSum(g, v));
	 
        if (denominator == 0) {
            GraphCloseness.values[v] = 0;
        } else {
    	    GraphCloseness.values[v] = numerator/denominator;
        
        }

    }
	
	return GraphCloseness;
	
}

// private function that finds the sum of the distances from vertex v to 
// all other reachable nodes
static double shortPathDistanceSum(Graph g, Vertex v){

    double shortDistance = 0;
    int nV = numVerticies(g);
    
    ShortestPaths path;
    path = dijkstra(g, v);
    
    for(int i = 0; i < nV; i++){
        shortDistance = shortDistance + path.dist[i];
    }
   
   return shortDistance; 
    
}

// private function that finds the number of nodes reachable from the vertex v
static double numReachable (Graph g, Vertex v){

    ShortestPaths path = dijkstra(g, v);
    double nReachable = 1; //include self
    
    for( int i = 0; i < numVerticies(g); i++){
        if(path.dist[i] != 0){
            nReachable++;
        }
    }

    return nReachable;
    
}

// calculates the centrality of a vertex, dependent upon the number of shortest
// paths between two nodes
NodeValues betweennessCentrality(Graph g){

	int s, t, v;
	int nV = numVerticies(g);
    NodeValues betweenness;
	betweenness.noNodes = nV;
	betweenness.values =  calloc(nV,sizeof(double));
	for (s = 0; s < nV; s++) {
	    for (t = 0; t < nV; t++) {
	        for (v = 0; v < nV; v++) {
	            if (v != s && v != t) {
	            
	                ShortestPaths shortest_p = dijkstra(g, s);
	                double countp = count_path(shortest_p, s, t);
	                double count_vp = count_vpath(shortest_p, s, t, v);
	                if (countp != 0) betweenness.values[v] += count_vp/countp;
	            
	            }
            }
        }
    }
	            
	return betweenness;
}

NodeValues betweennessCentralityNormalised(Graph g){
    NodeValues betweenness = betweennessCentrality(g);
	double nV = numVerticies(g);
    NodeValues normalised_betweenness;
	normalised_betweenness.noNodes = nV;
	normalised_betweenness.values =  calloc(nV,sizeof(double));
		       
    int i = 0;
    while (i < nV) {
    
        normalised_betweenness.values[i] = betweenness.values[i]/((nV-1)*(nV-2));
        i++;
    
    }     
	return normalised_betweenness;
	            

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
