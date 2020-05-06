#ifndef _WEIGHTED_GRAPH_
#define _WEIGHTED_GRAPH_

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <vector>

#include "EdgeNode.h"

// WeightedGraph class (Graph with edges that contain values)
// Needs work with addressing some hard coding.
class WeightedGraph{
private: 
    // Holds the amount of vertexes for later calculations
    int vertexes;

public:
    // For identifying undirected and directered edges.
    bool directed;
    // Array that contains edges
    EdgeNode *edges[MAX];
    // Constructor with (directed/undirected) parameter.
    WeightedGraph(bool);
    
    void setVertexes(int V);
    // Solves Traveling SalesMan Problem (min array path, start node key) parameters
    int tsp(int **adjMatrix, int tspPath[], int start);
    // Prints all edges, ex: Reno to Seattle distance - 704 miles
    void printConnections();
    // Prints Adjancey Matrix of Edge Weights
    void printMatrix(int **adjMatrix);
    // Takes all edges and forms a matrix of weights.
    // Uses dijkstraPath to solve A to C = (A + B) + (B + C) connections.
    void matrix(int **adjMatrix);
    // Adds edges to edge array ( start, end, edge weight, undirected/directed )
    void addEdge(int x, int y, int weight, bool directed);
    void addEdge(int x, int y, int weight, std::string X, std::string Y, bool directed);
    // Finds shortest path between two points.
    int dijkstraPath(int end, int start);
};

#include "WeightedGraph.cpp"
#endif