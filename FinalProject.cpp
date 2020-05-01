#include <cstdlib>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <vector>
#include <string>

//Given Miles per gallon
//Nevada Gas Price - 2.324
//MAX used for making arrays
#define MPG 40
#define NPG 2.324
#define MAX 100

// This is a global for the cities
// Goal, change this to a label within classes
// So... along with storing key, we store label being the name.
// This way we can get away from globals and make it more of a true class.
const char *cities[5] = {"Reno", 
                        "Salt Lake City", 
                        "Las Vegas", 
                        "San Fransico", 
                        "Seattle"};    

// EdgeNode Class will connect node to node
// Stores key(ex: 0, 1, 2, 3)
// Stores Weight(mileage)
// Needs getters and setters
class EdgeNode{
    public:
        int key;
        int weight;
        
        // For creating nodes, next being the next node in line.
        EdgeNode *next;
        // Constructors for EdgeNodes.
        EdgeNode(int);  // EdgeNode(key)
        EdgeNode(int, int);  // EdgeNode(key, weight)
};
// Constucter with (key) parameter
EdgeNode::EdgeNode(int key){
    this->key = key;
    this->weight = 0;
    this->next = NULL;    // Sets next null location to NULL
}
// Constructor with (key, weight) parameter
EdgeNode::EdgeNode(int key, int weight){
    this->key = key;
    this->weight = weight;
    this->next = NULL;    // Sets next location to NULL
}

// Node Class, will be used to for Adjancey List
// Not yet used in implementation, will address.
// Needs Work, should track a head and whatever.
class Node{
public:
    int key;
    Node *next;
    Node(int);
};
// Node Constructor with (key) parameter
Node::Node(int key){
    this->key = key;
    this->next = NULL;
}

// WeightedGraph class (Graph with edges that contain values)
// Needs work with addressing some hard coding.
class WeightedGraph{
private: 
    // This is a static member just for the purpose of hard coding the Adjancey Matrix.
    // May change this to a vector and pass from main into class.
    // Would be better memory management and more a true class.
    static const size_t vertexs = 5;

public:
    // Matrix for the purpose of solving Travelling Salesman Problem.
    int adjMatrix[vertexs][vertexs];
    // For identifying undirected and directered edges.
    bool directed;
    // Array that contains edges
    EdgeNode *edges[MAX];
    // Constructor with (directed/undirected) parameter.
    WeightedGraph(bool);
    
    // Solves Traveling SalesMan Problem (min array path, start node key) parameters
    int tsp(int tspPath[], int start);
    // Prints all edges, ex: Reno to Seattle distance - 704 miles
    void printConnections();
    // Prints Adjancey Matrix of Edge Weights
    void printMatrix();
    // Takes all edges and forms a matrix of weights.
    // Uses dijkstraPath to solve A to C = (A + B) + (B + C) connections.
    void matrix();
    // Adds edges to edge array ( start, end, edge weight, undirected/directed )
    void addEdge(int x, int y, int weight, bool directed);
    // Finds shortest path between two points.
    int dijkstraPath(int end, int start);
};
// Constructor ( undirected/directed ) parameter
WeightedGraph::WeightedGraph(bool directed){
    this->directed = directed;
    
    // Defaults all edges to NULL
    for(int i = 0; i < MAX; i++){
        this->edges[i] = NULL;
    }
}
// addEdge will add a weighted edge to edges[] with ( start, end, edge weight, undirected/directed ) parameter
void WeightedGraph::addEdge(int x, int y, int weight, bool directed){
    // This will bounds check between 0  to vertexs. 
    if(x+1 > 0 && x < vertexs + 1 && y+1 > 0 && y <vertexs +1){
        // This will create and set weight to y
        EdgeNode *edge = new EdgeNode(y, weight);
        // This will set created edge->next to x's node location in edges[] 
        edge->next = this->edges[x];
        // This will set edge[x] to edgeNode of y 
        this->edges[x] = edge;
        // This will effective effectively create a linked list of nodes
          
            // if its undirected, add to list of destination (y)
            if(!directed){
                addEdge(y, x, weight, true);
            }
    }
}

