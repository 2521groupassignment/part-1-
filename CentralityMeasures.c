// Graph ADT interface for Ass2 (COMP2521)
// Part 3 of Assignment 2
// Jing Jing Fan and Sarah Williams

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"

// auxillary functions
static double shortPathDistanceSum(Graph g, Vertex v); 
static double numReachable(Graph G, Vertex v);
static double countPath(ShortestPaths path, Vertex s, Vertex t);
static double countVPath(ShortestPaths path, Vertex s, Vertex t, Vertex v);
static int countInAdjVs(Graph g, Vertex v);
static int countOutAdjVs(Graph g, Vertex v);

// counts shortest paths from s to t
static double countPath(ShortestPaths path, Vertex s, Vertex t) {

    // counts a path when recursion reaches the source
    if (s == t) {
        return 1.0;
    }

    double count = 0.0;
    PredNode *pred = path.pred[t];
    //keeps iterating through the pred of the pred and etc.
    while (pred) {
        count += countPath(path, s, pred->v);
        pred = pred->next;
    }
    return count;
}

// counts shortest paths from s to t passing through v
static double countVPath(ShortestPaths path, Vertex s, Vertex t, Vertex v) {

    if (s == t) {
        return 0.0;
    }

    //if v is in the path, count the path
    if (v == t) {
        return countPath(path, s, v); 
    }

    double count = 0.0;
    PredNode *pred = path.pred[t];
    //keeps iterating through the pred of the pred and etc.
    while (pred) {
        count += countVPath(path, s, pred->v, v);
        pred = pred->next;
    }
    return count;
}

// counts number of nodes connected to v through in edges
static int countInAdjVs(Graph g, Vertex v) {

    double i = 0.0;
    AdjList curr = inIncident(g, v);
    while (curr != NULL) {
        i++;
        curr = curr->next;
    }
   
    return i;

}

// counts number of nodes connected to v through out edges
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
    assert(GraphOutDegrees.values != NULL);
    
    Vertex v;
    v = 0;
    while (v < nV) {
        //store results of individual v into an array
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
    assert(GraphInDegrees.values != NULL);
    
    Vertex v;
    v = 0;
    while (v < nV) {
        //store results of individual v into an array
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
    assert(GraphDegrees.values != NULL);
    
    Vertex v;
    v = 0;
    while (v < nV) {
        //store results of individual v into an array
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
	assert(GraphCloseness.values != NULL);
	    
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

//finds the sum of shortest path weight from v to all other nodes
static double shortPathDistanceSum(Graph g, Vertex v){

    double shortDistance = 0.0;
    int nV = numVerticies(g);
    
    ShortestPaths path;
    path = dijkstra(g, v);
    
    for(int i = 0; i < nV; i++){
        // summming all the shortest dists of v
        shortDistance = shortDistance + path.dist[i];
    }
   
   return shortDistance; 
    
}

// find how many reachable nodes from v including v
static double numReachable (Graph g, Vertex v){

    ShortestPaths path = dijkstra(g, v);
    double nReachable = 1.0; //include self
    
    int nV = numVerticies(g);
    
    for( int i = 0; i < nV; i++){
        // if dist is not 0 then it is reachable
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
	assert(betweenness.values != NULL);
	
	//loop source vertex
	for (s = 0; s < nV; s++) {
	    //loop destination vertex
	    for (t = 0; t < nV; t++) {
	        //loop vertex that is potentially between s and t
	        for (v = 0; v < nV; v++) {
	            if (v != s && v != t) {
	            
	                ShortestPaths path = dijkstra(g, s);
	                double countp = countPath(path, s, t);
	                double count_vp = countVPath(path, s, t, v);
	                // store betweeness result of each v into an array
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
    NodeValues normalisedBetweenness;
	normalisedBetweenness.noNodes = nV;
	normalisedBetweenness.values =  calloc(nV,sizeof(double));
	assert(normalisedBetweenness.values != NULL);
		       
    int i = 0;
    while (i < nV) {
    
        normalisedBetweenness.values[i] = betweenness.values[i]/((nV-1)*(nV-2));
        i++;
    
    }     
	return normalisedBetweenness;
	            

}


void showNodeValues(NodeValues values){

    if (values.values == NULL) {
		printf("Invalid Values\n");
		return;
	}
	Vertex v;
	for (v = 0; v < values.noNodes; v++) {
	    printf("%d: %f\n", v, values.values[v]);
    }

}

void freeNodeValues(NodeValues values){

    free(values.values);
	values.noNodes = 0;
	return;
}
