#include <cstdlib>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>
//Given Miles per gallon
//Nevada Gas Price - 2.324
#define MPG 40
#define NPG 2.324
#define MAX 100

const char *cities[5] = {"Reno", 
                        "Salt Lake City", 
                        "Las Vegas", 
                        "San Fransico", 
                        "Seattle"};    


class EdgeNode{
    public:
        int key;
        int weight;
        EdgeNode *next;
        EdgeNode(int);
        EdgeNode(int, int);
};

EdgeNode::EdgeNode(int key){
    this->key = key;
    this->weight = 0;
    this->next = NULL;
}

EdgeNode::EdgeNode(int key, int weight){
    this->key = key;
    this->weight = weight;
    this->next = NULL;
}

class WeightedGraph{
private: 
    static const size_t vertices = 5;

public:
    int adjMatrix[5][vertices];

    bool directed;
    EdgeNode *edges[MAX];
    WeightedGraph(bool);

    void setLabel(int key, const char []);
    char* getLabel(int key);
    int tsp(int tspPath[], int start);
    void print();
    void printMatrix();
    void matrix();
    void addEdge(int x, int y, int weight, bool directed);
    int dijkstraPath(int end, int start);
};
WeightedGraph::WeightedGraph(bool directed){
    this->directed = directed;

    for(int i = 0; i < 9; i++){
        this->edges[i] = NULL;
    }
}

void WeightedGraph::addEdge(int x, int y, int weight, bool directed){

    if(x+1 > 0 && x+1 < 6 && y+1 > 0 && y+1 <6){
        EdgeNode *edge = new EdgeNode(y, weight);
        edge->next = this->edges[x];
        this->edges[x] = edge;

            if(!directed){
                addEdge(y, x, weight, true);
            }
    }
}

int WeightedGraph::tsp(int tspPath[], int start){
    std::vector<int> vertex;
    for(int i = 0; i < 5; i++){
        if (i != start)
            vertex.push_back(i);
    }
        int tempArr[5];

        int minPath = INT_MAX;
        
        do{
            int currPathWeight = 0;

            int temp = start;
            for (int i = 0; i <vertex.size(); i++){
                tempArr[i] = vertex[i];
                currPathWeight += adjMatrix[temp][vertex[i]];
                temp = vertex[i];           
            }
            currPathWeight += adjMatrix[temp][start];
            if(std::min(minPath, currPathWeight)){
                minPath = std::min(minPath,currPathWeight);
                for(int i = 0; i<5;i++){
                    tspPath[i] = tempArr[i];
                }
            }
        }while(next_permutation(vertex.begin(), vertex.end()));        
   
return minPath;
}

void WeightedGraph::printMatrix(){
    std::cout << std::setw(18)<<" "<<"City x City Matrix by miles\n"; 
    std::cout << "    " << std::setfill('_')<< std::setw(50)<<" \n"<<std::setfill(' ');
    for(int i = 0;i < 5; i++){
        std::cout << std::setw(16) <<cities[i];
        for(int j =0; j <5;j++){
            std::cout<<" - "<< std::setw(4) << adjMatrix[j][i];
        }
        std::cout<< "\n";
    }
}
void WeightedGraph::matrix(){
    int tempNum, tracker = 0;
    int connection = 10;

    for(int v = 0; v < (5); v++){
        if(this->edges[v] != NULL){
                adjMatrix[tracker][v] = 0;
                connection -= v;
                EdgeNode *curr = this->edges[v];
                while(curr != NULL){
                    connection -= curr->key;
                    adjMatrix[curr->key][v] = curr->weight;
                    curr = curr->next;
                }
                if(connection != 0){
                tempNum = dijkstraPath(connection, v);
                adjMatrix[connection][v] = tempNum;
                }
        }
    connection = 10;
    tracker++;
    }    
}
void WeightedGraph::print(){

    for(int v = 0; v < (6); v ++){
        if(this->edges[v] != NULL){
            std::cout << cities[v] << " has neighbors: \n";
            EdgeNode *curr = this->edges[v];
            while(curr != NULL){
                std::cout << cities[curr->key] << " distance - " << curr->weight << std::endl;
                curr = curr->next;
            }
            std::cout<<std::endl;
        }
    }
}

int WeightedGraph::dijkstraPath(int end, int start){

    bool mark[MAX];
    int distance[MAX];
    int parent[MAX];
    EdgeNode *curr;
    int currVertice, linkVertice, weight, minPath;

        for(int i = 0; i < (MAX); i ++){
            mark[i] = false;
            distance[i] = INT_MAX;
            parent[i] = -1;
        }

    distance[start] = 0;
    currVertice = start;

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

        //Changes current vertice to vertice with shortest distance.
        minPath = INT_MAX;
        for(int i = 0; i < (MAX); i ++){
            if(!mark[i] && (distance[i] < minPath)){
                currVertice = i;
                minPath = distance[i];
            }
        }
    }

return distance[end];
  
}
void tspPrint(int tspPath[], int miles){

    int tempIndex = 0;
    std::cout << "\n\nShortest path: " << cities[0];
    for(int i =0; i < 4; i++){
        tempIndex = tspPath[i];
        std::cout << " -> " << cities[tempIndex];
        if (i == 4)
            std::cout << " -> " << cities[0];
    }
    std::cout << "\nMiles: " << miles;
    std::cout << "\nGallons of gas (40 mpg): " << miles/MPG;
    std::cout << "\nCost using Nevada average per gallon (2.324): " << (miles/MPG)*NPG<<std::endl;
}
int main(){

WeightedGraph *work = new WeightedGraph(false);

// 0 - Reno, 1 - Salt Lake City, 2 - Las Vegas, 3 - San Fran, 4 - Seattle 
work->addEdge(0, 1, 518, false);
work->addEdge(0, 2, 444, false);
work->addEdge(0, 3, 218, false);
work->addEdge(0, 4, 704, false);
work->addEdge(3, 4, 808, false);
work->addEdge(2, 3, 571, false);
work->addEdge(2, 1, 420, false);
work->addEdge(1, 4, 841, false);

work->print();
work->matrix();
work->printMatrix();
// 0 - Reno
int tspPath[5];
int tspMiles = work->tsp(tspPath, 0);
tspPrint(tspPath, tspMiles);

}