// This function solve the Traveling salemans probrlem.
// Uses an adaption of hamiltons circuit algorithm
// (correct path array, starting point) parameters
// returns int
int WeightedGraph::tsp(int tspPath[], int start){
    // Vector used to hold indexs of edges
    std::vector<int> vertex;
    for(int i = 0; i < vertexs; i++){
        if (i != start)
            vertex.push_back(i);
    }
        // Array to copy correct current path into
        // Min cost path container
        int tempArr[vertexs];
        int minPath = INT_MAX; 
         
        // For this project, output of all paths and mileage was required.
        // This information will be sent to a text file "FinalProjectText"
        // Reason:  To avoid clutting of the screen
        std::ofstream out;
        out.open("FinalProjectText.txt");
        out<< "OUTPUT OF ALL PATHS AND MILES:\n\n";
        
        // Do While Loop computing all paths
        do{
            // Tracks current of path
            // temp for purpose of traverse of matrix
            int currPathWeight = 0;
            int temp = start;
          
            out<< cities[temp]<< " -> ";
            // This loop will traverse the matrix adding current path weight
            for (int i = 0; i <vertex.size()+1; i++){
                currPathWeight += adjMatrix[temp][vertex[i]];
                temp = vertex[i];
                tempArr[i] = temp;           
            }
            // Add path weight back to origin
            currPathWeight += adjMatrix[temp][start];
            
            // This loop is for outputting current path to text file.
            // vertex - 1 due to start has been removed from path
            for(int i = 0;i < vertexs-1;i++){
                if( i == vertexs-2)
                    out<< cities[tempArr[i]]<< " -> ";
                else
                    out<< cities[tempArr[i]] << " -> ";
            }
            // Output final stop and current path weight
            out<< cities[temp];
            out<<  "\tMiles - "<< currPathWeight <<std::endl;
            
            // If current path is new minimal cost path, replace tspPath
            minPath = std::min(minPath, currPathWeight);
            if(minPath == currPathWeight){
                for(int i = 0; i < vertexs-1;i++){
                    tspPath[i] = tempArr[i];
                }
            }
        // next_permutation will circle til all computations are made.
        }while(next_permutation(vertex.begin(), vertex.end()));        
   out.close();
// return minimal cost as int
return minPath;
}

// Prints the matrix to terminal created via matrix()
void WeightedGraph::printMatrix(){
    std::cout << std::setw(18)<<" "<<"City x City Matrix by miles\n\n";
    std::cout << std::setw(20) << " " << std::setw(5) << "Reno"<< std::setw(5) << "SLC"
              << std::setw(7) << "LV" << std::setw(7) << "SF" << std::setw(10) << "Seattle" << std::endl;
    std::cout << "    " << std::setfill('-')<< std::setw(52)<<" \n"<<std::setfill(' ');
    for(int i = 0;i < vertexs; i++){
        std::cout << std::setw(16) <<cities[i];
        for(int j =0; j < vertexs;j++){
            std::cout<<" - "<< std::setw(4) << adjMatrix[j][i];
        }
        std::cout<< "\n";
    }
}

// Creates a matrix stored in adjMatrix
void WeightedGraph::matrix(){
    // Counters
    int tempNum, tracker = 0;
    // Connection is to track missing direct connections.
    // Note that the number of edges = (n*(n-1))/2 where n = # of vertexs
    // If we give each vertex a value 0-4, where 4 is does not connect to X
    // Then (# of edges) - 4 - 3 - 2 - 0 = x = 1
    // We then can use this with dijkstraPath to get a weight for (4,X)
    int connection = (vertexs*(vertexs-1))/2;
    
    // Converts list into matrix.
    for(int i = 0; i < vertexs; i++){
        // If end not end of edges array compute
        if(this->edges[i] != NULL){
                // First, set node to it's as 0, ex: reno to reno = 0
                adjMatrix[tracker][i] = 0;
                // connection - current position
                connection -= i;
                
                // Loop till reach end of list. 
                EdgeNode *curr = this->edges[i];
                while(curr != NULL){
                    connection -= curr->key;
                    adjMatrix[curr->key][i] = curr->weight;
                    curr = curr->next;
                }
                // If a missed connect is found then, compute it.
                if(connection != 0){
                tempNum = dijkstraPath(connection, i);
                adjMatrix[connection][i] = tempNum;
                }
        }
    // Reset connection
    connection = (vertexs*(vertexs-1))/2;
    tracker++;
    }    
}
// Prints all connections to terminal
void WeightedGraph::printConnections(){

    for(int i = 0; i < vertexs; i++){
        if(this->edges[i] != NULL){
            std::cout << std::setw(10) << cities[i] << " connects to: \n";
            EdgeNode *curr = this->edges[i];
            while(curr != NULL){
                std::cout <<std::setw(14) << cities[curr->key] << " distance - " << curr->weight << " miles"<< std::endl;
                curr = curr->next;
            }
            std::cout<<std::endl;
        }
    }
}

