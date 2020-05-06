#include "WeightedGraph.h"

//Given Miles per gallon
//Nevada Gas Price - 2.324
#define MPG 40
#define NPG 2.324

// Prototypes
void tspPrint(int tspPath[] , int miles, int vertexes, WeightedGraph* work);


int main(){

// Initilized a weighted graph as undirected.
WeightedGraph *work = new WeightedGraph(false);

// Setting all edges with mileage I googled, false = undirected

// Label Index.  These are hardcoded.  Method can be changed
// example:  input.txt or user input.
// 0 - Reno, 1 - Salt Lake City, 2 - Las Vegas, 3 - San Fran, 4 - Seattle

// work->addEdge(start, end, weight, start label, end label, directed)
work->addEdge(0, 1, 518, "Reno", "Salt Lake City", false);
work->addEdge(0, 2, 444, "Reno", "Las Vegas", false);
work->addEdge(0, 3, 218, "Reno", "San Fransico", false);
work->addEdge(0, 4, 704, "Reno", "Seattle", false);
work->addEdge(1, 4, 841, "Salt Lake City", "Seattle", false);
work->addEdge(2, 3, 571, "Las Vegas", "San Franisco", false);
work->addEdge(2, 1, 420, "Las Vegas", "Salt Lake City", false);
work->addEdge(3, 4, 808, "San Francisco", "Seattle", false);

// Create a 2D array for purpose of solving TSP problem.
int vertexes = 5;
int **adjMatrix;
adjMatrix = new int *[vertexes];
for(int i = 0; i<vertexes; i++)
    adjMatrix[i] = new int[vertexes];

// Do some work.
work->printConnections();
// Take graph list and convert to matrix.
work->matrix(adjMatrix);
work->printMatrix(adjMatrix);

// tspPath is a container to return the min path
int tspPath[vertexes];
// tsp returns an int of min path cost. 
// tsp also has access to tspPath[] for storing.
int tspMiles = work->tsp(adjMatrix, tspPath, 0);

tspPrint(tspPath, tspMiles, vertexes, work);
}

// Prints out solution to traveling salesman problem to terminal and outfile
void tspPrint(int tspPath[], int miles, int vertexes, WeightedGraph* work){

    std::cout << "\n\nMinimial cost path: " << work->edges[0]->label <<" -> ";
    for(int i =0; i < vertexes-1; i++){
        if(i == vertexes-2)
            std::cout << work->edges[tspPath[i]]->label << " -> " << work->edges[0]->label;
        else{
            std::cout << work->edges[tspPath[i]]->label << " -> ";
        }

    }
    std::cout << "\nMiles: " << miles;
    std::cout << "\nGallons of gas (40 mpg): " << miles/MPG;
    std::cout << "\nCost using Nevada average per gallon (2.324): " << (miles/MPG)*NPG<<std::endl;
  
    // This will open previously created file and appean to it.
    std::ofstream out;
    out.open ("FinalProjectText.txt", std::ios::out | std::ios::app);
        
        
        
        out << "\n\nMinimial cost path: " << work->edges[0]->label <<" -> ";
        for(int i =0; i < vertexes-1; i++){
            if(i == vertexes-2)
                out << work->edges[tspPath[i]]->label << " -> " << work->edges[0]->label;
            else{
                out << work->edges[tspPath[i]]->label << " -> ";
            }

        }
        out << "\nMiles: " << miles;
        out << "\nGallons of gas (40 mpg): " << miles/MPG;
        out << "\nCost using Nevada average per gallon (" << NPG << "): " << (miles/MPG)*NPG<<std::endl;
        
    out.close();

        std::cout << work->edges[0]->label;
}