// Uses Dijkstra's algorithm to find shortest path.
int WeightedGraph::dijkstraPath(int end, int start){
    // Containers used for tracking.
    bool mark[MAX];
    int distance[MAX];
    int parent[MAX];
    EdgeNode *curr;
    int currVertice, linkVertice, weight, minPath;
        // Set all containers to defaults.
        for(int i = 0; i < (MAX); i ++){
            mark[i] = false;
            distance[i] = INT_MAX;
            parent[i] = -1;
        }
    // Set to start position
    distance[start] = 0;
    currVertice = start;
    
    // Alogrithm that computes shortest path.
    while(mark[currVertice] == false){

        mark[currVertice] = true;
        curr = this->edges[currVertice];

        while(curr != NULL){

            linkVertice = curr->key;
            weight = curr->weight;

            if((distance[currVertice] + weight) < distance[linkVertice]){
                distance[linkVertice] = distance[currVertice] + weight;
                parent[linkVertice] = currVertice;
            }
            curr = curr->next;
        }

        //Changes current vertex to vertex with shortest distance.
        minPath = INT_MAX;
        for(int i = 0; i < (MAX); i ++){
            if(!mark[i] && (distance[i] < minPath)){
                currVertice = i;
                minPath = distance[i];
            }
        }
    }

// returns shortest path distance to end.
return distance[end];
}

// Prints out solution to traveling salesman problem to terminal and outfile
void tspPrint(int tspPath[], int miles, int vertexs){

    std::cout << "\n\nMinimial cost path: " << cities[0] <<" -> ";
    for(int i =0; i < vertexs-1; i++){
        if(i == vertexs-2)
            std::cout << cities[tspPath[i]] << " -> " << cities[0];
        else{
            std::cout << cities[tspPath[i]] << " -> ";
        }

    }
    std::cout << "\nMiles: " << miles;
    std::cout << "\nGallons of gas (40 mpg): " << miles/MPG;
    std::cout << "\nCost using Nevada average per gallon (2.324): " << (miles/MPG)*NPG<<std::endl;
  
    // This will open previously created file and appean to it.
    std::ofstream out;
    out.open ("FinalProjectText.txt", std::ios::out | std::ios::app);
        
        out << "\n\nMinimial cost path: " << cities[0] <<" -> ";
        for(int i =0; i < vertexs-1; i++){
            if(i == vertexs-2)
                out << cities[tspPath[i]] << " -> " << cities[0];
            else{
                out << cities[tspPath[i]] << " -> ";
            }

        }
        out << "\nMiles: " << miles;
        out << "\nGallons of gas (40 mpg): " << miles/MPG;
        out << "\nCost using Nevada average per gallon (2.324): " << (miles/MPG)*NPG<<std::endl;

    out.close();
}


int main(){
// Initilized a weighted graph as undirected.
WeightedGraph *work = new WeightedGraph(false);

// Setting all edges with mileage I googled, false = undirected
// 0 - Reno, 1 - Salt Lake City, 2 - Las Vegas, 3 - San Fran, 4 - Seattle 
work->addEdge(0, 1, 518, false);
work->addEdge(0, 2, 444, false);
work->addEdge(0, 3, 218, false);
work->addEdge(0, 4, 704, false);
work->addEdge(1, 4, 841, false);
work->addEdge(2, 3, 571, false);
work->addEdge(2, 1, 420, false);
work->addEdge(3, 4, 808, false);

// Do some work.
work->printConnections();
work->matrix();
work->printMatrix();
// 0 - Reno
// vertexs = 5
int tspPath[5];
int tspMiles = work->tsp(tspPath, 0);
tspPrint(tspPath, tspMiles, 5);
}
